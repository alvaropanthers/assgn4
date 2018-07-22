/*

##########################################################

## COP4338– Programming III – Summer C 2018

## Prof. Jose F. Osorio

## Student: alvaro orozco – 6072586

##

## Assignment #: 4

## Specs: Part 3 – openmp

## Due Date: 07/20/2018 by 11:55pm

##

## Module Name: main.c

##

## I Certify that this program code has been written by me

## and no part of it has been taken from any sources.

##########################################################
*/
#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

int currentStudent;
int totalStudents;

void answerStart();
void answerDone();
void questionStart();
void questionDone();
void enterOffice();
void leaveOffice();
void professor();
int isNumber(char number[]);

void student(int id){
  
  #pragma omp critical
  {
    currentStudent = id;
    enterOffice();
    ++totalStudents;
  }

  int size = (id % 4) + 1;
  int nthreads = omp_get_num_threads();
  for(int aQuestions = 0; aQuestions <= nthreads; aQuestions++){
    if(aQuestions < size){
      #pragma omp critical
      {
	currentStudent = omp_get_thread_num();
	questionStart();
	professor();
	questionDone();
      }
    }
      
    if(aQuestions == size){
      #pragma omp critical
      {
	currentStudent = id;
	leaveOffice();
	--totalStudents;
      }	
    }

    #pragma omp barrier

  }
}

int main(int argc, char **args){
  if(argc < 2){
    printf("Must enter two arguments of type (int) (int)\n");
    return -1;
  }

  for(int i = 1; i < argc; ++i){
    if(!isNumber(args[i])){
	printf("params must be of type (int)\n");
	exit(0);
      }
  }

  int threads = atoi(args[1]);
  int maxCapacity = atoi(args[2]);

  omp_set_num_threads(threads);

  int id = 0;
  #pragma omp parallel private(id)
  {
    id = omp_get_thread_num();
    student(id);
  }

  return 0;
}

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

void answerStart(){
  printf("Professor starts to answer questions for student %d\n", currentStudent);
}

void answerDone(){
  printf("Professor is done with answer for student %d\n", currentStudent);
}

void questionStart(){
  printf("Student %d asks a question\n", currentStudent);
}

void questionDone(){
  printf("Student %d is satisfy\n", currentStudent);
}

void enterOffice(){
  printf("Student %d enters office\n", currentStudent);
}

void leaveOffice(){
  printf("Student %d leaves office\n", currentStudent);
}

void professor(){
  answerStart();
  answerDone();
}
