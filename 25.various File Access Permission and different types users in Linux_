#include <stdio.h>
#include <stdlib.h>

int calculatePermissions(int r, int w, int x) {
    return r * 4 + w * 2 + x;
}

int main() {
    int r, w, x, permissions;
    printf("Enter the file access permissions for owner, group, and others, respectively.\n");
    printf("For read, write, and execute, enter 1, 2, and 4, respectively.\n");
    printf("r: ");
    scanf("%d", &r);
    printf("w: ");
    scanf("%d", &w);
    printf("x: ");
    scanf("%d", &x);

    permissions = calculatePermissions(r, w, x);
    printf("The total file access permissions for the owner, group, and others are %d.\n", permissions);
    return 0;
}
