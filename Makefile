CC=gcc
CFLAGS=-c -pthread -Wall -g
LIBS=-pthread -lpthread -g
OBJS=Ex2.o
SRC=Ex2.c

ex2: $(OBJS)
	$(CC) $(OBJS) -o ex2 $(LIBS)

main.o: $(SRC)
	$(CC) $(CFLAGS) $(SRC)

clean:
	rm -f $(OBJS) ex2
