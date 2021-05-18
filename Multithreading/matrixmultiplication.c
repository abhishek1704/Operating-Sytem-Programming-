#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#define MAX 100

int mat1[MAX][MAX], mat2[MAX][MAX], mul[MAX][MAX];
void display(int mat[MAX][MAX],int row,int col);

void *mul_thread(void *args)
{
	int *rcArgs = (int *) args, r, c, i, columns, temp, tval, del;

	r = rcArgs[0];
	c = rcArgs[1];
	columns = rcArgs[2];

	printf("\nThread (%d : %d) started...\n", r+1, c+1);

	for(i=0; i<columns; i++)
	{
		temp = mat1[r][i]*mat2[i][c];
		tval = tval + temp;

		printf("\nResult of thread (%d : %d) is %d * %d = %d, (updated value :  %d)", r+1, c+1, mat1[r][i], mat2[i][c], temp, tval);
		del = rand()%10;
		printf("\nThread (%d : %d) is going for sleep for %d units time...\n", r+1, c+1, del);
		sleep(del);
		printf("\nThread (%d : %d) resumed...\n", r+1, c+1);		
	}
	printf("\nThread (%d : %d) exited...\n", r+1, c+1);	
	pthread_exit((void *) tval);	
}

int main()
{
	int row1, col1, row2, col2, rcArgs[3], *status;
	pthread_t P[MAX][MAX]; 

	int i,j;
	printf("\nEnter the number of rows and columns in matrix 1 : ");
	scanf("%d", &row1);
	scanf("%d", &col1);
	printf("\nEnter the number of rows and columns in matrix 2 : ");
	scanf("%d", &row2);
	scanf("%d", &col2);

	while(col1 != row2)
	{
		printf("\nMultiplication is not possible !\n");
		printf("\nEnter the number of rows and columns in matrix 1 : ");
		scanf("%d", &row1);
		scanf("%d", &col1);
		printf("\nEnter the number of rows and columns in matrix 2 : ");
		scanf("%d", &row2);
		scanf("%d", &col2);	
	}

	printf("\nEnter the elements of matrix 1 :");
	for(i=0; i<row1; i++)
		for(j=0; j<col1; j++)
			scanf("%d",&mat1[i][j]);	

	printf("\nEnter the elements of matrix 2 :");
	for(i=0; i<row2; i++)
		for(j=0; j<col2; j++)
			scanf("%d",&mat2[i][j]);		

	printf("\nMatrix 1 :\n");
	display(mat1,row1,col1);printf("\n");
	printf("\nMatrix 2 :\n");
	display(mat2,row2,col2);printf("\n");

	for(i=0; i<row1; i++)
	{
		for(j=0; j<col2; j++)
		{
			rcArgs[0] = i;
			rcArgs[1] = j;
			rcArgs[2] = col1;

			if(pthread_create(&P[i][j], NULL, mul_thread, rcArgs) != 0)
			{
				printf("\nThread cannot be created !\n");
			}
			else
			{
				printf("\n# Thread (%d : %d) created successfully...\n", i+1, j+1);
				sleep(2);
			}
		}
	}

	for(i=0; i<row1; i++)
	{
		for(j=0; j<col2; j++)
		{
			{

				if(pthread_join(P[i][j], (void **)&status) != 0)
				{
					perror("\nThread cannot be joined !\n");
				}
				mul[i][j] = (long int)status;
			}
		}
	}	

	printf("\nMultithreading done !!!\n");
	printf("\nAnswer : \n");
	display(mul,row1,col2);printf("\n");

	return 0;
}

void display(int mat[100][100],int row,int col)
{
	int i,j;
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			printf("%d ",mat[i][j]);
		}
		printf("\n");
	}
}
