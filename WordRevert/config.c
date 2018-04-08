/**
 * @file config.c
 */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "config.h"

const char *status_file = "./result.txt";


int data_read(char *name, char *data)
{

	FILE *fp;
	char line[1024];

	fp = 0 == strncmp(name, "-", 2) ? stdin : fopen(name, "r");

	if (!fp) {
		perror("fopen");
		return -1;
	}

        if (fgets(line, sizeof(line), fp)) {
           fprintf(stdout,"data is %s",line);
           data = line;
        }

	fclose(fp);
	return 0;
}


int write_result_file(char *result)
{
       int fd;
       if((fd=open(status_file, O_WRONLY))==-1) { 
           fprintf(stderr, "status file open failed\n");
           return -1;
       }
       write(fd,result,strlen(result));
       close(fd);

       return 0;
}
