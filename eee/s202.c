#include <stdio.h>
#include <string.h>

#define MAX 10

int main() {
    int n, i, time = 0, done = 0;
    char pname[MAX][10];
    int at[MAX], bt[MAX], rt[MAX], ct[MAX], tat[MAX], wt[MAX];
    float avg_tat = 0, avg_wt = 0;
    char gantt[100][10]; int gtime[100], g = 0, prev = -1;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter name, arrival time, burst time for process %d: ", i+1);
        scanf("%s %d %d", pname[i], &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    while(done < n) {
        int idx = -1, min = 9999;
        for(i = 0; i < n; i++)
            if(at[i] <= time && rt[i] > 0 && rt[i] < min)
                min = rt[i], idx = i;

        if(idx != -1) {
            if(prev != idx) { strcpy(gantt[g], pname[idx]); gtime[g++] = time; prev = idx; }
            rt[idx]--; time++;
            if(rt[idx] == 0) {
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                avg_tat += tat[idx];
                avg_wt += wt[idx];
                done++;
            }
        } else { // CPU idle
            if(prev != -2) { strcpy(gantt[g], "idle"); gtime[g++] = time; prev = -2; }
            time++;
        }
    }
    gtime[g] = time;

    // Gantt chart
    printf("\nGantt Chart:\n");
    for(i = 0; i < g; i++) printf("| %s ", gantt[i]);
    printf("|\n");
    for(i = 0; i <= g; i++) printf("%-5d", gtime[i]);
    printf("\n");

    // Results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", pname[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAverage Turnaround Time: %.2f", avg_tat/n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt/n);
}
