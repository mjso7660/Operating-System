/*
 * C Program to List Files in Directory
 */
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
/* 
void listdir2(void)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
	    listdir(strdir->d_name);
        }
        closedir(d);
    }
    return(0);
}
*/

int is_dot_or_dot_dot(char const* name)
{
   return (strcmp(name, ".") == 0 || strcmp(name, "..") == 0 );
}

void listdir(char const* dirname)
{
   char* subdir;
   DIR* dirp = opendir(dirname);
   struct dirent *curr_ent;

   if ( dirp == NULL )
   {
      return;
   }

   while ( (curr_ent = readdir(dirp)) != NULL )
   { 
      // Print the name.
      printf("%s\n", curr_ent->d_name);

      // Traverse sub-directories excluding . and ..
      // Ignore . and ..
      if ( curr_ent->d_type == DT_DIR && ! (is_dot_or_dot_dot(curr_ent->d_name)) )
      {
         // Allocate memory for the subdirectory.
         // 1 additional for the '/' and the second additional for '\0'.
         subdir = malloc(strlen(dirname) + strlen(curr_ent->d_name) + 2);

         // Flesh out the subdirectory name.
         strcpy(subdir, dirname);
         strcat(subdir, "/");
         strcat(subdir, curr_ent->d_name);

         // List the contents of the subdirectory.
         listdir(subdir);

         // Free the allocated memory.
         free(subdir);
      }
   }

   // Close the directory
   closedir(dirp);
}

int main(void)
{
	char const *a = ".";
	listdir(a);
}

