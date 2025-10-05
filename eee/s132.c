#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

int main() {
    int n, i, tq;
    char pname[MAX][10];
    int at[MAX], bt[MAX], rt[MAX];   // arrival, burst, remaining burst
    int ct[MAX], tat[MAX], wt[MAX];
    int completed = 0, current_time = 0;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter process name, arrival time and CPU burst time for process %d: ", i+1);
        scanf("%s %d %d", pname[i], &at[i], &bt[i]);
        rt[i] = bt[i]; // initially remaining time = burst time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int done[n];       // to track completion
    for(i = 0; i < n; i++) done[i] = 0;

    printf("\nGantt Chart:\n");
    printf("%d", current_time);

    // Round Robin Scheduling
    while(completed < n) {
        int flag = 0; // check if some process runs in this cycle
        for(i = 0; i < n; i++) {
            if(rt[i] > 0 && at[i] <= current_time) {
                flag = 1;
                if(rt[i] > tq) {
                    printf(" | %s | %d", pname[i], current_time + tq);
                    current_time += tq;
                    rt[i] -= tq;
                } else {
                    printf(" | %s | %d", pname[i], current_time + rt[i]);
                    current_time += rt[i];
                    rt[i] = 0;
                    ct[i] = current_time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    avg_tat += tat[i];
                    avg_wt += wt[i];
                    done[i] = 1;
                    completed++;
                }
            }
        }
        if(flag == 0) {
            // CPU idle if no process has arrived yet
            current_time++;
            printf(" | idle | %d", current_time);
        }
    }

    // Print Results
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               pname[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time: %.2f", avg_tat);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);

    return 0;
}
