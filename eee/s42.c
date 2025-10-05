#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 100

int main() {
    char line[MAX], *args[20];
    int i;

    while(1) {
        printf("myshell$ ");
        fflush(stdout);

        if(fgets(line, MAX, stdin) == NULL)
            break; // Exit on Ctrl+D

        // Remove newline
        line[strcspn(line, "\n")] = '\0';

        // Tokenize command line
        i = 0;
        args[i] = strtok(line, " ");
        while(args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        if(args[0] == NULL)
            continue; // Empty input

        // Exit command
        if(strcmp(args[0], "exit") == 0)
            break;

        // ---------- Handle "search" command ----------
        if(strcmp(args[0], "search") == 0) {
            FILE *fp;
            char buffer[256];
            int count = 0;

            // Case 1: search filename pattern
            if(args[1] != NULL && args[2] != NULL && args[3] == NULL) {
                fp = fopen(args[1], "r");
                if(fp == NULL) {
                    perror("fopen");
                    continue;
                }

                int lineNo = 1;
                while(fgets(buffer, sizeof(buffer), fp)) {
                    if(strstr(buffer, args[2])) {
                        printf("Line %d: %s", lineNo, buffer);
                    }
                    lineNo++;
                }
                fclose(fp);
                continue;
            }

            // Case 2: search c filename pattern
            else if(args[1] != NULL && strcmp(args[1], "c") == 0 && args[2] != NULL && args[3] != NULL) {
                fp = fopen(args[2], "r");
                if(fp == NULL) {
                    perror("fopen");
                    continue;
                }

                while(fgets(buffer, sizeof(buffer), fp)) {
                    for(i = 0; i < strlen(buffer); i++) {
                        if(strncmp(&buffer[i], args[3], strlen(args[3])) == 0)
                            count++;
                    }
                }
                fclose(fp);
                printf("Total occurrences of '%s' = %d\n", args[3], count);
                continue;
            }

            else {
                printf("Usage:\n");
                printf(" search filename pattern\n");
                printf(" search c filename pattern\n");
                continue;
            }
        }

        // ---------- For other system commands ----------
        pid_t pid = fork();
        if(pid == 0) {
            // Child process executes command
            if(execvp(args[0], args) == -1) {
                perror("execvp");
            }
            exit(0);
        }
        else if(pid > 0) {
            wait(NULL); // Parent waits for child
        }
        else {
            perror("fork");
        }
    }

    return 0;
}
