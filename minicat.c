#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){
	int bflag = 0;
       	int oflag = 0;
	int c;
	int index;
	int fd_out;
	int fd_in;
	long buffersize;
	int readin;
	int writeout;
	
	while ((c = getopt(argc, argv, "b:o:"))!= -1){
		printf("optind is %s\n",argv[optind]);
		switch(c){
		case 'b':
			bflag = 1;
			buffersize = atoi(optarg);
			printf("optarg is %ld\n",buffersize);
			break;
		case 'o':
			oflag = 1;
			fd_out = open(optarg, O_RDWR|O_CREAT|O_TRUNC,0666);
			printf("file descriptor is %d\n",fd_out);
			break;
		case '?':
			if(optopt=='b')
				printf("-b argument missing\n");
			else if(optopt='o')
				printf("-o argument missing\n");
			break;
		}
	}

	char *buffer = malloc(buffersize);

	printf ("bflag = %d, oflag = %d\n",bflag,oflag);
	for(index = optind; index < argc; index++)
		fd_in = open(argv[optind], O_RDONLY);
		readin = read(fd_in,buffer,buffersize);
		writeout = write(fd_out,buffer,buffersize);
		printf("Non-option argument %s\n",argv[index]);

}

			
