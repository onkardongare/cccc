#include <stdio.h>
#include <string.h>

#define MAX 10

int main() {
    int n, i, current_time = 0, completed = 0;
    char pname[MAX][10];
    int at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX];
    int is_completed[MAX] = {0};
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter process name, arrival time, and burst time for process %d: ", i+1);
        scanf("%s %d %d", pname[i], &at[i], &bt[i]);
    }

    printf("\nGantt Chart:\n");
    printf("%d", current_time);

    while(completed < n) {
        int idx = -1, min_bt = 9999;

        // Find shortest job among arrived processes
        for(i = 0; i < n; i++) {
            if(at[i] <= current_time && !is_completed[i]) {
                if(bt[i] < min_bt) {
                    min_bt = bt[i];
                    idx = i;
                } else if(bt[i] == min_bt && at[i] < at[idx]) {
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            // Execute process
            current_time += bt[idx];
            ct[idx] = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            avg_tat += tat[idx];
            avg_wt += wt[idx];
            is_completed[idx] = 1;
            completed++;

            printf(" | %s | %d", pname[idx], current_time);
        } else {
            // CPU idle
            current_time++;
            printf(" | idle | %d", current_time);
        }
    }

    // Print results
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               pname[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);

    return 0;
}
