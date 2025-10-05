#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100

// Function for typeline
void typeline(char option[], char filename[]) {
    FILE *fp;
    char line[1024];
    int n, count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    if (option[0] == '+') {   // +n → print first n lines
        n = atoi(option + 1);
        while (fgets(line, sizeof(line), fp) != NULL && count < n) {
            printf("%s", line);
            count++;
        }
    }
    else if (strcmp(option, "-a") == 0) { // -a → print all lines
        while (fgets(line, sizeof(line), fp) != NULL) {
            printf("%s", line);
        }
    }
    else {
        printf("Invalid option!\n");
    }

    fclose(fp);
}

int main() {
    char input[MAX];
    char cmd[20], arg1[20], arg2[50];
    pid_t pid;

    while (1) {
        printf("myshell$ ");
        fgets(input, MAX, stdin);

        // remove newline
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) continue;

        // exit command
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // reset args
        cmd[0] = arg1[0] = arg2[0] = '\0';
        sscanf(input, "%s %s %s", cmd, arg1, arg2);

        // only allow typeline
        if (strcmp(cmd, "typeline") != 0) {
            printf("Only 'typeline' command is supported!\n");
            continue;
        }

        // fork child process to run typeline
        pid = fork();
        if (pid == 0) {   // child
            if (strlen(arg1) > 0 && strlen(arg2) > 0) {
                typeline(arg1, arg2);
            } else {
                printf("Usage: typeline +n filename OR typeline -a filename\n");
            }
            exit(0);
        }
        else if (pid > 0) {  // parent
            wait(NULL);
        }
        else {
            perror("Fork failed");
        }
    }

    return 0;
}
