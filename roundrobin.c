4. Round Robin

#include<stdio.h>
void roundRobin(int n, int at[], int bt[], int quantum) {
    int ft[n], tt[n], wt[n], remaining_bt[n];
    int time = 0, completed = 0;

    // Copy burst time to remaining time array
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
    }

    printf("\nGantt Chart:\n");
    printf("--------------------------------------\n");
    printf("|");

    while (completed < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0 && at[i] <= time) {
                printf(" P%d %2d |", i + 1, time);
                executed = 1;

                if (remaining_bt[i] > quantum) {
                    time = time + quantum;
                    remaining_bt[i] = remaining_bt[i] - quantum;
                } else {
                    time = time + remaining_bt[i];
                    ft[i] = time;
                    tt[i] = ft[i] - at[i];
                    wt[i] = tt[i] - bt[i];
                    remaining_bt[i] = 0;
                    completed = completed + 1;
                }
            }
        }
        if (executed == 0) {
            time = time + 1; // Increment time if no process is ready
        }
    }

    printf(" %2d |\n", time);
    printf("--------------------------------------\n");

    // Printing Process Table
    printf("\nProcess Table:\n");
    printf("------------------------------------------------\n");
    printf("| P# | AT  | BT  |  FT  |  TT  |  WT  |\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d  | %2d  | %2d  | %2d  | %2d  | %2d  |\n",
               i + 1, at[i], bt[i], ft[i], tt[i], wt[i]);
    }
    printf("------------------------------------------------\n");
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
   
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int at[n], bt[n];
    printf("Enter Arrival Time (AT) and Burst Time (BT) for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    roundRobin(n, at, bt, quantum);
    return 0;
}

output :

Enter number of processes: 4
Enter time quantum: 2
Enter Arrival Time (AT) and Burst Time (BT) for each process:
Process 1: 1 4
Process 2: 2 5
Process 3: 3 6
Process 4: 4 1

Gantt Chart:
--------------------------------------
| P1  1 | P2  3 | P3  5 | P4  7 | P1  8 | P2 10 | P3 12 | P2 14 | P3 15 | 17 |
--------------------------------------

Process Table:
------------------------------------------------
| P# | AT  | BT  |  FT  |  TT  |  WT  |
------------------------------------------------
| P1  |  1  |  4  | 10  |  9  |  5  |
| P2  |  2  |  5  | 15  | 13  |  8  |
| P3  |  3  |  6  | 17  | 14  |  8  |
| P4  |  4  |  1  |  8  |  4  |  3  |
------------------------------------------------