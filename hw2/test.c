/*
 * C Program to List Files in Directory
 */
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
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
   struct stat buf;

   if ( dirp == NULL )
   {
	   fprintf(stderr, "ERROR: Path '%s' does not exist\n",dirname);
	   exit(-1);
   }

   while ( (curr_ent = readdir(dirp)) != NULL )
   { 
	
      // Print the name.
      long sz = stat(curr_ent->d_name, &buf);
      char* ftype;
      int code = buf.st_mode & S_IFMT;
      
      if(S_ISREG(code)){
	      ftype = "f";
      }else if(S_ISDIR(code)){
	      ftype = "d";
      }else if(S_ISCHR(code)){
	      ftype = "c";
      }else if(S_ISBLK(code)){
	      ftype = "b";
      }else if(S_ISFIFO(code)){
	      ftype = "f";
      }else if(S_ISLNK(code)){
	      ftype = "sy";
      }else if(S_ISSOCK(code)){
	      ftype = "s";
      }
      char s[1000];
      time_t t = buf.st_mtime;
//      strftime(

      printf("%llu %llu %07o %lu %i %i %i %llu %i %s\n", curr_ent->d_ino, buf.st_blksize*buf.st_blocks/1000, ftype, buf.st_mode, buf.st_nlink, buf.st_uid, buf.st_gid, buf.st_size, buf.st_mtime, curr_ent->d_name);
      printf("%llu %llu\n", buf.st_blksize,buf.st_blocks);


      // Traverse sub-directories excluding . and ..
      // Ignore . and ..
      if ( curr_ent->d_type == DT_DIR && ! (is_dot_or_dot_dot(curr_ent->d_name)) )
      {
         // Allocate memory for the subdirectory.
         // 1 additional for the "/" and the second additional for "\0".
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

int main(int argc, char **argv)
{
	char* location;
	if(argc > 2)
	{
		fprintf(stderr, "ERROR: Only one argument allowed");
		exit(-1);
	}
	else if(argc == 1)
	{
		location = "./";
	}else if(argc == 2)
	{
		location = argv[1];
	}else{
		fprintf(stderr, "ERROR: Unexpected error");
	}

	listdir(location);
}

