#include "errno.h"
#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
#include "string.h"
#include "rhash.h" /* LibRHash interface */
#include "unistd.h"

#ifndef READLINE
#include <readline/readline.h>
#endif

int main(int argc, char *argv[]) {
   while (1) {
        char *input = NULL;
	size_t size = 0;
#ifndef READLINE
        input = readline("> ");
        if (input == NULL) {
                printf(">>Exiting command line<<\n");
		return 0;
        }
#else 
        printf("> ");
	if (getline(&input, &size, stdin) == -1) {
                printf(">>Exiting command line<<\n");
		return 0;
        }
#endif
        char *token1, *token2;
        char *command = strdup(input);

        token1 = strtok(command, " ");
	if (token1[0] == '\n') {
		printf(">>Ввод пуст, введите [тип хэша] и [имя файла или строку]<<\n");
		continue;
	}
	for(int i = 0; token1[i]; i++){
	 	token1[i] = tolower(token1[i]);
	}
	token2 = strtok(NULL, " ");
	if (!token2) {
		printf(">>Вы не задали второй аргумент: имя файла или строку<<\n");
		continue;
	}
	char *data;
	if (token2[0] == '"') {
		data = token2 + 1;
		data[strlen(data) - 1] = '\0';
	} else {
		token2[strlen(token2) - 1] = '\0';
		FILE *file = fopen(token2, "rb");
                if (!file) {
                        printf(">>Ошибка открытия файла %s<<\n", token2);
                	continue;
		}

                fseek(file, 0, SEEK_END);
                long filesize = ftell(file);
                fseek(file, 0, SEEK_SET);

                data = malloc(filesize + 1);
                fread((void *)data, filesize, 1, file);
                fclose(file);
		data[strlen(data) - 1] = '\0';
	}
	printf("data >%s<\n", data);
	
	rhash context;
   	char digest[64];
  	char output[130];
   	rhash_library_init();
	int res = -1;
	if (strcmp(token1, "sha1") == 0) {
		res = rhash_msg(RHASH_SHA1, data, strlen(token2), digest);
	} else if (strcmp(token1, "tth") == 0) {
		res = rhash_msg(RHASH_TTH, data, strlen(token2), digest);
	} else if (strcmp(token1, "md5") == 0) {
		res = rhash_msg(RHASH_MD5, data, strlen(token2), digest);
	}

	if (res < 0) {
		printf("\n>>Первый аргумент должен быть типом хэша, попробуйте SHA1, MD5, TTH<<\n");
		continue;
	}
	
	if (strcmp(token1, "sha1") == 0) {
		rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_SHA1), (RHPR_HEX | RHPR_UPPERCASE));
	} else if (strcmp(token1, "tth") == 0) {
		rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_TTH), (RHPR_HEX | RHPR_UPPERCASE));
	} else if (strcmp(token1, "md5") == 0) {
		rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_MD5), (RHPR_HEX | RHPR_UPPERCASE));
	}
	printf("%s\n", output); 

   }    
   return 0;
 }
