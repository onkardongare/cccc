#include <stdio.h>
#include <string.h>

#define MAX 10

int main() {
    int n, i, current_time = 0, completed = 0;
    char pname[MAX][10];
    int at[MAX], bt[MAX], pr[MAX];   // arrival, burst, priority
    int ct[MAX], tat[MAX], wt[MAX];
    int is_completed[MAX] = {0};
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter process name, arrival time, burst time and priority for process %d: ", i+1);
        scanf("%s %d %d %d", pname[i], &at[i], &bt[i], &pr[i]);
    }

    printf("\nGantt Chart:\n");
    printf("%d", current_time);

    while(completed < n) {
        int idx = -1, best_pr = 9999;

        // Find highest priority process that has arrived
        for(i = 0; i < n; i++) {
            if(at[i] <= current_time && !is_completed[i]) {
                if(pr[i] < best_pr) {
                    best_pr = pr[i];
                    idx = i;
                } else if(pr[i] == best_pr && at[i] < at[idx]) {
                    idx = i;  // tie-breaker: earlier arrival
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
    printf("\n\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pname[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);

    return 0;
}
