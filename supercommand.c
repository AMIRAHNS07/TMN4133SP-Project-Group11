#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For getopt()
#include <fcntl.h>
#include <linux/input.h>
#include <time.h>

// Function declarations
void file_operations_menu();
void directory_operations_menu();
void keylogger_operations_menu(int argc, char *argv[]);
void keylogger(const char *logfile);

int main(int argc, char *argv[]) 
{
    // Check if command-line arguments are provided
    if (argc == 3 && strcmp(argv[1], "-m") == 0) {
        int mode = atoi(argv[2]);  // Extract the mode (3 for keylogger)
        
        // If keylogger operation mode (3), directly call the keylogger function
        if (mode == 3) {
            keylogger_operations_menu(argc, argv);  // Directly call the keylogger operation
            return 0;  // Exit after running the keylogger
        } else {
            printf("Invalid mode selected!\n");
            return 1;  // Invalid mode
        }
    } 
    else {
        // If no arguments are passed, show the menu system
        int choice = 0;
        while (1) {
            printf("\n=== SUPER COMMAND MENU ===\n");
            printf("1. File Operations\n");
            printf("2. Directory Operations\n");
            printf("3. Keylogger Operations\n");
            printf("0. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    file_operations_menu();
                    break;
                case 2:
                    directory_operations_menu();
                    break;
                case 3:
                    keylogger_operations_menu(argc, argv);  // Keylogger operation
                    break;
                case 0:
                    printf("Exiting program. Goodbye!\n");
                    return 0;
                default:
                    printf("Invalid choice! Please try again.\n");
            }
        }
    }
}

// Keylogger menu function (with command-line args support)
void keylogger_operations_menu(int argc, char *argv[]) {
    // Hardcoded log file name
    const char *logfile = "keylog.txt";  // The log file will always be 'keylog.txt'

    // Print message indicating keylogger is starting
    printf("\n=== Keylogger Operations ===\n");
    printf("Starting keylogger... Log file: %s\n", logfile);

    // Call the keylogger function with the log file 'keylog.txt'
    keylogger(logfile);
}

void file_operations_menu() {
    int choice;
    while (1) {
        printf("\n=== File Operations Menu ===\n");
        printf("1. Create/ Open File\n");
        printf("2. Change File Permission\n");
        printf("3. Read from File\n");
        printf("4. Write to File\n");
        printf("5. Delete File\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf("Selected: Create/Open File\n");
                break;
            case 2:
                printf("Selected: Change File Permission\n");
                break;
            case 3:
                printf("Selected: Read from File\n");
                break;
            case 4:
                printf("Selected: Write to File\n");
                break;
            case 5:
                printf("Selected: Delete File\n");
                break;
            case 0:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void directory_operations_menu() {
    int choice;
    while (1) {
        printf("\n=== Directory Operations Menu ===\n");
        printf("1. Create Directory\n");
        printf("2. Delete Directory\n");
        printf("3. Print Current Directory\n");
        printf("4. List Files in Directory\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf("Selected: Create Directory\n");
                break;
            case 2: 
                printf("Selected: Delete Directory\n");
                break;
            case 3:
                printf("Selected: Print Current Working Directory\n");
                break;
            case 4:
                printf("Selected: List Files in Directory\n");
                break;
            case 0:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

