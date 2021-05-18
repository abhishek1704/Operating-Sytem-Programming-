
#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
  
#define N 5 
#define Thinking 2 
#define Hungry 1 
#define Eating 0 
#define Left (i + 4) % N 
#define Right (i + 1) % N 
 
void display_status(); 
int state[N], eat_status[N]={0}; 
int phil[N] = { 0, 1, 2, 3, 4 }; 
  
sem_t mutex; 
sem_t S[N]; 
  
void test(int i) 
{ 
    if (state[i] == Hungry && state[Left] != Eating && state[Right] != Eating) 
    { 
        state[i] = Eating; 
        eat_status[i]++;
        sleep(2);   

        printf("\n  After ensuring others are not eating, philosopher no. %d started eating !\n", i+1);
        display_status();

        sem_post(&S[i]); 
    } 
    else
    {
        int j=0, tempeat[N]={0};
        // printf("\n  #### Philosophers %d or %d are eating, %d can't eat right now ! ####\n", Left+1, Right+1, i+1);
        printf("\n#### As philosopher no. ");
        for (j=0; j<N; j++)
        {
            if (state[j] == Eating)
            {
                if (j == Left || j == Right)
                    printf("%d ", j+1);
            }
        }
        printf("eating, %d can't eat ####\n", i+1);
    }
} 
  
void take_fork(int i) 
{   
    sem_wait(&mutex); 
  
    state[i] = Hungry; 
  
    printf("\n  Philosopher no. %d is hungry !\n", i+1);
  
    test(i); 
  
    sem_post(&mutex); 

   	sem_wait(&S[i]);   
    sleep(1); 
} 
  
void put_fork(int i) 
{   
    sem_wait(&mutex); 
  
    int r = 0;
    state[i] = Thinking;   


    printf("\n  Philosopher no. %d is putting forks %d and %d down !\n", i+1, Left+1, Right); 
 
    printf("\n  Philosopher %d is Thinking now ....\n", i + 1); 
  
    test(Left); 
    test(Right); 
  
    sem_post(&mutex); 
} 
  
void* philospher(void* num) 
{ 
  
    while (1) { 
  
        int* i = num;   
        sleep(1);   
        take_fork(*i); 

        sleep(0);   
        put_fork(*i); 
    } 
} 

void display_status()
{
    int i=0;
    char avForks[N];

    for(i=0; i<N; i++)
    {
        avForks[i] = 'A';     
    }
    for(i=1; i<N; i++)
    {
        if (state[i] == 0 && state[i+1] != 0 && state[i-1] != 0)
            avForks[i-1] = avForks[i] = 'N';       
    }
    if(state[0] == 0 && state[1] != 0 && state[N-1] != 0)
    {
        avForks[0] = avForks[N-1] = 'N';
    }

    printf("\n------------------------------------------------------------\n");
    printf("Philosopher\t");
    for(i=0; i<N; i++)
        printf(" %d\t", i+1);
    printf("\n------------------------------------------------------------");
    printf("\n");
    printf("State\t\t");
    for(i=0; i<N; i++)
    {
        if (state[i] == 0)
            printf(" E\t");
        else if (state[i] == 1)
            printf(" H\t");
        else
            printf(" T\t");           
    }
    printf("\n------------------------------------------------------------");
    printf("\n");  
    printf("Available forks\t    ");
    for(i=0; i<N; i++)
    {
        printf(" %c\t    ", avForks[i]);     
    }
    printf("\n------------------------------------------------------------");
    printf("\n");  
    printf("No. of eats\t");
    for(i=0; i<N; i++)
        printf(" %d\t", eat_status[i]);
    printf("\n------------------------------------------------------------\n");
    
}

int main() 
{ 
  
    int i; 
    pthread_t thread_id[N]; 
  
    sem_init(&mutex, 0, 1); 
  
    for (i = 0; i < N; i++)   
        sem_init(&S[i], 0, 0); 
  
    for (i = 0; i < N; i++) 
    { 
          pthread_create(&thread_id[i], NULL, philospher, &phil[i]);   
        printf("\n# Philosopher no. %d has entered and started thinking....\n", i+1);
    } 
  
    for (i = 0; i < N; i++) 
  
        pthread_join(thread_id[i], NULL); 
} 
