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
void file_operations_menu() 
{
    int choice;
    while (1) 
    {
        printf("\n=== File Operations Menu ===\n");
        printf("1. Create/ Open File\n");
        printf("2. Change File Permission\n");
        printf("3. Read from File\n");
        printf("4. Write to File\n");
        printf("5. Delete File\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
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


