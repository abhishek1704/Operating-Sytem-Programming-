#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#define MAX 100

int partition (int arr[], int low, int high); 
int merge(int a[],int start,int mid,int end);
void quickSort(int arr[], int low, int high);
void mergeSort(int a[],int start,int end);

void display(int a[],int n)
{
	int i;
	
	for(i=0;i<n;i++)
	{
		printf("%d ",a[i]);
	}
}

void swap(int *a,int *b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

// Quick sort
int partition (int arr[], int low, int high)  
{  
    int pivot = arr[high]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  

void quickSort(int arr[], int low, int high)  
{  
    if (low < high)  
    {  
        int pi = partition(arr, low, high);  
  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}			

// Merge sort
void mergeSort(int a[],int start,int end)
{
	int mid;
	
	if(start<end)
	{
		mid = (start+end)/2;
		mergeSort(a,start,mid);
		mergeSort(a,mid+1,end);
		merge(a,start,mid,end);
	}
}	

int merge(int a[],int start,int mid,int end)
{
	int i,j,c[30],k=0;
	
	i = start;
	j = mid+1;
	
	while(i<=mid && j<=end)
	{
		if(a[i]<a[j])
		{
			c[k] = a[i];
			k++;i++;
		}
		else
		{
			c[k] = a[j];
			k++;j++;
		}
	}
	
	while(i<=mid)
	{
		c[k] = a[i];
		k++;i++;
	}
	
	while(j<=end)
	{
		c[k] = a[j];
		k++;j++;
	}
	
	for(i=start,j=0;i<=end;i++,j++)
	{
		a[i] = c[j];
	}
		
}
			

int main()
{
	int i, n, a[MAX], pid, id;
	
	printf("\nEnter the size of the array : ");
	scanf("%d",&n);
	
	printf("\nEnter the elememts : ");

	for(i=0; i<n; i++)
		scanf("%d",&a[i]);


	id = fork();
	printf("\n-------------------------------\n");	
	printf("\n  fork done, id : %d\n", id);

	if(id == 0)
	{

		printf("\n# In the child process...\n");
		printf("# Parent id : %d\n", getppid());
		printf("# Child is going to sleep...\n");
		printf("# Sorting by quickSort....\n");
    	quickSort(a, 0, n - 1);  
		printf("# Elements after sorting by child : \n"); 
		for(i=0;i<n;i++)
		{
			printf("  %d",a[i]);
		}	
		printf("\n\n# Child process is completed !\n");
	}
	else
	{	

		printf("\n- In the parent process...\n");
		printf("- Parent id : %d\n", getpid());
		printf("- Sorting by mergeSort....\n");
		mergeSort(a,0,n-1);
		printf("- Elements after sorting by parent : \n"); 
		for(i=0;i<n;i++)
		{
			printf("  %d",a[i]);
		}	
		printf("\n\n- Parent is going for wait call....\n");	
		wait(0);
		printf("\n-------------------------------\n");
		printf("\n- Now child process is completed, parent is free to exit !\n");
	}	

	return 0;	
}
