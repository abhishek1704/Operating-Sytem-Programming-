#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX 100

int main()
{
	int f_desc1[2], f_desc2[2], eof = 0, conptr;
	pid_t pid;

	char filename[MAX], buffer[MAX], ch, ch1;

	FILE *fp; 

	pipe(f_desc1);
	pipe(f_desc2);

	pid = fork();

	if (pid == 0)
	{
		sleep(5);

		printf("\n# In the child proccess with parent id : %d\n\n", getppid());
		close(f_desc1[1]);
		read(f_desc1[0], buffer, sizeof(buffer));
		printf("  File %s is being read by child as recieved from pipe 1\n", buffer);
		fp = fopen(buffer, "r");
		close(f_desc1[0]);
		close(f_desc2[0]);
		printf("  Reading end of both the pipes is closed !\n");
		printf("  Contents of file %s are sent back through pipe 2 to the parent\n", buffer);
		while (eof != -1)
		{
			eof = fscanf(fp, "%c", &ch);
			write(f_desc2[1], &ch, sizeof(ch));
		}

		close(f_desc2[1]);
		printf("\n  Closing writing end of pipe 2 and exiting from child proccess !!\n");
		printf("\n-------------------------------------------------------------------\n");

		exit(0);
	}
	else
	{
		close(f_desc1[0]);
		printf("\n# In the parent proccess, id : %d\n\n", getpid());
		printf("  Enter the name of the file : ");
		scanf("%s", filename);
		printf("  Filename %s is sent through the pipe 1\n", filename);
		write(f_desc1[1], filename, strlen(filename)+1);
		close(f_desc1[1]);
		close(f_desc2[1]);
		printf("\n-------------------------------------------------------------------\n");

		sleep(5);

		printf("\n  Contents of file %s are recieved successfully by the parent !\n", filename);
		printf("\n\nContents are :\n\n");
		while (conptr != 0)
		{
			conptr = read(f_desc2[0], &ch1, sizeof(ch1));
			printf("%c", ch1);
		}
		printf("Now closing the pipe 2\n");

		exit(0);
	}


	return 0;
}
