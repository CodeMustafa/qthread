CC=cc
CFLAGS=-g -Wall -c
LDFLAGS=-L .
LIB_SRC=queue.c thread_manage.c sync.c
LIB_OBJ=$(LIB_SRC:.c=.o)
LIB_OUT=libquark.a

all:$(LIB_OUT)

$(LIB_OUT): $(LIB_OBJ)
	ar -rcs $@ $(LIB_OBJ)
.c.o:
	$(CC) $(CFLAGS) $<

run: main.o $(LIB_OUT)
	$(CC) $(LDFLAGS) main.o -o run -lquark

clean:
	rm *.o *.a run
