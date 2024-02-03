#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	if (argc <= 1) { //Check if there are any arguments
		fprintf(stderr, "No Arguments");
		exit(EINVAL);
	}

	for (int i = 1; i < argc; i++) {
		int fds[2];
		pipe(fds); //create the pipe

		int ret = fork();
		if (ret == 0) {//child
			if (i != argc-1) {//Not the last argument
				dup2(fds[1], 1);
			}

			close(fds[0]);
			close(fds[1]);
			execlp(argv[i], argv[i]);

			return EXIT_FALIURE; //if execlp fails
		}
		else if (ret>0) { //parent
			dup2(fds[0], 0);

			close(fds[0]);
			close(fds[0]);

			int wstatus;
			waitpid(ret, &wstatus, 0);

			// WIFEXITED(status): child exited normally 
			// WEXITSTATUS(status): return code when child exits

			bool child_st = WIFEXITED(wstatus);

			if (child_st) {
				exit(WEXITSTATUS(wstatus));
			}

		}
	}
	return 0;
}
