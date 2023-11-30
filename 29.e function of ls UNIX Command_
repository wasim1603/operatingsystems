#include <stdio.h>
#include <dirent.h>

void ls(char *dir) {
    DIR *dp;
    struct dirent *ep;
    dp = opendir(dir);
    if (dp != NULL) {
        while ((ep = readdir(dp)) != NULL) {
            printf("%s\n", ep->d_name);
        }
        closedir(dp);
    } else {
        perror("Couldn't open the directory");
    }
}

int main() {
    char dir[100];
    printf("Enter the directory: ");
    scanf("%s", dir);
    ls(dir);
    return 0;
}
