/**
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    return ;
}

int main(int argc, char *argv[])
{
	char *config = NULL, *progname, *result = NULL;
        char data[1024];
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
        
       if (daemon(1,1) < 0) {
           fprintf(stderr, "daemon failed");
           exit(1); 
       }
 
        
       while (running) {
              write_result_file(result);
              sleep(30);
       }
 

      return 0;
}
