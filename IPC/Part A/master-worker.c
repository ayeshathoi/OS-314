#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include <pthread.h>
#include <unistd.h>


int item_to_produce, item_to_consume, curr_buf_size;
int total_items, max_buf_size, num_workers, num_masters;

int *buffer;
int fill_index=0;
int use_index=0;

//lock and condition variables
pthread_mutex_t lock;
pthread_cond_t empty;
pthread_cond_t fill;

void print_produced(int num, int master) {

  printf("Produced %d by master %d\n", num, master);
}

void print_consumed(int num, int worker) {

  printf("Consumed %d by worker %d\n", num, worker);
  
}


//produce items and place in buffer
//modify code below to synchronize correctly
void *generate_requests_loop(void *data)
{
  int thread_id = *((int *)data);

  while(1)
    {
      //lock the thread
      pthread_mutex_lock(&lock);

      //check if the buffer is full
      while(curr_buf_size == max_buf_size) {
        if(item_to_produce<total_items)
        {
          //if full, wait for the buffer to be empty
          pthread_cond_wait(&empty, &lock);
        }
        else
          break;
      }
      
      if(item_to_produce >= total_items) {
        // max item limit exceeded.. break
        // as no more items to produce, wake up all the consumers to that no one remains sleeping
        pthread_cond_broadcast(&fill);
	      pthread_mutex_unlock(&lock);
        break;
      }
      // now find an empty slot in the buffer and add the item
      for(int i=0;i<max_buf_size;i++) {
        if(buffer[i] == -1) {
          buffer[i] = item_to_produce;
          break;
        }
      }
      print_produced(item_to_produce, thread_id);
      curr_buf_size++;
      item_to_produce++;
      //send signal that buffer is filled
      pthread_cond_signal(&fill);
      pthread_mutex_unlock(&lock);
    }
  return 0;
}
void *consume_requests_loop(void *data)
{
  int thread_id = *((int *)data);
  int item;
  while(1)
    {
      //lock the thread
      pthread_mutex_lock(&lock);

      //check if the buffer is empty
      while(curr_buf_size == 0) {
        if(item_to_consume<total_items)
        {
         //if empty, wait for the buffer to be filled
         pthread_cond_wait(&fill, &lock);
        }
        else
           break;
      }

      if(item_to_consume == total_items) {
        // max item limit exceeded and all items consumed.. break
        // as there are no more to produce,wake up all producers to that no one remains sleeping
        pthread_cond_broadcast(&empty);
        pthread_mutex_unlock(&lock);
        break;
      }
 
      //now find a filled slot in the buffer and remove the item
      for(int i=0;i<max_buf_size;i++) {
        if(buffer[i] != -1) {
          item = buffer[i];
          // make it empty
          buffer[i] = -1;
          break;
        }
      }
      item_to_consume++;
      curr_buf_size--;  
      print_consumed(item, thread_id);
      pthread_cond_signal(&empty);
      pthread_mutex_unlock(&lock);
    }
  return 0;
}

//write function to be run by worker threads
//ensure that the workers call the function print_consumed when they consume an item

int main(int argc, char *argv[])
{
  //create arrays to track the master and worker id
  int *master_thread_id;
  int *worker_thread_id;

  //create master and producer threads
  pthread_t *master_thread;
  pthread_t *worker_thread;


  item_to_produce = 0;
  item_to_consume = 0;
  curr_buf_size = 0;
  int i;

  //initialization of lock and condition variables
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&empty, NULL);
  pthread_cond_init(&fill, NULL);
  
   if (argc < 5) {
    printf("./master-worker #total_items #max_buf_size #num_workers #masters e.g. ./exe 10000 1000 4 3\n");
    exit(1);
  }
  else {
    total_items = atoi(argv[1]);
    max_buf_size = atoi(argv[2]);
    num_workers = atoi(argv[3]);
    num_masters = atoi(argv[4]);
  }
    
  // initiaize buffer
   buffer = (int *)malloc (sizeof(int) * max_buf_size);
   for(int i =0 ;i<max_buf_size;i++) {
     buffer[i] = -1;
   }

  //creating master and producer thread ids
   master_thread_id = (int *)malloc(sizeof(int) * num_masters);
   worker_thread_id = (int *)malloc(sizeof(int) * num_workers);
  
  
  //creating master and worker threads
   master_thread = (pthread_t *)malloc(sizeof(pthread_t) * num_masters);
   worker_thread = (pthread_t *)malloc(sizeof(pthread_t) * num_workers);

  for (i = 0; i < num_masters; i++)
    master_thread_id[i] = i;

  for (i = 0; i < num_workers; i++)
    worker_thread_id[i] = i;  

   //create master producer threads  
  for (i = 0; i < num_masters; i++)
  {
    int result = pthread_create(&master_thread[i], NULL, generate_requests_loop, (void *)&master_thread_id[i]);
     if (result != 0) {
      printf("Error creating master thread %d\n", i);
      exit(EXIT_FAILURE);
    }
  }
  //create worker consumer threads
  for (i = 0; i < num_workers; i++)
  {
    int result = pthread_create(&worker_thread[i], NULL, consume_requests_loop, (void *)&worker_thread_id[i]);
     if (result != 0) {
      printf("Error creating worker thread %d \n", i);
      exit(EXIT_FAILURE);
    }
  }

  //wait for all threads to complete
  for (i = 0; i < num_masters; i++)
    {
      pthread_join(master_thread[i], NULL);
      printf("master %d joined\n", i);
    }
  for (i = 0; i < num_workers; i++)
    {
      pthread_join(worker_thread[i], NULL);
      printf("worker %d joined \n", i);
    }
  
  /*----Deallocating Buffers---------------------*/
  free(buffer);
  free(master_thread_id);
  free(master_thread);

  free(worker_thread_id);
  free(worker_thread);
  /*---------------------------------------------*/
  //destroy lock and condition variables
  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&empty);
  pthread_cond_destroy(&fill);
  
  return 0;
}