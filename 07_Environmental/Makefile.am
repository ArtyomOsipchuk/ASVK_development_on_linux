CFLAGS = -Wall -O0 -g

bin_PROGRAMS=rhash

rhash_SOURCES=src/rhash.c

TESTS=other_sums.sh

other_sums.sh:
	echo "abcde" > test_file
	echo "Sha1 test_file" | ./rhash > output_rhashc
	echo " test_file" >> output_rhashc
	echo test_file | sha1sum > output_sha
	diff output_rhashc output_sha
	echo "md5 test_file" | ./rhash > output_rhashc
	echo " test_file" >> output_rhashc
	echo test_file | md5sum > output_md
	diff output_rhashc output_md
	rm -rf test_file output_sha output_md output rhashc
	chmod +x $@

gitclean:
	git clean -df
