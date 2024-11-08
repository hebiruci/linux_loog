DYNAMIC_LIB = ./libmath.so
pic_objects = add.o sub.o mult.o div.o

dynamic: $(DYNAMIC_LIB)

$(pic_objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(DYNAMIC_LIB): $(pic_objects)
	ld -verbose -shared -o $@ $^
# 选项-verbose可以输出ld运行过程中的详细信息，-shared选项表示生成动态链接库文件。
$(TARGET): main.o $(DYNAMIC_LIB)
	$(CC) -o $@ main.o -L. -lmath -Wl,-rpath=.
#使用 -rpath 选项，将动态库的路径嵌入到可执行文件中。
clean:
	rm -f $(pic_objects)
	rm -f $(DYNAMIC_LIB)
# 执行make dynamic即可生成动态库文件libmath.so
