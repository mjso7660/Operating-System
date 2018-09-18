#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int concat(int fd_in, int fd_out, long buffersize, char* buffer, char* output_file, char* input_file){
	int bytes_written;
	int bytes_read = read(fd_in, buffer, buffersize);
	
	while(bytes_read > 0){
		bytes_written = write(fd_out, buffer, bytes_read);
		if(bytes_written < 0){
			fprintf(stderr,"ERROR (%s): Failed to write to output file %s\n", strerror(errno), output_file);
			exit(-1);
		}
		bytes_read = read(fd_in, buffer, buffersize);
	}
	if(bytes_read < 0){
		fprintf(stderr,"ERROR (%s): Failed to read an input file %s\n", strerror(errno), input_file);
		exit(-1);
	}
}

int main(int argc, char **argv){
	int c;
	int index;
	int fd_out = STDOUT_FILENO;
	int fd_in;
	long buffersize = 1024;				//Default to 1024	
	char* output_file = 0;
	
	while ((c = getopt(argc, argv, "b:o:"))!= -1){
		switch(c){
		case 'b':
			if((buffersize = atoi(optarg)) < 1){
				fprintf(stderr, "ERROR: Invalid argument: buffer size must be greater than 0\n");
				exit(-1);
			}
			break;
		case 'o':
			output_file = optarg;
			fd_out = open(optarg, O_RDWR|O_CREAT|O_TRUNC,0666);
			if(fd_out < 0)
				fprintf(stderr,"ERROR (%s): Failed to OPEN output file %s\n", strerror(errno), output_file);
				exit(-1);
			break;
		case '?':
			if(optopt=='b'){
				fprintf(stderr,"ERROR: -b argument missing\n");
				exit(-1);
			}else if(optopt=='o'){
				fprintf(stderr,"ERROR: -o argument missing\n");
				exit(-1);
			}
			break;
		default:
			fprintf(stderr, "ERROR: Incorrect input\n");
			exit(-1);
		}
	}

	char *buffer = malloc(buffersize);

	for(index = optind; index < argc; index++){
		fd_in = open(argv[optind], O_RDONLY);
		if(fd_in < 0){
			fprintf(stderr, "ERROR: Failed to OPEN a input file %s\n",argv[optind]);
			exit(-1);
		}
		concat(fd_in, fd_out, buffersize, buffer, output_file, argv[optind]);
	}
	if(fd_out != STDOUT_FILENO || close(fd_out) < 0 ){
		fprintf(stderr,"ERROR (%s): Failed to CLOSE output file %s\n", strerror(errno), output_file);
		exit(-1);
	}
	free(buffer);
	return(EXIT_SUCCESS);
}
