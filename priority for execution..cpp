#include <stdio.h>

struct Process {
    int process_id;
    int burst_time;
    int priority;
    int remaining_time;
    int arrival_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int findHighestPriority(struct Process processes[], int n, int currentTime) {
    int highestPriority = -1;
    int highestIndex = -1;

    for (int i = 0; i < n; ++i) {
        if (processes[i].arrival_time <= currentTime && processes[i].remaining_time > 0) {
            if (highestPriority == -1 || processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                highestIndex = i;
            }
        }
    }

    return highestIndex;
}

void priorityScheduling(struct Process processes[], int n) {
    int completed = 0;
    int currentTime = 0;
    int prevProcess = -1;
    float total_waiting_time = 0, total_turnaround_time = 0;

    while (completed < n) {
        int currentProcess = findHighestPriority(processes, n, currentTime);

        if (currentProcess == -1) {
            currentTime++;
            continue;
        }

        if (prevProcess != currentProcess) {
            processes[currentProcess].waiting_time += currentTime - processes[currentProcess].arrival_time;
        }

        processes[currentProcess].remaining_time--;

        currentTime++;

        if (processes[currentProcess].remaining_time == 0) {
            processes[currentProcess].completion_time = currentTime;
            processes[currentProcess].turnaround_time = processes[currentProcess].completion_time - processes[currentProcess].arrival_time;
            processes[currentProcess].waiting_time = processes[currentProcess].turnaround_time - processes[currentProcess].burst_time;

            total_waiting_time += processes[currentProcess].waiting_time;
            total_turnaround_time += processes[currentProcess].turnaround_time;

            completed++;
        }

        prevProcess = currentProcess;
    }

    printf("Process\t Arrival Time\t Burst Time\t Priority\t Turnaround Time\t Waiting Time\n");

    for (int i = 0; i < n; ++i) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\t\t\t %d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority, processes[i].turnaround_time, processes[i].waiting_time);
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
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    priorityScheduling(processes, n);

    return 0;
}

