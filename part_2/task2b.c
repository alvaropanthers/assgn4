#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int SharedVariable = 0;

#ifdef PTHREAD_SYNC
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
#endif

void *SimpleThread(void *param) { 
  int *w = (int *)param;
  int which = *w;
  int num, val = 0;

  for (num = 0; num < 20; num++) { 
    if (random() > RAND_MAX / 2) 
      usleep(10);
    //LOCK
    #ifdef PTHREAD_SYNC
    pthread_mutex_lock(&mutex);
    #endif
    val = SharedVariable;
    printf("*** thread %d sees value %d\n", which, val);
    SharedVariable = val + 1;
    #ifdef PTHREAD_SYNC
    pthread_mutex_unlock(&mutex);
    #endif
    //UNLOCK
  }

  #ifdef PTHREAD_SYNC
  pthread_barrier_wait(&barrier);
  #endif
  val = SharedVariable;
  printf("Thread %d sees final value %d\n", which, val);
}

int main(int argc, char **argv){

  if(argc != 2){
    printf("Must enter one param of type (int)\n");
    exit(-1);
  }
  
  int length = atoi(argv[argc - 1]);
  pthread_t pthread[length];
  int pthreadIds[length];

  #ifdef PTHREAD_SYNC
  pthread_mutex_init(&mutex, NULL);
  pthread_barrier_init(&barrier, NULL, length);
  #endif
  
  int i;
  for(i = 0; i < length; ++i){
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthreadIds[i] = i;
    pthread_create(&pthread[i], &attr, SimpleThread, &pthreadIds[i]);
  }

  for(i = 0; i < length; ++i){
    pthread_join(pthread[i], NULL);
  }

  return 0;
}
