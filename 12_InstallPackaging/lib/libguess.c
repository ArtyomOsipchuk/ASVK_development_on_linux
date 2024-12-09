#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include <locale.h>
#include <libintl.h>
#include <ctype.h>
#include "libguess.h"
#include <unistd.h>

#define _(STRING) gettext(STRING) /**< gettext to choose what to translate */
#define LOCALE_PATH "po" /**< our own localization */


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
                        fprintf(stderr, "pip install roman\n");
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
                        fprintf(stderr, "pip install roman\n");
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

