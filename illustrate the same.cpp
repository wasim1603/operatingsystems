#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main() {
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    
    source_fd = open("source.txt", O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    
    dest_fd = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd);
        return EXIT_FAILURE;
    }

    
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return EXIT_FAILURE;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading from source file");
        close(source_fd);
        close(dest_fd);
        return EXIT_FAILURE;
    }

    
    if (close(source_fd) == -1 || close(dest_fd) == -1) {
        perror("Error closing files");
        return EXIT_FAILURE;
    }

    printf("File copied successfully.\n");
    return EXIT_SUCCESS;
}

