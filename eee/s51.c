#include <stdio.h>

int findOptimal(int pages[], int temp[], int n, int index, int frames) {
    int i, j, farthest = index, pos = -1, found;
    for(i = 0; i < frames; i++) {
        found = 0;
        for(j = index; j < n; j++) {
            if(temp[i] == pages[j]) {
                if(j > farthest){
                    farthest = j;
                    pos = i;
                }
                found = 1;
                break;
            }
        }
        // If a page will never be used again
        if(found == 0)
            return i;
    }
    if(pos == -1)
        return 0;  // default
    else
        return pos;
}

int main() {
    int frames, n, i, j, k, pos, faults = 0;
    int temp[10], pages[30];

    // Reference String (given)
    int ref[] = {8,5,7,8,5,7,2,3,7,3,5,9,4,6,2};
    n = sizeof(ref) / sizeof(ref[0]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for(i = 0; i < frames; i++)
        temp[i] = -1;

    printf("\nReference String: ");
    for(i = 0; i < n; i++) {
        printf("%d ", ref[i]);
    }
    printf("\n\n");

    for(i = 0; i < n; i++) {
        int page = ref[i];
        int found = 0;

        // Check if already present
        for(j = 0; j < frames; j++) {
            if(temp[j] == page) {
                found = 1;
                break;
            }
        }

        if(found == 0) {
            // If empty slot exists
            int done = 0;
            for(j = 0; j < frames; j++) {
                if(temp[j] == -1) {
                    temp[j] = page;
                    faults++;
                    done = 1;
                    break;
                }
            }

            // If no empty slot, replace using Optimal
            if(done == 0) {
                pos = findOptimal(ref, temp, n, i+1, frames);
                temp[pos] = page;
                faults++;
            }
        }

        // Print current frame status
        printf("Step %2d -> ", i+1);
        for(k = 0; k < frames; k++) {
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
