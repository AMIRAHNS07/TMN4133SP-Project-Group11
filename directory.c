#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

//Function to create a directory
void create_directory(const char *path)
{
   if (mkdir(path, 0777) == 0)
   {
      printf("Directory created successfully: %s\n", path);
   }
   else
   {

      perror("Failed to create directory");
   }
 }

// Function to deleta a directory
void delete_directory(const char *path)
{

   if(rmdir(path) == 0)
   {
      print("Directory deleted successfully: %s\n", path);
   }
   else
   {
      perror("Failed to delete directory");
   }

 }

//Function to print the current working directory
void print_current_directory()
{
   char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) !=NULL)
   {
     printf("Current working directory: %s\n", cwd);
   }
   else
    {
      perror("Failed to get current directory");
     }
  }

// Function to list files in a directory
void list_files_in_directory(const char *path)
{
   DIR *dir = opendir(path);
   struct dirent *entry;
   if (dir == NULL)
   {

     perror("Failed to open directory");
     return;
   }

    printf("Listing files in directory: %s\n", path);
    while ((entry = readdir(dir)) !=NULL)
   {
     printf("%s\n", entry->d_name);
   }

   closedir(dir);

}
