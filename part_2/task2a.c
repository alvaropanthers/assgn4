#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int SharedVariable = 0;

void *SimpleThread(void *param) { 
  int *w = (int *)param;
  int which = *w;
  int num, val = 0;

  for (num = 0; num < 20; num++) { 
    if (random() > RAND_MAX / 2) 
      usleep(10);
    val = SharedVariable;
    printf("*** thread %d sees value %d\n", which, val);
    SharedVariable = val + 1;
  }
  val = SharedVariable;
  printf("Thread %d sees final value %d\n", which, val);
}

void printargs(int argc, char **argv){
  int i;
  for(i = 0; i < argc; ++i)
    printf("%d\n", atoi(argv[i]));
}

int main(int argc, char **argv){

  if(argc != 2){
    printf("Must enter one param of type (int)\n");
    exit(-1);
  }
  
  int length = atoi(argv[argc - 1]);
  pthread_t pthread[length];
  
  int i;
  for(i = 0; i < length; ++i){
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&pthread[i], &attr, SimpleThread, &pthread[i]);
  }

  for(i = 0; i < length; ++i){
    pthread_join(pthread[i], NULL);
  }

  return 0;
}
