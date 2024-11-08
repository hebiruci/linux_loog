# 指定编译器
CC = gcc

# 指定头文件和库文件的路径
INCLUDE_PATHS = -I/home/cyx/study/Source/binutils-2.34/bfd -I/home/cyx/study/Source/binutils-2.34/include
LIB_PATHS = -L/home/cyx/Install/binutils/install/lib -L/home/cyx/study/Source/binutils-2.34/libiberty -L/home/cyx/study/Source/binutils-2.34/bfd

# 指定库
LIBS = -lbfd -liberty -lz -ldl

# 指定目标文件和源文件
TARGET = revise
SRC = revise1.c

# 编译选项
CFLAGS = $(INCLUDE_PATHS)
LDFLAGS = $(LIB_PATHS) $(LIBS)

# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(SRC)
	$(CC) -g $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# 清理生成的文件
clean:
	rm -f $(TARGET)
