#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include "directory.h"
#include "file_operations.h"

void file_operations_menu();
void directory_operations_menu();
void keylogger_operations_menu(const char *logfile);
void keylogger(const char *logfile);

// Function declarations for directory operations
void create_directory(const char *path);
void delete_directory(const char *path);
void print_current_directory();
void list_files_in_directory(const char *path);

int main(int argc, char *argv[]) 
{

     
     if (argc == 4 && strcmp(argv[1], "-m") == 0 && atoi(argv[2]) == 3) {
        const char *logfile = argv[3];
        keylogger_operations_menu(logfile);
        return 0;
      }

      if (argc == 5 && strcmp(argv[1], "-m") == 0 && atoi(argv[2]) == 2 && atoi(argv[3]) ==3) {
        const char *path = argv[4]; 
        list_files_in_directory(path);
        return 0;
       }

     if (argc >= 4 && strcmp(argv[1], "-m") == 0 && atoi(argv[2]) == 1) {
        int operation = atoi(argv[3]);
        switch(operation) {
            case 1: // Create file
                if (argc == 5) {
                    create_file(argv[4]);
                    return 0;
                }
                break;
            case 2: // Change permissions
                if (argc == 6) {
                    mode_t mode = strtol(argv[5], NULL, 8);
                    change_file_permission(argv[4], mode);
                    return 0;
                }
                break;
            case 3: // Read file
                if (argc == 5) {
                    read_file(argv[4]);
                    return 0;
                }
                break;
            case 4: // Write to file
                if (argc == 5) {
                    write_file(argv[4]);
                    return 0;
                }
                break;
            case 5: // Delete file
                if (argc == 5) {
                    delete_file(argv[4]);
                    return 0;
                }
                break;
            default:
                printf("Invalid file operation\n");
                return 1;
        }
        printf("Invalid number of arguments for file operation\n");
        return 1;
    }

    // Main menu if no command-line args are passed
    int choice;
    while (1) 
    {
        printf("\n=== SUPER COMMAND MENU ===\n");
        printf("1. File Operations\n");
        printf("2. Directory Operations\n");
        printf("3. Keylogger Operations\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                file_operations_menu();
                break;

            case 2:
                directory_operations_menu();
                break;

            case 3:
                keylogger_operations_menu("keylog.txt");  // Keylogger operation
                break;

            case 0:
                printf("Exiting program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
  

// Keylogger menu function
void keylogger_operations_menu(const char *logfile) 
{
    printf("\n=== Keylogger Operations ===\n");
    printf("Starting keylogger... Log file: %s\n", logfile);

    // Start the keylogger in the background and log keystrokes
    keylogger(logfile);
}

// File operations menu function
void file_operations_menu() {
    int choice;
    char filepath[256];
    char mode_str[5];
    mode_t mode;

    while (1) {
        printf("\n=== File Operations Menu ===\n");
        printf("1. Create/Open File\n");
        printf("2. Change File Permission\n");
        printf("3. Read from File\n");
        printf("4. Write to File\n");
        printf("5. Delete File\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                printf("Enter filepath: ");
                fgets(filepath, sizeof(filepath), stdin);
                filepath[strcspn(filepath, "\n")] = 0; // Remove newline
                create_file(filepath);
                break;

            case 2:
                printf("Enter filepath: ");
                fgets(filepath, sizeof(filepath), stdin);
                filepath[strcspn(filepath, "\n")] = 0;
                printf("Enter permissions in octal (e.g., 644): ");
                fgets(mode_str, sizeof(mode_str), stdin);
                mode = strtol(mode_str, NULL, 8);
                change_file_permission(filepath, mode);
                break;

            case 3:
                printf("Enter filepath: ");
                fgets(filepath, sizeof(filepath), stdin);
                filepath[strcspn(filepath, "\n")] = 0;
                read_file(filepath);
                break;

            case 4:
                printf("Enter filepath: ");
                fgets(filepath, sizeof(filepath), stdin);
                filepath[strcspn(filepath, "\n")] = 0;
                write_file(filepath);
                break;

            case 5:
                printf("Enter filepath: ");
                fgets(filepath, sizeof(filepath), stdin);
                filepath[strcspn(filepath, "\n")] = 0;
                delete_file(filepath);
                break;

            case 0:
                return;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

// Directory operations menu function
void directory_operations_menu() 
{
    int choice;

    while (1) 
    {
        printf("\n=== Directory Operations Menu ===\n");
        printf("1. Create Directory\n");
        printf("2. Delete Directory\n");
        printf("3. Print Current Directory\n");
        printf("4. List Files in Directory\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf ("%d", &choice);

        switch (choice) 
        {
            case 1:
                {

                char path[100]; 
                printf("Enter the directory name/path: ");
                scanf("%s", path);
                create_directory(path);
                }
                break;

            case 2:
                { 

                char path[100];
                printf("Enter the directory name/path to delete: ");
                scanf("%s", path);
                delete_directory(path);
                }
                break;


            case 3:
                print_current_directory();
                break;

            case 4:
                {
              
                char path[100];
                printf("Enter the directory path to list: ");
                scanf("%s", path);
                list_files_in_directory(path);
                }
                break;

            case 0:
                return;

            default:
                printf("Invalid choice! Please try again.\n");
        }

    }
}


