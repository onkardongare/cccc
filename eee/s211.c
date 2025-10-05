#include <stdio.h>
#include <unistd.h>   // for fork(), getpid(), getppid()
#include <sys/types.h> // for pid_t

int main() {
    pid_t pid;   // process ID type variable

    // create a new process
    pid = fork();

    // check if fork() succeeded
    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }

    // Child process block
    else if (pid == 0) {
        printf("I am Child Process.\n");
        printf("Child PID: %d\n", getpid());     // get process ID
        printf("Parent PID: %d\n", getppid());   // get parent process ID
    }

    // Parent process block
    else {
        printf("I am Parent Process.\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
    }

    return 0;
}