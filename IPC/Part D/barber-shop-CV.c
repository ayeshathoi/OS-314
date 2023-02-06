/**
 * The Sleeping Barber Problem
 * A barbershop consists of a waiting room with n chairs, and the
 * barber room containing the barber chair. If there are no customers
 * to be served, the barber goes to sleep. If a customer enters the
 * barbershop and all chairs are occupied, then the customer leaves
 * the shop. If the barber is busy, but chairs are available, then the
 * customer sits in one of the free chairs. If the barber is asleep, the
 * customer wakes up the barber. Write a program to coordinate the
 * barber and the customers.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
int no_of_chairs;

int total_customer_count;
int customers=0;
int arrived_customer = 0;

// defining values
int customer_cond_val;
int barber_cond_val;
int barber_done_val;
int customer_done_val;

// lock for customer count access
pthread_mutex_t customer_mutex_lock;
pthread_mutex_t customer_cond_lock;
pthread_mutex_t barber_cond_lock;
pthread_mutex_t barber_done_lock;
pthread_mutex_t customer_done_lock;

// 4 condition variables
pthread_cond_t customer_cond;
pthread_cond_t barber_cond;
pthread_cond_t barber_done_cond;
pthread_cond_t customer_done_cond;


void* barber(void* arg) {
    printf("Barber entered\n");

    while (arrived_customer < total_customer_count) {
        // check if there is any customer waiting
        printf("No one detected. Barber is going to sleep.\n");
        
        // waiting so that customer sends signal and wakes up
        
        pthread_mutex_lock(&customer_cond_lock);
        while(customer_cond_val<=0)
        {
            pthread_cond_wait(&customer_cond,&customer_cond_lock);
        }
        customer_cond_val--;
        pthread_mutex_unlock(&customer_cond_lock);
        
        printf("Barber woke up.\n");

        // notify customer that his turn has come
        
        pthread_mutex_lock(&barber_cond_lock);
        barber_cond_val++;
        pthread_cond_signal(&barber_cond);
        pthread_mutex_unlock(&barber_cond_lock);

        // printf("Barber %d is cutting hair.\n", id);
        sleep(3);
        
        // notify customer that barber is done
        
        pthread_mutex_lock(&barber_done_lock);
        barber_done_val++;
        pthread_cond_signal(&barber_done_cond);
        pthread_mutex_unlock(&barber_done_lock);
        printf("Barber is done.\n");

        // waiting for customer to signal that it is done
        pthread_mutex_lock(&customer_done_lock);
        while(customer_done_val<=0)
        {
            pthread_cond_wait(&customer_done_cond,&customer_done_lock);
        }
        customer_done_val--;
        pthread_mutex_unlock(&customer_done_lock);

    }

    printf("All customers gone. Barber is leaving the shop.\n");
    return NULL;
}
void balk(int id){
     printf("All chairs are occupied. Customer %d left\n", id);
}
void getHairCut(int id){
     printf("Customer %d is getting a haircut.\n", id);
}
void* customer(void* arg) {
    int id = *((int*) arg);
    printf("Customer %d arrived\n", id);

    //lock for customer variable access
    // zem_down(&customer_mutex_lock);
    pthread_mutex_lock(&customer_mutex_lock);
    if (customers == no_of_chairs) {
        // update the arrived customer
        balk(id);
        ++arrived_customer;
        //release the lock
        pthread_mutex_unlock(&customer_mutex_lock);
        return NULL;
    }
    ++customers;
    printf("Customer %d is waiting.\n", id);

    //sends signal to barber to wake up
    pthread_mutex_lock(&customer_cond_lock);
    customer_cond_val++;
    pthread_cond_signal(&customer_cond);
    pthread_mutex_unlock(&customer_cond_lock);

    //release the lock as customer access complete
    pthread_mutex_unlock(&customer_mutex_lock);
    
    // wait for barber's signal that its this customer's turn
    pthread_mutex_lock(&barber_cond_lock);
    while(barber_cond_val<=0)
    {
        pthread_cond_wait(&barber_cond,&barber_cond_lock);
    }
    barber_cond_val--;
    pthread_mutex_unlock(&barber_cond_lock);

    getHairCut(id);

    // wait till barber is done
    pthread_mutex_lock(&barber_done_lock);
    while(barber_done_val<=0)
    {
        pthread_cond_wait(&barber_done_cond,&barber_done_lock);
    }
    barber_done_val--;
    pthread_mutex_unlock(&barber_done_lock);

    // update customer count
    pthread_mutex_lock(&customer_mutex_lock);
    --customers;
    ++arrived_customer;
    pthread_mutex_unlock(&customer_mutex_lock);

    // notify barber that customer is done

    pthread_mutex_lock(&customer_done_lock);
    customer_done_val++;
    pthread_cond_signal(&customer_done_cond);
    pthread_mutex_unlock(&customer_done_lock);
 
    printf("Customer %d is leaving the shop.\n", id);
    return NULL;
}

int main(int argc, char* argv[]) {

    //creating barber thread and customer threads
    pthread_t barber_thread;
    pthread_t *customer_threads;

     //create arrays to track the customers id
    int *customer_thread_id;
    int i;

    
    pthread_mutex_init(&customer_mutex_lock, NULL);
    pthread_mutex_init(&customer_cond_lock, NULL);
    pthread_mutex_init(&barber_cond_lock, NULL);
    pthread_mutex_init(&customer_done_lock, NULL);
    pthread_mutex_init(&barber_done_lock, NULL);

    pthread_cond_init(&customer_cond, NULL);
    pthread_cond_init(&barber_cond, NULL);
    pthread_cond_init(&customer_done_cond, NULL);
    pthread_cond_init(&barber_done_cond, NULL);

    customer_cond_val = 0;
    barber_cond_val = 0;
    customer_done_val = 0;
    barber_done_val = 0;

    
    if (argc < 3) {
        printf("Invalid Arguments: ./barber-shoop #total_customer_count #no_of_chairs\n");
        return 1;
    }
    else
    {
        total_customer_count = atoi(argv[1]);
        no_of_chairs = atoi(argv[2]);
    }


  //creating customer thread ids
   customer_thread_id = (int *)malloc(sizeof(int) * total_customer_count);
  
  //creating customer threads
   customer_threads = (pthread_t *)malloc(sizeof(pthread_t) * total_customer_count);

   for(i = 0; i < total_customer_count; i++)
    customer_thread_id[i] = i;  

   //create barber thread
    pthread_create(&barber_thread, NULL, barber, NULL);

   //create customer threads
    for (i = 0; i < total_customer_count; i++)
    {
        pthread_create(&customer_threads[i], NULL, customer,(void*) &customer_thread_id[i]);
        sleep(rand() % 3);
    }

    //wait for all threads to complete
    pthread_join(barber_thread, NULL);
    printf("barber joined\n");
    
    for (i = 0; i < total_customer_count; i++)
    {
      pthread_join(customer_threads[i], NULL);
      printf("customer %d joined \n", i);
    }

    printf("All done\n");
    return 0;
}