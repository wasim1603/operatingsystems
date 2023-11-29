#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 50
#define MAX_FILENAME_LEN 50

struct File {
    char filename[MAX_FILENAME_LEN];
    int size;
};

struct Directory {
    struct File files[MAX_FILES];
    int file_count;
};

void initializeDirectory(struct Directory *dir) {
    dir->file_count = 0;
}

void addFile(struct Directory *dir, const char *filename, int size) {
    if (dir->file_count < MAX_FILES) {
        strcpy(dir->files[dir->file_count].filename, filename);
        dir->files[dir->file_count].size = size;
        dir->file_count++;
        printf("File '%s' added successfully.\n", filename);
    } else {
        printf("Directory is full. Cannot add more files.\n");
    }
}

void displayFiles(struct Directory *dir) {
    printf("Files in directory:\n");
    if (dir->file_count == 0) {
        printf("Directory is empty.\n");
    } else {
        for (int i = 0; i < dir->file_count; i++) {
            printf("File: %s, Size: %d\n", dir->files[i].filename, dir->files[i].size);
        }
    }
}

int main() {
    struct Directory singleLevelDir;
    initializeDirectory(&singleLevelDir);

    addFile(&singleLevelDir, "file1.txt", 100);
    addFile(&singleLevelDir, "document.docx", 250);
    addFile(&singleLevelDir, "image.jpg", 500);

    displayFiles(&singleLevelDir);

    return 0;
}

