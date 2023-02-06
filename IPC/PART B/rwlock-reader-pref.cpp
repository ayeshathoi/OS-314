#include "rwlock.h"

void InitalizeReadWriteLock(struct read_write_lock * rw)
{
  rw->readerCount   = 0;
  rw->writerCount   = 0;
  rw->write_present = 0;
  pthread_mutex_init(&rw->lock,NULL);
  pthread_cond_init(&rw->writerCond,NULL);
  pthread_cond_init(&rw->readerCond,NULL);
}

void ReaderLock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->lock);
  while(rw->write_present == 1)
  {
    pthread_cond_wait(&rw->readerCond,&rw->lock);
  }
  rw->readerCount++;
  pthread_mutex_unlock(&rw->lock);

}

void ReaderUnlock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->lock);
	rw->readerCount--;
	if(rw->readerCount==0){
		pthread_cond_broadcast(&rw->writerCond);	
	}
	pthread_mutex_unlock(&rw->lock);

}

void WriterLock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->lock);
	while(rw->readerCount > 0 || rw->write_present == 1)
		pthread_cond_wait(&rw->writerCond,&rw->lock);
	rw->write_present=1;
	pthread_mutex_unlock(&rw->lock);
}

void WriterUnlock(struct read_write_lock * rw)
{
  pthread_mutex_lock(&rw->lock);
	rw->write_present=0;
	pthread_cond_broadcast(&rw->readerCond);
	pthread_cond_signal(&rw->writerCond);
	pthread_mutex_unlock(&rw->lock);
  
}

