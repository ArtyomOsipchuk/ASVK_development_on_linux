.PHONY: clean
GENERATES= *.o o.* *~ *.out esub

all: compile test check

compile:
	cc -O0 -g -Wall esub.c -o esub

test:
	echo '_abcdef_' | ./esub '(a)b(c)d(e)' '<\3\2\1>' > t1_esub.out
	echo '_abcdef_' | sed -E 's/(a)b(c)d(e)/<\3\2\1>/' > t1_sed.out
	diff t1_esub.out t1_sed.out
	echo '_abcdef_' | ./esub '(a)b(c)(def)' '<\3\2\1>' > t2_esub.out
	echo '_abcdef_' | sed -E 's/(a)b(c)(def)/<\3\2\1>/' > t2_sed.out
	diff t2_esub.out t2_sed.out
	echo 'ebaabcd' | ./esub 'ab' 'BA' > t3_esub.out
	echo 'ebaabcd' | sed -E 's/ab/BA/' > t3_sed.out
	diff t3_esub.out t3_sed.out
	echo 'Learn regular expressions' | ./esub '(regular) (express)ion(s?)' 'to \2 emotion\3 \1ly' > t4_esub.out
	echo 'Learn regular expressions' | sed -E 's/(regular) (express)ion(s?)/to \2 emotion\3 \1ly/' > t4_sed.out
	diff t4_esub.out t4_sed.out
check:
	./esub
	echo 'ab' | ./esub 'a(b' 'ab'
	echo 'ab' | ./esub 'ab' 'a\1b'
	echo 'eabc' | ./esub 'ab' 'BA'
	echo 'DabcE' | ./esub 'a(b)c' '\1_\1'
	echo '_abcdef_' | ./esub '(a)b(c)d(e)' '<\3\2\1>'
	echo '2024 17 October Thursday' | ./esub '([[:digit:]]{4}) +([[:digit:]]{1, 2}) +([[:alpha:]]+) +([[:alpha:]]+)' '\4, \2 \3 year of \1'
	echo '2024 17 October Thursday' | sed -E 's/([[:digit:]]{4}) +([[:digit:]]{1, 2}) +([[:alpha:]]+) +([[:alpha:]]+)/\4, \2 \3 year of \1/'

clean:
	rm -f $(GENERATES)
