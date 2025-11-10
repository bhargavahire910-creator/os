#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct Process {
    int pid;
    int at; // Arrival Time
    int bt; // Burst Time
    int rt; // Remaining Time
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

int main() {
    int n;
    float avg_wt = 0, avg_tat = 0;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1) return 1;

    struct Process p[n];
    int completed = 0;
    int current_time = 0;
    int min_rt_idx = -1;
    int min_rt = INT_MAX;
    bool is_process_executing = false;

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("\nProcess Execution Order:\n");

    // Main simulation loop (continues until all processes are completed)
    while (completed != n) {
        min_rt_idx = -1;
        min_rt = INT_MAX;

        // Find process with minimum remaining time among those that have arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                if (p[i].rt < min_rt) {
                    min_rt = p[i].rt;
                    min_rt_idx = i;
                }
                // Tie-breaker: if remaining time is same, choose the one that arrived earlier
                if (p[i].rt == min_rt) {
                    if (p[i].at < p[min_rt_idx].at) {
                        min_rt_idx = i;
                    }
                }
            }
        }

        if (min_rt_idx != -1) {
            // Execute the found process for 1 unit of time
            if (!is_process_executing || min_rt_idx != (min_rt_idx)) {
                 // Just for visualization if needed, though it prints every second
                 // printf("T%d: P%d\n", current_time, p[min_rt_idx].pid);
            }
            
            p[min_rt_idx].rt--;
            current_time++;
            is_process_executing = true;

            // If process is finished
            if (p[min_rt_idx].rt == 0) {
                completed++;
                is_process_executing = false;
                p[min_rt_idx].ct = current_time;
                p[min_rt_idx].tat = p[min_rt_idx].ct - p[min_rt_idx].at;
                p[min_rt_idx].wt = p[min_rt_idx].tat - p[min_rt_idx].bt;

                avg_tat += p[min_rt_idx].tat;
                avg_wt += p[min_rt_idx].wt;
            }
        } else {
            // No process has arrived yet, CPU is idle
            current_time++;
        }
    }

    // Print Table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
            p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time: %f", avg_wt / n);
    printf("\nAverage Turnaround Time: %f", avg_tat / n);

    return 0;
}
