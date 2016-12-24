CC=gcc
CFLAGS=-c -pthread -Wall -g
LIBS=-pthread -lpthread -g
OBJS=main.o
SRC=main.c

a.out: $(OBJS)
	$(CC) $(OBJS) -o a.out $(LIBS)

main.o: $(SRC)
	$(CC) $(CFLAGS) $(SRC)

clean:
	rm -f $(OBJS) a.out
