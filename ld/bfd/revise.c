#include "config.h"
#include "ansidecl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bfd.h>

void bfd_error(const char *message) {
    bfd_perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input file> <section name> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_filename = argv[1];
    const char *section_name = argv[2];
    const char *output_filename = argv[3];

    // 初始化BFD库
    bfd_init();

    // 打开输入文件
    bfd *input_bfd = bfd_openr(input_filename, NULL);
    if (!input_bfd) {
        bfd_error("Failed to open input file");
    }

    // 检查文件是否是目标文件
    if (!bfd_check_format(input_bfd, bfd_object)) {
        bfd_error("Input file is not an object file");
    }

    // 打印所有的section名称用于调试
    printf("Input file sections:\n");
    for (asection *sec = input_bfd->sections; sec != NULL; sec = sec->next) {
        printf("  %s\n", sec->name);
    }

    // 找到指定的section
    asection *section = bfd_get_section_by_name(input_bfd, section_name);
    if (!section) {
        fprintf(stderr, "Section not found: %s\n", section_name);
        bfd_close(input_bfd);
        return EXIT_FAILURE;
    }

    // 分配缓冲区并读取section内容
    size_t section_size = bfd_section_size(section);
    void *buffer = malloc(section_size);
    if (!buffer) {
        bfd_error("Failed to allocate buffer");
    }

    if (!bfd_get_section_contents(input_bfd, section, buffer, 0, section_size)) {
        bfd_error("Failed to read section contents");
    }

    // 进行修改，例如将section的内容全部设置为0
    memset(buffer, 0, section_size);

    // 创建输出文件
    bfd *output_bfd = bfd_openw(output_filename, bfd_get_target(input_bfd));
    if (!output_bfd) {
        bfd_error("Failed to open output file");
    }

    // 设置输出文件格式
    if (!bfd_set_format(output_bfd, bfd_object)) {
        bfd_error("Failed to set output file format");
    }

    // 复制所有section到输出文件
    for (asection *sec = input_bfd->sections; sec != NULL; sec = sec->next) {
        printf("Creating section: %s with flags: 0x%lx\n", sec->name, sec->flags);

        // 创建新section
        asection *new_sec = bfd_make_section_anyway_with_flags(output_bfd, sec->name, sec->flags);
        if (!new_sec) {
            fprintf(stderr, "Failed to create section: %s\n", sec->name);
            continue;
        }

        // 设置section内容
        size_t size = bfd_section_size(sec);
        if (!bfd_set_section_contents(output_bfd, new_sec, buffer, 0, size)) {
            fprintf(stderr, "Failed to write section contents: %s\n", sec->name);
        }
    }

    // 释放资源
    free(buffer);
    bfd_close(input_bfd);
    bfd_close(output_bfd);

    return EXIT_SUCCESS;
}
