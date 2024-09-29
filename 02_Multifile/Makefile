.PHONY: clean
GENERATES=prog prog-a prog-so README README-a README-so liboutput.so liboutput_static.a file1 file2 file3
TRASH= *o *~ o.*
CC= cc
CFLAGS= -Wall -fPIC

all:	README README-a README-so test

test:	prog prog-a prog-so
	./prog 2> file1 ; ./prog-a 2> file2 ; LD_LIBRARY_PATH=`pwd` ./prog-so 2> file3
	echo `cmp file1 file2`
	echo `cmp file1 file3`
	echo `cmp file2 file3`
	./prog a > file1 ; ./prog-a a > file2 ; LD_LIBRARY_PATH=`pwd` ./prog-so a > file3
	cmp file1 file2 ; cmp file1 file3 ; cmp file2 file3
	./prog a b c > file1 ; ./prog-a a b c > file2 ; LD_LIBRARY_PATH=`pwd` ./prog-so a b c > file3
	cmp file1 file2 ; cmp file1 file3 ; cmp file2 file3

liboutput_static.a:	liboutput_static.a(fun.o const.o)
	ar -rcs liboutput_static.a $^

liboutput.so:	fun.o const.o
	$(CC) -shared $^ -o $@

prog:	const.o fun.o prog.o
	$(CC) $^ -o $@

prog-a:	prog.o liboutput_static.a
	cc -L. prog.o -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. prog.o -loutput -o $@

README: prog
	./$< 2> $@

README-a:	prog-a
	./$< 2> $@

README-so:	prog-so
	LD_LIBRARY_PATH=`pwd` ./$< 2> $@

fun.o:	outlib.h

clean:
	rm -rf $(TRASH) $(GENERATES)
