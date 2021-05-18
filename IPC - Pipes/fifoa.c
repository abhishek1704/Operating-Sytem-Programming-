#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int ret = 0, f1 = 0, f2 = 0;
	char sentence[200], readSentence[1000];

	printf("Creating the FIFO 1\n");

	ret = mkfifo("myfifo", 0666);
	printf("\nEnter some text : \n");

	fgets(sentence, 200, stdin);

	printf("\nWriting the text into FIFO 1\n");

	f1 = open("myfifo", O_WRONLY);
	write(f1, sentence, strlen(sentence)+1);
	printf("\nWaiting for the info through FIFO 2, going for sleep ...\n");
	sleep(5);

	f2 = open("myfifo", O_RDONLY);
	read(f2, readSentence, 1000);
	printf("\nThe info received from FIFO 2 : \n\n%s", readSentence);
	printf("\n\n");

	unlink("myfifo");

	return 0;
}
