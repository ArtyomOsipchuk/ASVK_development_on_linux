CFLAGS = -Wall -O0 -g

bin_PROGRAMS=hh

hh_SOURCES=src/hh.c

TESTS=notatty.sh

notatty.sh:
	echo 'test "`./key < /dev/null 2>&1`" = "./key: Not a terminal"' > $@
	chmod +x $@

#gitclean:
#	git clean -df
