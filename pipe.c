#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	printf ("how many args are there: %d\n", argc); 
	printf ("what are they:\n");
	for (int i=0;i<argc;i++) {
		printf ("argv %d is: %s \n", i, argv[i]);
	}
	return 0;
}
