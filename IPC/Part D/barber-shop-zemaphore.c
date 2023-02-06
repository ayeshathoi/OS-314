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
#include "zemaphore.c"
int no_of_chairs;

int total_customer_count;
int customers=0;
int arrived_customer = 0;

// lock for customer count access
zem_t customer_mutex_lock;

// 4 condition variables
zem_t customer_cond;
zem_t barber_cond;
zem_t barber_done_cond;
zem_t customer_done_cond;

void* barber(void* arg) {
    printf("Barber entered\n");

    while (arrived_customer < total_customer_count) {
        // check if there is any customer waiting
        printf("No one detected. Barber is going to sleep.\n");
        
        // waiting so that customer sends signal and wakes up
        zem_down(&customer_cond);
        printf("Barber woke up.\n");

        // notify customer that his turn has come
        zem_up(&barber_cond);

        // printf("Barber %d is cutting hair.\n", id);
        sleep(3);

        // notify customer that barber is done
        zem_up(&barber_done_cond);
        printf("Barber is done.\n");

        // waiting for customer to signal that it is done
        zem_down(&customer_done_cond);

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
    zem_down(&customer_mutex_lock);
    if (customers == no_of_chairs) {
        // update the arrived customer
        balk(id);
        ++arrived_customer;
        //release the lock
        zem_up(&customer_mutex_lock);
        return NULL;
    }
    ++customers;
    printf("Customer %d is waiting.\n", id);
    //sends signal to barber to wake up
    zem_up(&customer_cond);
    //release the lock as customer access complete
    zem_up(&customer_mutex_lock);
    // wait for barber's signal that its this customer's turn
    zem_down(&barber_cond);

    getHairCut(id);

    // wait till barber is done
    zem_down(&barber_done_cond);

    // update customer count
    zem_down(&customer_mutex_lock);
    --customers;
    ++arrived_customer;
    zem_up(&customer_mutex_lock);

    // notify barber that customer is done
    zem_up(&customer_done_cond);
  
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

    
    // initiating 1 because its a lock
    zem_init(&customer_mutex_lock, 1);

    //initiating 0 because these are condition variables
    zem_init(&barber_cond, 0);
    zem_init(&customer_cond, 0);
    zem_init(&barber_done_cond, 0);
    zem_init(&customer_done_cond, 0);
    
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