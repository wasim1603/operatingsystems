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

void SJF(struct Process processes[], 

