#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80
#define MAX_ARGS 10

int main() {

    while (1)
    {
        char input[MAX_LINE];
        char *token;
        char *argv[MAX_ARGS];
        // prompt
        printf("myshell> ");

        // read command
        fgets(input, MAX_LINE, stdin);

        // tokenize input
        token = strtok(input, " \n\t");
        int i = 0;
        while (token != NULL) {
            argv[i++] = token;
            token = strtok(input, " \n\t");
        }
        argv[i] = NULL;

        if (argv[0] == NULL) {  // empty command
            continue;
        }

        if (strcmp(argv[0], "exit") == 0) {
            printf("Goodbye\n");
            exit(0);
        }
    }
    

    return 0;
}