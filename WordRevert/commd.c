/**
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "config.h"


static void usage(char *progname)
{
    fprintf(stderr,
        "\nusage: %s [options]\n\n"
        " -f [file] read data from 'file'\n"
        " -h        prints this message and exits\n"
        "\n",
        progname);
}

char * item_revert(char *item)
{
    char *output = malloc(1024);
    char buf[1024] = {0};

    int column = 0;
    int i = 0;

    fprintf(stdout,"item is: %s",item);

    char *word_start = output;
    for(i=0; i<strlen(item); i++) {
        if (!isalpha(item[i])) {
            int wordlen = strlen(&buf[1022 - column + 1]) + 1;
            int wordstart = 1022 - column + 1;
            int wordend = 1022;
            if(isupper(buf[wordend])) {
                buf[wordstart]=toupper(buf[wordstart]);
                buf[wordend]=tolower(buf[wordend]);
            }

            strcpy(word_start, &buf[wordstart]);
            word_start[wordlen-1] = item[i];

            printf("write line(%d): %s\n", wordlen, &buf[1022 - column + 1]);
            column = 0;
            word_start += wordlen;
        } else {
            buf[1022 - column] = item[i];
            column++;
            printf("shit %c\n", item[i]);
        }
    }

    printf("output: %s\n", output);

    return output;
}

int main(int argc, char *argv[])
{
    char *config = NULL, *progname, *result = NULL;
    char data[1024] = {0};
    int c;
    int running=1;

    /* Process the command line arguments. */
    progname = strrchr(argv[0], '/');
    progname = progname ? 1+progname : argv[0];
    while (EOF != (c = getopt(argc, argv, "246AEf:hi:l:mPp:qrsvz"))) {
        switch (c) {
            case 'f':
                    config = optarg;
                    break;
            case 'h':
                    usage(progname);
                    return 0;
            case '?':
                    usage(progname);
                    return -1;
            default:
                    usage(progname);
                    return -1;
            }
    }

    if (config && data_read(config, data)) {
        fprintf(stderr, "failed to read configuration file\n");
        return -1;
    }

    //function
    result=item_revert(data);

    //if (daemon(1,1) < 0) {
    //    fprintf(stderr, "daemon failed");
    //    exit(1);
    //}

    while (running) {
        write_result_file(result);
        sleep(30);
    }

    return 0;
}
