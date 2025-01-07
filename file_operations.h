#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <sys/types.h>

// Function declarations for file operations
void create_file(const char *filepath);
void change_file_permission(const char *filepath, mode_t mode);
void read_file(const char *filepath);
void write_file(const char *filepath);
void delete_file(const char *filepath);

#endif
