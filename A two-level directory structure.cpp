#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRECTORIES 50
#define MAX_FILES_PER_DIR 50
#define MAX_FILENAME_LEN 50

struct File {
    char filename[MAX_FILENAME_LEN];
    int size;
};

struct Directory {
    char dirname[MAX_FILENAME_LEN];
    struct File files[MAX_FILES_PER_DIR];
    int file_count;
};

struct MainDirectory {
    struct Directory directories[MAX_DIRECTORIES];
    int dir_count;
};

void initializeMainDirectory(struct MainDirectory *mainDir) {
    mainDir->dir_count = 0;
}

void initializeDirectory(struct Directory *dir, const char *name) {
    strcpy(dir->dirname, name);
    dir->file_count = 0;
}

void addFileToDirectory(struct Directory *dir, const char *filename, int size) {
    if (dir->file_count < MAX_FILES_PER_DIR) {
        strcpy(dir->files[dir->file_count].filename, filename);
        dir->files[dir->file_count].size = size;
        dir->file_count++;
        printf("File '%s' added to directory '%s'.\n", filename, dir->dirname);
    } else {
        printf("Directory '%s' is full. Cannot add more files.\n", dir->dirname);
    }
}

void addDirectory(struct MainDirectory *mainDir, const char *dirname) {
    if (mainDir->dir_count < MAX_DIRECTORIES) {
        initializeDirectory(&mainDir->directories[mainDir->dir_count], dirname);
        mainDir->dir_count++;
        printf("Directory '%s' added successfully.\n", dirname);
    } else {
        printf("Main directory is full. Cannot add more directories.\n");
    }
}

void displayFilesInDirectory(struct Directory *dir) {
    printf("Files in directory '%s':\n", dir->dirname);
    if (dir->file_count == 0) {
        printf("Directory is empty.\n");
    } else {
        for (int i = 0; i < dir->file_count; i++) {
            printf("File: %s, Size: %d\n", dir->files[i].filename, dir->files[i].size);
        }
    }
}

int main() {
    struct MainDirectory twoLevelDir;
    initializeMainDirectory(&twoLevelDir);

    addDirectory(&twoLevelDir, "Folder1");
    addDirectory(&twoLevelDir, "Folder2");

    addFileToDirectory(&twoLevelDir.directories[0], "file1.txt", 100);
    addFileToDirectory(&twoLevelDir.directories[1], "document.docx", 250);
    addFileToDirectory(&twoLevelDir.directories[1], "image.jpg", 500);

    displayFilesInDirectory(&twoLevelDir.directories[0]);
    displayFilesInDirectory(&twoLevelDir.directories[1]);

    return 0;
}

