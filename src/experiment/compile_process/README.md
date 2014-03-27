这是一个

.c -->( 预处理 ) .i -->(编译) .s -->(汇编) .o -->(链接) 可执行文件的中间过程

libprint.a来自
gcc print_lili.c -c -o print_lili.o
gcc print_cici.c -c -o print_cici.o
ar rcs libprint.a print_lili.o print_cici.o

libprint.so来自
gcc print_lili.c print_cici.c -shared -fPIC -o libprint.so
