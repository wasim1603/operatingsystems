#include <stdio.h>

struct Process {
    int process_id;
    int burst_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
};

void roundRobin(struct Process processes[], int n, int time_slice) {
    int remaining_processes = n;
    int currentTime = 0;

    while (remaining_processes > 0) {
        for (int i = 0; i < n; ++i) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > time_slice) {
                    currentTime += time_slice;
                    processes[i].remaining_time -= time_slice;
                } else {
                    currentTime += processes[i].remaining_time;
                    processes[i].turnaround_time = currentTime;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    remaining_processes--;
                }
            }
        }
    }

    float total_waiting_time = 0, total_turnaround_time = 0;

    printf("Process\t Burst Time\t Turnaround Time\t Waiting Time\n");

    for (int i = 0; i < n; ++i) {
        printf("%d\t\t %d\t\t %d\t\t\t %d\n", processes[i].process_id, processes[i].burst_time,
               processes[i].turnaround_time, processes[i].waiting_time);

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n, time_slice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; ++i) {
        processes[i].process_id = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    printf("Enter the time slice for Round Robin: ");
    scanf("%d", &time_slice);

    roundRobin(processes, n, time_slice);

    return 0;
}

