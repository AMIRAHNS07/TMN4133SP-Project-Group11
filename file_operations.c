#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "file_operations.h"

// Function to create/open a new file
void create_file(const char *filepath) {
    int fd = open(filepath, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("Error creating file");
        return;
    }
    printf("File created successfully: %s\n", filepath);
    close(fd);
}

// Function to change file permissions
void change_file_permission(const char *filepath, mode_t mode) {
    if (chmod(filepath, mode) == -1) {
        perror("Error changing file permissions");
        return;
    }
    printf("File permissions changed successfully for: %s\n", filepath);
}

// Function to read from file and print to stdout
void read_file(const char *filepath) {
    char buffer[4096];
    ssize_t bytes_read;
    
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        return;
    }
    
    printf("File contents:\n");
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    
    if (bytes_read == -1) {
        perror("Error reading file");
    }
    
    close(fd);
}

// Function to write to file from stdin
void write_file(const char *filepath) {
    char buffer[4096];
    ssize_t bytes_read;
    
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file for writing");
        return;
    }
    
    printf("Enter text to write (Ctrl+D to finish):\n");
    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        if (write(fd, buffer, bytes_read) != bytes_read) {
            perror("Error writing to file");
            close(fd);
            return;
        }
    }
    
    if (bytes_read == -1) {
        perror("Error reading from stdin");
    }
    
    close(fd);
    printf("File written successfully\n");
}

// Function to delete a file
void delete_file(const char *filepath) {
    if (unlink(filepath) == -1) {
        perror("Error deleting file");
        return;
    }
    printf("File deleted successfully: %s\n", filepath);
}
