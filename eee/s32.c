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

        // ---------- Handle "count" command ----------
        if(strcmp(args[0], "count") == 0) {
            if(args[1] == NULL || args[2] == NULL) {
                printf("Usage: count [c|w|l] filename\n");
                continue;
            }

            FILE *fp = fopen(args[2], "r");
            if(fp == NULL) {
                perror("fopen");
                continue;
            }

            int ch, lines = 0, words = 0, chars = 0;
            int in_word = 0;

            while((ch = fgetc(fp)) != EOF) {
                chars++;

                if(ch == '\n')
                    lines++;

                if(ch == ' ' || ch == '\n' || ch == '\t')
                    in_word = 0;
                else if(in_word == 0) {
                    in_word = 1;
                    words++;
                }
            }
            fclose(fp);

            if(strcmp(args[1], "c") == 0)
                printf("Characters: %d\n", chars);
            else if(strcmp(args[1], "w") == 0)
                printf("Words: %d\n", words);
            else if(strcmp(args[1], "l") == 0)
                printf("Lines: %d\n", lines);
            else
                printf("Invalid option. Use c, w or l.\n");

            continue;
        }

        // ---------- For other system commands ----------
        pid_t pid = fork();
        if(pid == 0) {
            // Child process
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
