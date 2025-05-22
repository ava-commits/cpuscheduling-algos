#include <stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void findCompletionTime(Process proc[], int n) {
    int current_time = 0;
    printf("\nGantt Chart Progress:\n");
    printf("0");  // start time
    
    for (int i = 0; i < n; i++) {
        if (current_time < proc[i].arrival_time) {
            current_time = proc[i].arrival_time;
        }
        proc[i].completion_time = current_time + proc[i].burst_time;
        current_time = proc[i].completion_time;
        printf(" -- P%d -- %d", proc[i].pid, proc[i].completion_time);
    }
    printf("\n");
}

void findTurnaroundAndWaitingTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
    }
}

void printProcessTable(Process proc[], int n) {
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
            proc[i].pid, proc[i].arrival_time, proc[i].burst_time, 
            proc[i].completion_time, proc[i].turnaround_time, proc[i].waiting_time);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process proc[n];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Process %d: ", proc[i].pid);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
    }
    
    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival_time > proc[j + 1].arrival_time) {
                Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
    
    findCompletionTime(proc, n);
    findTurnaroundAndWaitingTime(proc, n);
    printProcessTable(proc, n);
    
    return 0;
}

OUTPUT : Enter number of processes: 4
Enter Arrival Time and Burst Time for each process:
Process 1: 0 5
Process 2: 1 3
Process 3: 2 8
Process 4: 3 6

Gantt Chart Progress:
0 -- P1 -- 5 -- P2 -- 8 -- P3 -- 16 -- P4 -- 22

Process	AT	BT	CT	TAT	WT
P1	0	5	5	5	0
P2	1	3	8	7	4
P3	2	8	16	14	6
P4	3	6	22	19	13