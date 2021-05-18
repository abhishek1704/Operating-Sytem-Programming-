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
		printf("\nThe control is now with parent process...\n");
		printf(" Parent is going to sleep !\n");
		sleep(10);
		printf("\nParent wakes up !\n");
		printf("\n--- process has become zombie ! ---\n");
		while(1)
		{

		}
		printf("\nParent is exiting now....\n\n");
		exit(-1);
	}
	else
	{
		printf("\n# The control is now with child process... \n");
		printf(" - Child process id : %d\n", getpid());
		printf(" - Parent process id : %d\n", getppid());
		printf(" - Child is exiting now.....\n");
		exit(0);
	}
}