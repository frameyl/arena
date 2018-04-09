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
    char line[1024] = {0};
    int n=0;

    fp = 0 == strncmp(name, "-", 2) ? stdin : fopen(name, "r");

    if (!fp) {
        perror("fopen");
        return -1;
    }

    char *linestart = data;
    while (fgets(line, sizeof(line), fp)) {
        n = sprintf(linestart, line);
        linestart += n;
    }

    fprintf(stdout,"data is: %s",data);

    fclose(fp);
    return 0;
}


int write_result_file(char *result)
{
    if (!result) return -1;

    int fd;
    if((fd=open(status_file, O_APPEND))==-1) {
        fprintf(stderr, "status file open failed\n");
        return -1;
    }
    write(fd,result,strlen(result));
    close(fd);

    return 0;
}
