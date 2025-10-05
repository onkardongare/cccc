#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    pid = fork();  // Create child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    // Child Process
    else if (pid == 0) {
        printf("Child Process Started...\n");
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        
        // Child sleeps longer than parent
        sleep(5);

        printf("\nAfter Parent Ends:\n");
        printf("Child PID: %d, New Parent PID (Adopted by init): %d\n", getpid(), getppid());
        printf("Child Process Ends.\n");
    }

    // Parent Process
    else {
        printf("Parent Process Started...\n");
        printf("Parent PID: %d, Child PID: %d\n", getpid(), pid);
        
        // Parent sleeps briefly, then ends
        sleep(2);
        printf("Parent Process Ends.\n");
    }

    return 0;
}
