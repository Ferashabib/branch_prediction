#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>

int main(int argc, char *argv[])
{
	printf("I am lazy, letting other program to ls the directory\n\n");
	printf("I will just wait for their report\n\n");
	execlp("ls", "ls", NULL);
	printf ("They finished; Done! \n");
	return 0;
}
