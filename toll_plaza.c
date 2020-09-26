#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>


#define MaxCars 5 // Maximum cars the vehicles can toll check
#define BufferSize 5 
sem_t empty;
sem_t full;
int vehicle_in = 0;
int vehicle_out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *vehicle_arrived(void *a_no)
{   
    int car_no;
    for(int i = 0; i < MaxCars; i++) {
        car_no= rand();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[vehicle_in] = car_no;
        printf("Car %d: ID %d at queue %d\n", *((int *)a_no),buffer[vehicle_in],vehicle_in);
        vehicle_in = (vehicle_in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *toll_checked(void *c_no)
{   
    for(int i = 0; i < MaxCars; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int car_no = buffer[vehicle_out];
        printf("Car %d: checked id %d at queue %d\n",*((int *)c_no),car_no, vehicle_out);
        vehicle_out = (vehicle_out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{   

    pthread_t arr[5],check[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    int vec[5] = {1,2,3,4,5}; 

    for(int i = 0; i < 5; i++) {
        pthread_create(&arr[i], NULL, (void *)vehicle_arrived, (void *)&vec[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&check[i], NULL, (void *)toll_checked, (void *)&vec[i]);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(arr[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(check[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
    
}
