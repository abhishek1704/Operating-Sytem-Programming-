#include <stdio.h>

int main(int argc, char *argv[])
{
	int a[10], i, x, c=0, l, r, mid, m, f = 0;

	printf("\nArray recieved in string format : ");
	for(i = 0; i < argc; i++)
	{
		printf("%c", *argv[i]);
	}
	printf("\n\nArray converted to integer format : ");
	for(i = 0; i < argc; i++)
	{
		a[i] = atoi(argv[i]);
		printf(" %d", a[i]);
	}
	
	printf("\n\nEnter the number to be searched : ");
	scanf("%d", &x);
	
	l = 0; r = i-1;

    while (l <= r) 
    { 
	    m = l + (r - l) / 2; 

	    // Check if x is present at mid 
	    if (a[m] == x) 
	    {
	        f = 1;
	        break; 
	    }

	    // If x greater, ignore left half 
	    if (a[m] < x) 
	        l = m + 1; 

	    // If x is smaller, ignore right half 
	    else
	        r = m - 1; 
	} 

	if (f) printf("\n\nThe number is found at index %d", m);
	else printf("\n\nThe number is not found !");

	return 0;
}
