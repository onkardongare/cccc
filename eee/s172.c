#include <stdio.h>
#include <string.h>

#define MAX 10

int main() {
    int n, i, j;
    char pname[MAX][10];
    int at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX];
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter process name, arrival time, and burst time for process %d: ", i+1);
        scanf("%s %d %d", pname[i], &at[i], &bt[i]);
    }

    // Sort by Arrival Time
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(at[i] > at[j]) {
                int t = at[i]; at[i] = at[j]; at[j] = t;
                t = bt[i]; bt[i] = bt[j]; bt[j] = t;
                char name[10]; strcpy(name, pname[i]);
                strcpy(pname[i], pname[j]);
                strcpy(pname[j], name);
            }
        }
    }

    int time = 0;
    printf("\nGantt Chart:\n");

    for(i = 0; i < n; i++) {
        if(time < at[i]) {       // CPU idle
            printf("%d | idle | %d ", time, at[i]);
            time = at[i];
        }
        printf("| %s |", pname[i]);
        time += bt[i];
        ct[i] = time;
    }
    printf("%d\n", time);

    // Calculate TAT and WT
    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", pname[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);

    return 0;
}
