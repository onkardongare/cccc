#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

#define MAX 100

int main() {
    char line[MAX], *args[20];
    int i;

    while(1) {
        printf("myshell$ ");   // Shell prompt
        // fflush(stdout);

        fgets(line, MAX, stdin);

        // Remove trailing newline
        line[strcspn(line, "\n")] = '\0';

        if (strlen(input) == 0) continue;

        // Tokenize command
        i = 0;
        args[i] = strtok(line, " ");
        while(args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        if(args[0] == NULL) {
            continue; // empty input
        }

        // --------- Handle "exit" ----------
        if(strcmp(args[0], "exit") == 0) {
            break;
        }

        // --------- Handle "list" command ----------
        if(strcmp(args[0], "list") == 0) {
            if(args[1] == NULL || args[2] == NULL) {
                printf("Usage: list f dirname OR list n dirname\n");
                continue;
            }

            DIR *dir;
            struct dirent *entry;
            int count = 0;

            dir = opendir(args[2]);
            if(dir == NULL) {
                perror("opendir");
                continue;
            }

            if(strcmp(args[1], "f") == 0) {
                // Print names of all files
                while((entry = readdir(dir)) != NULL) {
                    printf("%s\n", entry->d_name);
                }
            }
            else if(strcmp(args[1], "n") == 0) {
                // Count number of entries
                while((entry = readdir(dir)) != NULL) {
                    count++;
                }
                printf("Number of entries = %d\n", count);
            }
            else {
                printf("Invalid option. Use f or n.\n");
            }

            closedir(dir);
            continue;
        }

        // --------- Other commands ----------
        pid_t pid = fork();
        if(pid == 0) {
            // Child process
            if(execvp(args[0], args) == -1) {
                perror("execvp");
            }
            exit(0);
        }
        else if(pid > 0) {
            // Parent waits
            wait(NULL);
        }
        else {
            perror("fork");
        }
    }

    return 0;
}
