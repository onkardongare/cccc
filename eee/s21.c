#include <stdio.h>

int main() {
    int frames, temp[10];
    int n, i, j, k, pos = 0, faults = 0;

    // Reference string (given in question)
    int ref[] = {3,4,5,6,3,4,7,3,4,5,6,7,2,4,6};
    n = sizeof(ref) / sizeof(ref[0]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    // Initialize all frames as empty
    for(i = 0; i < frames; ++i)
        temp[i] = -1;

    printf("\nReference String: ");
    for(i = 0; i < n; i++) {
        printf("%d ", ref[i]);
    }
    printf("\n\n");

    // Main loop for each page in reference string
    for(i = 0; i < n; ++i) {
        int page = ref[i];
        int flag = 0;

        // Check if page already in frames (hit)
        for(j = 0; j < frames; ++j) {
            if(temp[j] == page) {
                flag = 1;
                break;
            }
        }

        // If page not found → Page Fault
        if(flag == 0) {
            temp[pos] = page;         // Replace at FIFO position
            pos = (pos + 1) % frames; // Move pointer to next frame (circular)
            faults++;
        }

        // Print current frame status
        printf("Step %2d -> ", i+1);
        for(k = 0; k < frames; ++k) {
            if(temp[k] != -1)
                printf("%d ", temp[k]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
