#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <


int main(){
	int PATH_MAX = 0;
	char *symlinkpath = "./test.c";
	char actualpath [PATH_MAX+1];
	char *ptr;

	ptr = realpath(symlinkpath, actualpath);
	printf("%s\n",ptr);
}
