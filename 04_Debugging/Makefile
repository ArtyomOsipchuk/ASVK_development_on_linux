.PHONY: clean
GENERATES= *.o *~ t1.out t2.out a.out

all: main test clean

main:
	cc -O0 -g ./range.c

test: main
	gdb --batch -x ./debug1.gdb --args ./a.out 1 12 | grep "@@@*" > t1.out
	diff t1.out t1_perfect.out
	gdb --batch -x ./debug2.gdb --args ./a.out -100 100 3 | grep "@@@*" > t2.out
	diff t2.out t2_perfect.out

clean:
	rm -rf $(GENERATES)
