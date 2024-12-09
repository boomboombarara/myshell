#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "ls_command.h"

#define MAX_LINE 80
#define MAX_PRGR 300
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
        token = strtok(input, " \n");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            argv[i++] = token;
            token = strtok(NULL, " \n");
        }
        argv[i] = NULL;

        if (argv[0] == NULL) {  // empty command
            continue;
        }

        if (strcmp(argv[0], "exit") == 0) {
            printf("Goodbye\n");
            exit(0);
        } else if (strcmp(argv[0], "cd") == 0) {
            chdir(argv[1]);
        } else if (strcmp(argv[0], "pwd") == 0) {
            getcwd(input, MAX_LINE);
            printf("%s\n", input);
        } else if (strcmp(argv[0], "ls") == 0) {
            my_ls();
        } else if (strcmp(argv[0], "cat") == 0) {
            FILE *file = fopen(argv[1], "r");
            if (file == NULL) {  // 파일 열기에 실패한 경우
                perror("cat");
                continue;
            }


            char line[MAX_PRGR];

            while (fgets(line, MAX_LINE, file) != NULL) {
                printf("%s", line);  // 읽은 한 줄을 출력합니다.
            }
            fclose(file);
            printf("\n");

        } else {
            if (access(argv[0], X_OK) == 0) {
                pid_t pid = fork();
                if (pid == 0) { // child process
                    execvp(argv[0], argv);
                    perror("execvp");
                    exit(EXIT_FAILURE);
                } else if (pid > 0) { // parent process
                    int status;
                    waitpid(pid, &status, 0);
                } else {
                    perror("fork");
                }
            } else {
                fprintf(stderr, "command not found: %s\n", argv[0]);
            }
        }
    }
    

    return 0;
}