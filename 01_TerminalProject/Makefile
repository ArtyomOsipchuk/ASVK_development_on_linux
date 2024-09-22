SRC=Show.c
EXEC=Show
CC=cc
LDLIBS=-lncurses
CFLAGS=-Wall

%:	%.c
	$(CC) $(CFLAGS) $< $(LDLIBS) -o $@

all:	Show

clean:
	rm -r o oo $(EXE) *.o

