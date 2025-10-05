#include <stdio.h>

int findLRU(int time[], int n) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int frames, temp[10], time[10];
    int n, i, j, pos, faults = 0, counter = 0, flag1, flag2;
    
    // Reference string (given in question)
    int ref[] = {3,4,5,4,3,4,7,2,4,5,6,7,2,4,6};
    n = sizeof(ref) / sizeof(ref[0]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for(i = 0; i < frames; ++i)
        temp[i] = -1;

    printf("\nReference String: ");
    for(i = 0; i < n; i++) {
        printf("%d ", ref[i]);
    }
    printf("\n\n");

    for(i = 0; i < n; ++i) {
        flag1 = flag2 = 0;

        for(j = 0; j < frames; ++j) {
            if(temp[j] == ref[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if(flag1 == 0) {
            for(j = 0; j < frames; ++j) {
                if(temp[j] == -1) {
                    faults++;
                    temp[j] = ref[i];
                    counter++;
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if(flag2 == 0) {
            pos = findLRU(time, frames);
            faults++;
            temp[pos] = ref[i];
            counter++;
            time[pos] = counter;
        }

        printf("Step %2d -> ", i+1);
        for(j = 0; j < frames; ++j) {
            if(temp[j] != -1)
                printf("%d ", temp[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
