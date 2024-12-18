#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int create_file(const char *filename) {
    // Create a new file with default permissions (0644)
    int fd = creat(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        fprintf(stderr, "Error creating file %s: %s\n", filename, strerror(errno));
        return -1;
    }
    close(fd);
    printf("File %s created successfully.\n", filename);
    return 0;
}

int change_file_permission(const char *filename, mode_t new_mode) {
    // Change file permissions
    if (chmod(filename, new_mode) == -1) {
        fprintf(stderr, "Error changing permissions for %s: %s\n", filename, strerror(errno));
        return -1;
    }
    printf("Permissions for %s changed successfully.\n", filename);
    return 0;
}

int read_file(const char *filename) {
    // Open file for reading
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error opening file %s for reading: %s\n", filename, strerror(errno));
        return -1;
    }

    // Read and print file contents
    char buffer[4096];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1) {
        fprintf(stderr, "Error reading file %s: %s\n", filename, strerror(errno));
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int write_to_file(const char *filename) {
    // Open file for writing (create if not exists, truncate if exists)
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        fprintf(stderr, "Error opening file %s for writing: %s\n", filename, strerror(errno));
        return -1;
    }

    printf("Enter text to write (Ctrl+D to finish):\n");

    // Read from stdin and write to file
    char buffer[4096];
    ssize_t bytes_read;
    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        ssize_t bytes_written = write(fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            fprintf(stderr, "Error writing to file: %s\n", strerror(errno));
            close(fd);
            return -1;
        }
    }

    close(fd);
    printf("File %s written successfully.\n", filename);
    return 0;
}

int remove_file(const char *filename) {
    // Remove/delete file
    if (unlink(filename) == -1) {
        fprintf(stderr, "Error removing file %s: %s\n", filename, strerror(errno));
        return -1;
    }
    printf("File %s removed successfully.\n", filename);
    return 0;
}

// File operations menu function
int file_operations_menu() {
    int choice;
    char filename[256];
    mode_t new_mode;

    while (1) {
        printf("\n--- File Operations Menu ---\n");
        printf("1. Create/Open a new file\n");
        printf("2. Change file permissions\n");
        printf("3. Read from a file\n");
        printf("4. Write to a file\n");
        printf("5. Remove a file\n");
        printf("6. Return to main menu\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            // Clear input buffer
            while (getchar() != '\n');
            printf("Invalid input. Please try again.\n");
            continue;
        }

        // Clear input buffer
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Enter filename: ");
                if (fgets(filename, sizeof(filename), stdin) == NULL) continue;
                filename[strcspn(filename, "\n")] = 0; // Remove newline
                create_file(filename);
                break;
            
            case 2:
                printf("Enter filename: ");
                if (fgets(filename, sizeof(filename), stdin) == NULL) continue;
                filename[strcspn(filename, "\n")] = 0; // Remove newline
                
                printf("Enter new permission (in octal, e.g., 644): ");
                if (scanf("%o", &new_mode) != 1) {
                    printf("Invalid permission.\n");
                    break;
                }
                while (getchar() != '\n'); // Clear input buffer
                
                change_file_permission(filename, new_mode);
                break;
            
            case 3:
                printf("Enter filename to read: ");
                if (fgets(filename, sizeof(filename), stdin) == NULL) continue;
                filename[strcspn(filename, "\n")] = 0; // Remove newline
                read_file(filename);
                break;
            
            case 4:
                printf("Enter filename to write: ");
                if (fgets(filename, sizeof(filename), stdin) == NULL) continue;
                filename[strcspn(filename, "\n")] = 0; // Remove newline
                write_to_file(filename);
                break;
            
            case 5:
                printf("Enter filename to remove: ");
                if (fgets(filename, sizeof(filename), stdin) == NULL) continue;
                filename[strcspn(filename, "\n")] = 0; // Remove newline
                remove_file(filename);
                break;
            
            case 6:
                return 0;
            
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
