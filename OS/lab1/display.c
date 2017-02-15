#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
pid_t pid[2];
int main(void)
{
	int n = 0;
	for(; n<3; n++)
	{
		if((pid[n] = fork()) == 0)
			break;
	}
	switch(n)
	{
		case 1://child process 1
		{
			char* argv[] = {"./windows/window1/window1", NULL};
			if(execv("./windows/window1/window1", argv)==-1)
			{
				printf("errno = %d\n", errno); // errno = 33 
			 	printf("error: %s\n", strerror(errno)); // error: Numerical argument out of domain 
			}
			break;
		}
		case 2://child process 2
		{
			char* argv[] = {"./windows/window2/window2", NULL};
			if(execv("./windows/window2/window2", argv)==-1)
			{
				printf("errno = %d\n", errno); // errno = 33 
			 	printf("error: %s\n", strerror(errno)); // error: Numerical argument out of domain 
			}
			break;
		}
		case 3://child process 3
		{
			char* argv[] = {"./windows/window3/window3", NULL};
			if(execv("./windows/window3/window3", argv)==-1)
			{
				printf("errno = %d\n", errno); // errno = 33 
			 	printf("error: %s\n", strerror(errno)); // error: Numerical argument out of domain 
			}
			break;
		}
	}
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	waitpid(pid[2], NULL, 0);
	return 0;
}
