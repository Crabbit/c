#ls makefile.

CC = gcc

CFLAGS = -g -Wall

OBJECTS = main-ls.o decode_switches.o
EXEC = ls


$(EXEC): $(OBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS) 

main-ls.o: main-ls.c decode_switches.h

#处理用户输入模块
decode_switches.o: decode_switches.c decode_switches.h

.PHONY:clean
clean:
	rm $(OBJECTS)
