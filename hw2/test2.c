/*
 * C Program to List Files in Directory
 */
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

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
		lstat(curr_ent->d_name, &buf);
		char* ftype;
		int code = buf.st_mode & S_IFMT;

		char a[100], b[100];
		char s[1000];
		char const*symlinkpath = dirname;
		char actualpath [100];
		char *ptr;
		ptr = realpath(symlinkpath, actualpath);
		//printf("%s\n",symlinkpath);
		sprintf(s, "%s/%s",ptr,curr_ent->d_name);
		
		//char *file = strcat(a,b);
		printf("%s\n",s);

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
			printf("SUB: %s\n",subdir);
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

