#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include <locale.h>
#include <libintl.h>
#include <ctype.h>
#include "config.h"

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po"

int main(int argc, char*argv[]) {
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALE_PATH);
	textdomain(PACKAGE);
	printf(_("Imagine the number!\n"));
	int n = 50;
	int up = 99, down = 1;
	while (down <= up) {
		printf(_("Is your number bigger than %d?\n"), n);
        	char ans[128];
		scanf("%s", ans);
		for (int i = 0; i < strlen(ans); ++i) {
			ans[i] = tolower(ans[i]);
		}
		printf("%s\n", ans);
		int mid = (up + down) / 2;
		if (strcmp(ans, _("yes")) == 0) {
			down = mid + 1;
			n = (up - down) / 2 + down;
		} else if (strcmp(ans, _("no")) == 0) {
			up = mid - 1;
			n = (up - down) / 2 + down;
		} else {
			printf(_("Please enter 'yes' or 'no'\n"));
		}

	}
	printf(_("Your number is %d!\n"), n);
	return 0;
}
