SUBDIRS = po lib src tests

@DX_RULES@

all-local: doxygen-doc

doxygen-doc/man/man1/guess.1:	doxygen-doc

man1_MANS = doxygen-doc/man/man1/guess.1

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

http: doxygen-doc
	python3 -m http.server 5000 --directory $</html

checklog:	check
	cat tests/*.log

gitclean:
	git clean -df
