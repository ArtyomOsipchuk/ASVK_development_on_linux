.PHONY: clean
GENERATES=labirinth labirinth1 labirinth2 labirinth3 labirinth1.c labirinth2.c labirinth3.c
TRASH= *o *~ o.*
CC= cc

all: labirinth labirinth1 labirinth2 labirinth3

run:
	./labirinth
	./labirinth1 5
	./labirinth2 _@ 4
	./labirinth3 2 "*%" 3

labirinth:
	$(CC) labirinth.c -o $@

labirinth1.c:
	cp labirinth.c labirinth0.c
	patch labirinth0.c < 01.patch
	cp labirinth0.c labirinth1.c

labirinth1: labirinth1.c
	$(CC) $^ -o $@

labirinth2.c: labirinth1.c
	patch labirinth0.c < 02.patch
	cp labirinth0.c labirinth2.c

labirinth2: labirinth2.c
	$(CC) $^ -o $@

labirinth3.c: labirinth2.c
	patch labirinth0.c < 03.patch
	cp labirinth0.c labirinth3.c
	rm labirinth0.c

labirinth3: labirinth3.c
	$(CC) $^ -o $@

clean:
	rm -rf $(TRASH) $(GENERATES)

