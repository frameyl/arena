#include <stdio.h>
#include "filestat.h"

#define MAX_FILENAME_LEN 1024

int main() {
	char largestFilename[MAX_FILENAME_LEN] = {'\0'};

	FindFileWithMaxSizeInDir(".", largestFilename, sizeof(largestFilename));
	char a = getchar();
	printf("result:%s\n", largestFilename);
	return 0;
}
