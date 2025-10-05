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

            // Case 1: search f filename pattern (first occurrence)
            if(args[1] != NULL && strcmp(args[1], "f") == 0 && args[2] != NULL && args[3] != NULL) {
                fp = fopen(args[2], "r");
                if(fp == NULL) {
                    perror("fopen");
                    continue;
                }

                int lineNo = 1;
                int found = 0;
                while(fgets(buffer, sizeof(buffer), fp)) {
                    if(strstr(buffer, args[3])) {
                        printf("First occurrence at line %d: %s", lineNo, buffer);
                        found = 1;
                        break; // Stop at first occurrence
                    }
                    lineNo++;
                }
                if(!found)
                    printf("Pattern '%s' not found in file %s.\n", args[3], args[2]);
                fclose(fp);
                continue;
            }

            // Case 2: search c filename pattern (count occurrences)
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
                printf(" search f filename pattern   # first occurrence\n");
                printf(" search c filename pattern   # count occurrences\n");
                continue;
            }
        }

        // ---------- Other system commands ----------
        pid_t pid = fork();
        if(pid == 0) {
            // Child process executes system command
            if(execvp(args[0], args) == -1) {
                perror("execvp");
            }
            exit(0);
        }
        else if(pid > 0) {
            wait(NULL); // Parent waits
        }
        else {
            perror("fork");
        }
    }

    return 0;
}
