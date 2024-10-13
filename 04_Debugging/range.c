#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int a = 0, b = 0, c = 1;
	if (argc == 2) {
		b = atoi(argv[1]);
	} else if (argc == 3) {
		a = atoi(argv[1]);
		b = atoi(argv[2]);
	} else if (argc == 4) {
		a = atoi(argv[1]);
		b = atoi(argv[2]);
		c = atoi(argv[3]);
	}
	for (int i = a; i < b; i += c) {
		printf("%d", i);
	}
	return 0;
}
