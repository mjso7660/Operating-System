#include <libgen.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	char* local_file = "a.out";

	char* ts1 = strdup(local_file);
	char* ts2 = strdup(local_file);

	char* dir = dirname(ts1);
	printf("%s\n",dir);
}
