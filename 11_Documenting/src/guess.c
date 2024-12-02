#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include <locale.h>
#include <libintl.h>
#include <ctype.h>
#include "config.h"
#include <unistd.h>

#define _(STRING) gettext(STRING) /**< gettext to choose what to translate */
#define LOCALE_PATH "po" /**< our own localization */

/** @mainpage Number guesser library
 * @copydetails library
 */
/** @page library Number guesser library
 * # Best Guesser
 * ## Real markdown Mainpage
 * Usage: ./guess [\a -r ]\n
 * -r to use roman
 *
 * - guesses numbers
 * - you can do it in
 *   - russian
 *   - english
 * - your numbers is
 *   - roman
 *   - arabic
 */

/** @page guess
 * @p Number guesser
 * @section SYNOPSIS
 * `namegen` [ \a -r ]
 * @section DESCRIPTION
 * Guesses number between 1 and 100
 *
 * @copydetails library
 */

/** to_roman func. @p prints roman number
 *
 * @param n arabic number 
 * @return 0 if good or 1 if bad
 */
int to_roman(int n) {
		int pipefd[2];
		char buff[128];
		pid_t pid;
		if (pipe(pipefd) == -1) {
			fprintf(stderr, "Pipe failed\n");
			return 1;
		}
		pid = fork();
		if (pid == 0) {
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			char command[128];
			snprintf(command, sizeof(command), "%d", n);
			char *args[] = {"roman", command, NULL};
			execvp(args[0], args);
			fprintf(stderr, "pip install roman!\n");
			return 1;
		} else {
			close(pipefd[1]);
			int bytes;
			while ((bytes = read(pipefd[0], buff, sizeof(buff) - 1)) > 0) {
				buff[bytes - 1] = '\0';
				printf(_("Is your number bigger than "));
				printf("%s?\n", buff);
			}
			close(pipefd[0]);
		}
		return 0;
}

/** to_arabic func. @p prints arabic number
 *
 * @param s string with roman number
 * @return 0 if good or 1 if bad
 */
int to_arabic(char *s) {
		int pipefd[2];
		char buff[128];
		pid_t pid;
		if (pipe(pipefd) == -1) {
			fprintf(stderr, "Pipe failed\n");
			return 1;
		}
		pid = fork();
		if (pid == 0) {
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			char command[128];
			snprintf(command, sizeof(command), "%s", s);
			char *args[] = {"roman", "-r", command, NULL};
			execvp(args[0], args);
			fprintf(stderr, "pip install roman!\n");
			return 1;
		} else {
			close(pipefd[1]);
			int bytes;
			while ((bytes = read(pipefd[0], buff, sizeof(buff) - 1)) > 0) {
				buff[bytes - 1] = '\0';
				printf(_("Is your number bigger than "));
				printf("%s?\n", buff);
			}
			close(pipefd[0]);
		}
		return 0;
}


/** Main func. @p Guesses number of your between 1 and 100.
 *
 * @param argc how many args
 * @param argv some args
 * @return based 0 if good code or 1 if bad.
 */
int main(int argc, char*argv[]) {
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALE_PATH);
	textdomain(PACKAGE);
	int flag = 0;
	if (argc > 1) {
		if (argc > 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
			printf(_("Usage: ./guess [-r]\n"));
			printf(_("-r to use roman numbers\n"));
			return 0;
		}
	}
	if (argc == 2) {
		if (!strcmp(argv[1], "-r")) {
			flag = 1;
		} else {
			fprintf(stderr, "Invalid arguments. Use -h or --help\n");
			return 0;
		}
	}
	printf(_("Imagine the number!\n"));
	int n = 50;
	int up = 99, down = 1;
	while (down <= up) {
		if (flag == 1) {
			if (to_roman(n) == -1) {
				fprintf(stderr, "Romanisation failed\n");
				return 1;
			}
		} else {
			printf(_("Is your number bigger than %d?\n"), n);
		}
        	char ans[128];
		if (!scanf("%s", ans)) {
			return 0;
		}
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
