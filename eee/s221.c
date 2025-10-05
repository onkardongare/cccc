#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

int main() {
    pid_t pid;

    pid = fork();  // Create child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("Child process before nice(), PID = %d\n", getpid());
        
        // Increase niceness (lower priority)
        int new_nice = nice(5);
        printf("Child process after nice(5): new nice value = %d\n", new_nice);

        // Simulate work
        for (int i = 0; i < 5; i++) {
            printf("Child working... (%d)\n", i + 1);
            sleep(1);
        }
    }
    else {
        // Parent process
        printf("Parent process, PID = %d\n", getpid());
        printf("Parent waiting for child...\n");

        wait(NULL);  // Wait for child to finish
        printf("Child finished. Parent exiting.\n");
    }

    return 0;
}
