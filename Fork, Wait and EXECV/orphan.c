#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () 
{

	int pid, id;

	pid = getpid();

	printf("\nThe id of the current process : %d\n", pid); 

	printf("Forking a child process !\n");
	id = fork();

	if (id != 0)
	{
		printf("\nThe control is now with parent process ...\n");
		printf(" Parent is going to sleep !\n");
		sleep(5);
		
		printf("\nParent wakes up !\n");
		printf(" Parent process is exiting !\n");
		exit(-1);
	}
	else
	{
		printf("\n# The control is now with child process ... \n");
		printf(" - Child process id : %d\n", getpid());
		printf(" - Parent process id : %d\n", getppid());
		printf(" - Child is going for sleep - 1 !\n");
		sleep(5);

		printf("\n# Again child process wakes up - 1 ! \n");
		printf(" - Child process id : %d\n", getpid());
		printf(" - Parent process id : %d\n", getppid());
		printf(" - Child is going for sleep - 2 !\n\n");
		sleep(5);

		printf("\n\n# Again child process wakes up - 2 ! \n");
		printf(" - Child has now a new parent with id : %d\n\n", getppid());
		exit(0);
	}
}