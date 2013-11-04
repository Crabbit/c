CFLAGS = -g
LDLIBS = -lssl -lcrypto -ldl
OBJS = order_commu.o order_file.o order_errno.o
EXEC = order_commu

$(EXEC): $(OBJS)
#	$(CC) -o $(EXEC) $(OBJS) $(LIBS)

order_commu.o: order_commu.c order_file.h order_errno.h

order_errno.o: order_errno.c order_errno.h

order_file.o: order_file.c order_errno.h


.PHONY:

clean:
	rm $(OBJS) $(EXEC)
