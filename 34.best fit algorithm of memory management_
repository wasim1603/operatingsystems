#include <stdio.h>
#include <stdlib.h>

void bestFit(int blockSize[], int m, int size[], int n) {
    int allocation[n], j, leastSize, minIndex;
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        leastSize = blockSize[0];
        minIndex = 0;
        for (j = 1; j < m; j++) {
            if (blockSize[j] >= size[i] && blockSize[j] - size[i] < leastSize) {
                leastSize = blockSize[j] - size[i];
                minIndex = j;
            }
        }
        if (leastSize < blockSize[minIndex]) {
            allocation[i] = minIndex;
            blockSize[minIndex] -= size[i];
        }
    }

    printf("\nBlock Number\tProcess Number\t\tBlock Size\n\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("%d\t\t%d\t\t\t%d\n", allocation[i], i, size[i]);
        } else {
            printf("%d\t\t%d\t\t\tNot Allocated\n", i, i);
        }
    }
}

int main() {
    int m, n, size[10], blockSize[10];

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter the size of each memory block: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the size of each process: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &size[i]);
    }

    bestFit(blockSize, m, size, n);

    return 0;
}
