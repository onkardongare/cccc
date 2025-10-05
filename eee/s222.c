#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define MAX_GANTT 100

int main() {
    int n, i, current_time = 0, completed = 0;
    char pname[MAX][10];
    int at[MAX], bt[MAX], pr[MAX];   
    int rt[MAX];                     
    int ct[MAX], tat[MAX], wt[MAX];
    int is_completed[MAX] = {0};

    char gantt_proc[MAX_GANTT][10];  
    int gantt_time[MAX_GANTT];         
    int gantt_count = 0;

    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter process name, arrival time, burst time and priority for process %d: ", i + 1);
        scanf("%s %d %d %d", pname[i], &at[i], &bt[i], &pr[i]);
        rt[i] = bt[i];
    }

    int prev = -1;

    while (completed < n) {
        int idx = -1;
        int best_pr = 9999;

        for (i = 0; i < n; i++) {
            if (at[i] <= current_time && rt[i] > 0) {
                if (pr[i] < best_pr) {
                    best_pr = pr[i];
                    idx = i;
                } else if (pr[i] == best_pr) {
                    if (at[i] < at[idx]) idx = i;
                }
            }
        }

        if (idx != -1) {
            if (prev != idx) {
                strcpy(gantt_proc[gantt_count], pname[idx]);
                gantt_time[gantt_count] = current_time;
                gantt_count++;
                prev = idx;
            }

            rt[idx]--;        
            current_time++;

            if (rt[idx] == 0) {
                ct[idx] = current_time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                avg_tat += tat[idx];
                avg_wt += wt[idx];
                is_completed[idx] = 1;
                completed++;
            }
        } else {
            if (prev != -2) {
                strcpy(gantt_proc[gantt_count], "idle");
                gantt_time[gantt_count] = current_time;
                gantt_count++;
                prev = -2;
            }
            current_time++;
        }
    }

    gantt_time[gantt_count] = current_time;

    printf("\nGantt Chart:\n");
    for (i = 0; i < gantt_count; i++) {
        printf("| %s ", gantt_proc[i]);
    }
    printf("|\n");

    for (i = 0; i <= gantt_count; i++) {
        printf("%-5d", gantt_time[i]);
    }
    printf("\n");

    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pname[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);

    return 0;
}
