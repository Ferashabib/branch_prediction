#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	if (argc <= 1) { //Check if there are any arguments
		//printf("No Arguments");
		exit(EINVAL);
	}

	for (int i = 1; i < argc; i++) { //argv[0] is the program itself so we start at 1
		int fds[2];
		pipe(fds); //create the pipe

		int ret = fork();
		if (ret == 0) {//child
			if (i == argc-1) { //If this is the last argument
				close(fds[0]);
				close(fds[1]);

				//int execlp(const char *file, const char *arg, ... /*(char*) NULL*/);  
				execlp(argv[i], argv[i], NULL);

				//printf("Execlp failed!");
				return (EXIT_FAILURE); //if execlp fails
			}
			else { //NOT the last argument
			
			// dup2() performs the same task as dup(), but it specifically redirects fd.
			//output will go to write end of fds[1] instead of stdout
			dup2(fds[1], 1);
			close(fds[0]);
			close(fds[1]);
		      
			//int execlp(const char *file, const char *arg, ... /*(char*) NULL*/);  
			execlp(argv[i], argv[i], NULL);

			//printf("Execlp failed!");
			return (EXIT_FAILURE); //if execlp fails
			}
		}

		else if (ret>0) { //parent
			dup2(fds[0], 0); //redirect stdin to pipe

			close(fds[0]);
			close(fds[1]);

			//pid_t waitpid(pid_t pid, int *wstatus, int options);
			int wstatus;
			waitpid(ret, &wstatus, 0);

			// WIFEXITED(status): child exited normally 
			// WEXITSTATUS(status): return code when child exits

			int child_st = WIFEXITED(wstatus);
			int code = WEXITSTATUS(wstatus);
			int key = child_st && code;

			if (key) {

				//printf("Oop!");
				exit(code);
			}

		}

		else { //error

			//printf("No fork, just spoons");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}
