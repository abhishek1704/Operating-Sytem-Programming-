
// Reader's priority 

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <semaphore.h>
#define MAX 10

void init();

int rcnt = 0, data = 1;
pthread_mutex_t lock, wlock;

void init()
{
    pthread_mutex_init(&lock, NULL);
    pthread_mutex_init(&wlock, NULL);
}

void *writer(void *args)
{  
	int wid = *(int *) args;

	while(1)
	{
	    sleep(rand()%10 + 1);
	    
	    pthread_mutex_lock(&wlock);
	    printf("\n\t\t\t\t\t# Writer no. %d has entered", wid); 
	    printf("\n\t\t\t\t\t  Writer no. %d has incremented data from %d -> %d", wid, data, data+1); 
	  	data++;

	    // printf("\n\t\t\t\t  Writer no. %d has written a data : %d", wid, data);

	    printf("\n\t\t\t\t\t  Writer no. %d has completed writing, unlocking the resource ....\n", wid);

	    pthread_mutex_unlock(&wlock);
    }

}

void *reader(void *args)
{   
	int rid = *(int *) args;

	while(1)
	{
		sleep(rand()%10 + 1);

	    pthread_mutex_lock(&lock);
	    printf("\n\n# Reader no. %d has entered", rid); 
	    rcnt++;

	    if(rcnt == 1) 
	    {	
	        pthread_mutex_lock(&wlock); 
	        printf("\n  Reader no. %d has blocked all the writers (First reader)", rid);
	    }

	    pthread_mutex_unlock(&lock);

	    printf("\n  Reader no. %d has read a data : %d", rid, data);
		sleep(2);

	    pthread_mutex_lock(&lock);
	    printf("\n  Reader no. %d has locked the resource afer reading ....", rid);
 
	    rcnt--;
	    printf("\n  Reader count : %d\n", rcnt);
	    if(rcnt == 0) 
	    {
	        pthread_mutex_unlock(&wlock); 
	        printf("\n  Now, the resource is freed by reader no. %d (last reader)\n", rid);
	    }    

	    pthread_mutex_unlock(&lock);

    }

}

int main()
{   

    pthread_t rthread[MAX+1], wthread[MAX+1];
    int r, w, i, k = 1;

	printf("\nEnter the number of readers : ");
	scanf("%d", &r);
	printf("\nEnter the number of writers : ");
	scanf("%d", &w);

	init();

    for(i=1; i<=r; i++) 
    {
        pthread_create(&rthread[i], NULL, (void *)reader, (void *)&k);
        k++;
    }
    k = 1;
    for(i=1; i<=w; i++)
    {
        pthread_create(&wthread[i], NULL, (void *)writer, (void *)&k);
        k++;
    }

    for(i=1; i<=r; i++) 
    {
        pthread_join(rthread[i], NULL);
    }

    for(i=1; i<=w; i++)
    {
        pthread_join(wthread[i], NULL);
    }


    return 0;
    
}
