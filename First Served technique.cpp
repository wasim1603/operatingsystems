#include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
};

void calculateWaitingTime(struct Process processes[], int n, int waiting_times[]) {
    int total_time = 0;
    waiting_times[0] = 0; 

    for (int i = 1; i < n; ++i) {
        
        total_time += processes[i - 1].burst_time;
        waiting_times[i] = total_time - processes[i].arrival_time;
        
        
        if (waiting_times[i] < 0)
            waiting_times[i] = 0;
    }
}

void calculateTurnaroundTime(struct Process processes[], int n, int waiting_times[], int turnaround_times[]) {
    for (int i = 0; i < n; ++i) {
        
        turnaround_times[i] = processes[i].burst_time + waiting_times[i];
    }
}

void calculateAverageTimes(struct Process processes[], int n) {
    int waiting_times[n], turnaround_times[n];
    float total_waiting_time = 0, total_turnaround_time = 0;

    calculateWaitingTime(processes, n, waiting_times);
    calculateTurnaroundTime(processes, n, waiting_times, turnaround_times);

    printf("Process\t  Arrival Time  \tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; ++i) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, waiting_times[i], turnaround_times[i]);

        total_waiting_time += waiting_times[i];
        total_turnaround_time += turnaround_times[i];
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
    }

    
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    calculateAverageTimes(processes, n);

    return 0;
}

