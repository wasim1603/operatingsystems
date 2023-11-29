#include <stdio.h>

#define MEMORY_SIZE 1000

struct MemoryBlock {
    int start;
    int size;
    int allocated;
};

struct MemoryBlock memory[MEMORY_SIZE];

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].start = i * 10;
        memory[i].size = 10;
        memory[i].allocated = 0;
    }
}

void allocateMemory(int processId, int size) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].allocated == 0 && memory[i].size >= size) {
            memory[i].allocated = processId;
            printf("Memory allocated to Process %d: Starting at %d, Size: %d\n", processId, memory[i].start, memory[i].size);
            break;
        }
    }
}

int main() {
    initializeMemory();

    allocateMemory(1, 30);
    allocateMemory(2, 20);
    allocateMemory(3, 15);

    return 0;
}

