3.1 Priority (Preemptive)

#include <stdio.h>

typedef struct {
    int pid, arrival_time, burst_time, remaining_time, priority, completion_time, turnaround_time, waiting_time;
} Process;

void findCompletionTime(Process proc[], int n, int timeline[], int *timeline_size) {
    int completed = 0, current_time = 0, min_idx;
    int is_completed[n];

    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
        proc[i].remaining_time = proc[i].burst_time;
    }

    while (completed < n) {
        min_idx = -1;
        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && proc[i].arrival_time <= current_time) {
                if (min_idx == -1 || proc[i].priority < proc[min_idx].priority) {
                    min_idx = i;
                }
            }
        }

        if (min_idx == -1) {
            current_time++;
        } else {
            timeline[(*timeline_size)++] = proc[min_idx].pid;
            proc[min_idx].remaining_time--;
            current_time++;

            if (proc[min_idx].remaining_time == 0) {
                proc[min_idx].completion_time = current_time;
                proc[min_idx].turnaround_time = proc[min_idx].completion_time - proc[min_idx].arrival_time;
                proc[min_idx].waiting_time = proc[min_idx].turnaround_time - proc[min_idx].burst_time;
                is_completed[min_idx] = 1;
                completed++;
            }
        }
    }
}

void printGanttChart(int timeline[], int timeline_size) {
    printf("\nGantt Chart:\n ");
    
    for (int i = 0; i < timeline_size; i++) {
        if (i == 0 || timeline[i] != timeline[i - 1]) {
            printf("| P%d ", timeline[i]);
        }
    }
    printf("|\n0");
    
    for (int i = 0; i < timeline_size; i++) {
        if (i == 0 || timeline[i] != timeline[i - 1]) {
            printf("    %d", i + 1);
        }
    }
    printf("\n");
}

void printProcessDetails(Process proc[], int n) {
    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, proc[i].priority, proc[i].completion_time, proc[i].turnaround_time, proc[i].waiting_time);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    printf("Enter Arrival Time, Burst Time, and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
    }

    int timeline[100], timeline_size = 0;
    findCompletionTime(proc, n, timeline, &timeline_size);
    printProcessDetails(proc, n);
    printGanttChart(timeline, timeline_size);
    
    return 0;
}


output ; 

Enter number of processes: 5
Enter Arrival Time, Burst Time, and Priority for each process:
Process 1: 1 2 3
Process 2: 2 3 4
Process 3: 3 4 5
Process 4: 5 6 7
Process 5: 6 7 8

Process	AT	BT	Priority	CT	TAT	WT
1	1	2	3		3	2	0
2	2	3	4		6	4	1
3	3	4	5		10	7	3
4	5	6	7		16	11	5
5	6	7	8		23	17	10

Gantt Chart:
 | P1 | P2 | P3 | P4 | P5 |
0    1    3    6    10    16
















3.2 Priority (Non-preemptive):

#include <stdio.h>

typedef struct {
    int pid, arrival_time, burst_time, priority, completion_time, turnaround_time, waiting_time;
} Process;

void findCompletionTime(Process proc[], int n) {
    int completed = 0, current_time = 0, min_idx;
    int is_completed[n];

    for (int i = 0; i < n; i++) is_completed[i] = 0;

    while (completed < n) {
        min_idx = -1;
        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && proc[i].arrival_time <= current_time) {
                if (min_idx == -1 || proc[i].priority < proc[min_idx].priority) {
                    min_idx = i;
                }
            }
        }

        if (min_idx == -1) {
            current_time++;
        } else {
            proc[min_idx].completion_time = current_time + proc[min_idx].burst_time;
            proc[min_idx].turnaround_time = proc[min_idx].completion_time - proc[min_idx].arrival_time;
            proc[min_idx].waiting_time = proc[min_idx].turnaround_time - proc[min_idx].burst_time;
            current_time = proc[min_idx].completion_time;
            is_completed[min_idx] = 1;
            completed++;
        }
    }
}

void printGanttChart(Process proc[], int n) {
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < n; i++) printf("| P%d ", proc[i].pid);
    printf("|\n0");
    for (int i = 0; i < n; i++) printf("    %d", proc[i].completion_time);
    printf("\n");
}

void printProcessDetails(Process proc[], int n) {
    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, proc[i].priority, proc[i].completion_time, proc[i].turnaround_time, proc[i].waiting_time);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    printf("Enter Arrival Time, Burst Time, and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
    }

    findCompletionTime(proc, n);
    printProcessDetails(proc, n);
    printGanttChart(proc, n);
    
    return 0;
}

 
output

Enter number of processes: 4
Enter Arrival Time, Burst Time, and Priority for each process:
Process 1: 1 4 5
Process 2: 2 3 4
Process 3: 5 6 8
Process 4: 1 3 4

Process	AT	BT	Priority	CT	TAT	WT
1	1	4	5		11	10	6
2	2	3	4		7	5	2
3	5	6	8		17	12	6
4	1	3	4		4	3	0

Gantt Chart:
 | P1 | P2 | P3 | P4 |
0    11    7    17    4
