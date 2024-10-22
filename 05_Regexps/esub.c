#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAXGR 10

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: echo <text> | ./esub <regexp> <pattern>\n");
		return 0;
	}

        char *buf;
        size_t len = 0;
        int chars, b, e;
        regex_t regex;
        regmatch_t bags[MAXGR];

        int err_number = regcomp(&regex, argv[1], REG_EXTENDED);
	if (err_number) {
		char err_msg[256];
		regerror(err_number, NULL, err_msg, sizeof(err_msg));
		printf("Ошибка: %s\n", err_msg);
		return 0;
	}

        for (buf = NULL; (chars = getline(&buf, &len, stdin)) != -1; buf = NULL) {
                buf[chars - 1] = 0;
                if (regexec(&regex, buf, MAXGR, bags, 0) == 0) {
                        for(int i = 1; i < MAXGR && bags[i].rm_so >= 0; ++i) {
                                b = bags[i].rm_so, e = bags[i].rm_eo;
				char repl[e - b];
				sprintf(repl, "\\%d", i);
				for (int j = 0; j < strlen(argv[2]); ++j) {
					char cmp[e - b];
					strncpy(cmp, argv[2] + j, 2);
					cmp[2] = 0;
					if (strcmp(cmp, repl) == 0) {
						char new[e - b];
						strncpy(new, buf + b, e - b);
						new[e - b] = 0;
						char old[j + 1];
						strncpy(old, argv[2], j + 1);
						old[j + 1] = 0;
						char cent[strlen(argv[2]) - j - 1];
						strncpy(cent, argv[2] + j + 2, strlen(argv[2]) - j - 1);
						cent[strlen(argv[2]) - j - 1] = 0;
						sprintf(argv[2], "%s%s%s", old, new, cent);
					}
				}
			}
			int i = 0, j = 0;
			char c = '\\';
			while (argv[2][i]) {
				if (argv[2][i] != c) {
					argv[2][j++] = argv[2][i];
				}
				i++;
			}
			argv[2][j] = 0;
                        b = bags[0].rm_so, e = bags[0].rm_eo;
			char tmp[e - b + 1];
			strncpy(tmp, buf + b, e - b);
			tmp[e - b] = 0;
			for (int j = 0; j < strlen(buf); ++j) {
				char cmp[e - b];
				strncpy(cmp, buf + j, e - b);
				cmp[e - b] = 0;
				if (strcmp(cmp, tmp) == 0) {
					char old[j];
					strncpy(old, buf, j);
					old[j] = 0;
					char cent[100]; //strlen(buf) - e + b - strlen(argv[2])];
					strncpy(cent, buf + j + e - b, strlen(buf) - j - e + b);
					cent[strlen(buf) - j + e - b] = 0;
					sprintf(buf, "%s%s%s", old, argv[2], cent);
					break;
				}
			}
			puts(buf);
                }
                free(buf);
        }
        regfree(&regex);
        return 0;
}
