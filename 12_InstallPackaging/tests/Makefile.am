TESTS = dummy
bin_PROGRAMS = dummy

check_PROGRAMS = dummy

%.c: %.ts
	checkmk $< > $@

LDADD=$(top_builddir)/lib/libguess.la @CHECK_LIBS@
