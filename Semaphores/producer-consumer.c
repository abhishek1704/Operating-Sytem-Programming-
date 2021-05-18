#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define bufferSize 5

int out =0;
int in =0;
int buffer[bufferSize];
sem_t full;
sem_t empty;
	
pthread_mutex_t lock;
//int count =0;
int item=1;

void *Producer( void* pno)
{
	int q, value, z;
	q= *(int *) pno;
	while(1)
	{
		z = (rand()%10)+1;
		sleep(z);
		sem_wait(&empty);
		sem_getvalue(&empty, &value);
		
		pthread_mutex_lock(&lock);
		printf("\nProducer %d: produced %d item", q, item);
		buffer[(in++)%bufferSize]=item++;
		printf("\nBuffer : [ ");
		for(int i=0; i< bufferSize; i++)
			printf("%d ", buffer[i]);
		printf("]\n");
		if(value == 0)
		{
			printf("\n------ BUFFER FULL ------.");
			printf("\nProducers are now waiting for consumers to consume\n", q);
		}
		printf("producer %d exited\n", q);
		pthread_mutex_unlock(&lock);
		sem_post(&full); 				 
	}
	pthread_exit(0);
}

void *Consumer( void* cno)
{
	int q, value, z, top;//ount=0;
	q= *(int *) cno;
	while(1)
	{
		
		z = (rand()%10)+1;
		sleep(z);
		sem_wait(&full);
		sem_getvalue(&full, &value);			
		pthread_mutex_lock(&lock);
		top = buffer[(out++)%bufferSize];
		int s = out-1;
		buffer[(s)%bufferSize]=0;
		printf("\nConsumer %d consume %d items", q,top) ;
		printf("\nBuffer : [ ");
		int count=0;
		for(int i=0; i< bufferSize; i++)
		{
			printf("%d ", buffer[i]);
			if(buffer[i]==0)
			 count++;
		}
		printf("]\n");
//		printf("count = %d", count);
		if(count == bufferSize)
		{
			printf("-------BUFFER EMPTY-------.");
			printf("\nConsumers are now waiting for producers to produce items\n");
			count=0;
		}
		printf("Consumer %d exited\n", q);
		pthread_mutex_unlock(&lock);
		sem_post(&empty); 				 
	}
	pthread_exit(0);
}

int main()
{
	int  np, nc;
	pthread_t pro[bufferSize], con[bufferSize];
	pthread_mutex_init(&lock, NULL);
	sem_init(&empty, 0, bufferSize);
	sem_init(&full, 0, 0);
	int arr[]={ 1, 2, 3, 4, 5};
	
	printf("\nEnter no of producer :");
	scanf("%d", &np);
	
	printf("\nEnter no of consumer : ");
	scanf("%d", &nc);
	
	for(int i =0 ; i< np ;++i)
	{		
		if(pthread_create(&pro[i], NULL, Producer, &arr[i])!=0)
		 	printf("\nCannot create thread.\n");
		else
			printf("\nProducer %d entered ...\n", i+1);

	}
	
	for(int i =0 ; i< np ;i++)
	{		
		if(pthread_create(&con[i], NULL, Consumer, &arr[i])!=0)
		 	printf("\nCannot create thread.\n");
		else
		 	printf("\nConsumer %d entered ...\n", i+1);

	}
	
	for(int i =0 ; i< np ;i++)
	{
		pthread_join(pro[i], NULL);
		printf("\n------ Thread for producer %d joined at End.\n",i+1);
	}
	
	for(int i =0 ; i< np ;i++)
	{
		pthread_join(con[i], NULL);
		printf("\n------ Thread for consumer %d joined at End.\n",i+1);
	}
	
	return 0;
}
