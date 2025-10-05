#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100

// Bubble Sort function (Parent)
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for(i = 0; i < n-1; i++) {
        for(j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Insertion Sort function (Child)
void insertionSort(int arr[], int n) {
    int i, key, j;
    for(i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main() {
    int n, arr[MAX], i;
    pid_t pid;

    printf("Enter number of integers: ");
    scanf("%d", &n);

    printf("Enter %d integers: ", n);
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pid = fork();  // Create a child process

    if(pid < 0) {
        perror("Fork failed");
        return 1;
    }

    // Child Process
    else if(pid == 0) {
        printf("\nChild Process (PID: %d)\n", getpid());
        insertionSort(arr, n);
        printf("Sorted array using Insertion Sort:\n");
        for(i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }

    // Parent Process
    else {
        wait(NULL);  // Wait for child to finish
        printf("\nParent Process (PID: %d)\n", getpid());
        bubbleSort(arr, n);
        printf("Sorted array using Bubble Sort:\n");
        for(i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }

    return 0;
}
