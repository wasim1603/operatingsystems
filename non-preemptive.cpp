#include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int executed;
};

void calculateTurnaroundTime(struct Process processes[], int n) {
    for (int i = 0; i < n; ++i) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    }
}

void calculateWaitingTime(struct Process processes[], int n) {
    for (int i = 0; i < n; ++i) {
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

void SJF(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    while (completed < n) {
        int shortestBurst = 9999;
        int shortestIndex = -1;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= currentTime && processes[i].executed == 0) {
                if (processes[i].burst_time < shortestBurst) {
                    shortestBurst = processes[i].burst_time;
                    shortestIndex = i;
                }
            }
        }

        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        processes[shortestIndex].completion_time = currentTime + processes[shortestIndex].burst_time;
        currentTime = processes[shortestIndex].completion_time;
        processes[shortestIndex].executed = 1;
        completed++;
    }

    calculateTurnaroundTime(processes, n);
    calculateWaitingTime(processes, n);

    printf("Process\t Arrival Time\t Burst Time\t Turnaround Time\t Waiting Time\n");

    for (int i = 0; i < n; ++i) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t\t %d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time);

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; ++i) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].executed = 0;
    }

    SJF(processes, n);

    return 0;
}

