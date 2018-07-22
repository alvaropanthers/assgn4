/*

##########################################################

## COP4338– Programming III – Summer C 2018

## Prof. Jose F. Osorio

## Student: alvaro orozco - 6072586

##

## Assignment #: 4

## Specs: Part 2.b – pthread

## Due Date: 07/20/2018 by 11:55pm

##

## Module Name: task2b.c

##

## I Certify that this program code has been written by me

## and no part of it has been taken from any sources.

##########################################################
     */
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int SharedVariable = 0;

#ifdef PTHREAD_SYNC
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
#endif

int isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        if (number[i] > '9' || number[i] < '0')
           return 0;
    }
    return 1;
}


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

  for(int i = 1; i < argc; ++i){
    if(!isNumber(argv[i])){
	printf("params must be of type (int)\n");
	exit(0);
      }
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
