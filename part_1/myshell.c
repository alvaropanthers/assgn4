/*

##########################################################

## COP4338– Programming III – Summer C 2018

## Prof. Jose F. Osorio

## Student: alvaro orozco - 6072686

##

## Assignment #: 4

## Specs: Part 1 – Command Line Shell

## Due Date: 07/20/2018 by 11:55pm

##

## Module Name: myshell.c

##

## I Certify that this program code has been written by me

## and no part of it has been taken from any sources.

##########################################################
     */
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAXIMUM_INPUT 1024
#define DELIMITER " "

void parse_input(char **args, int *size, char *string, int *amp);
void start_child(pid_t pid, char **args);
void print_arguments(char **args, int *size);
void get_input(char *args, const int SIZE);
void input_handler(char **args, int *size, int *amp);
pid_t start_process();
void shell_body(char **args, int amp);

int main(){
  int count = 0;
  while(count < 10){
    //Input stuff
    int size = MAXIMUM_INPUT / 2;
    char **arguments = (char **)malloc(size);
    int amp = 0;
    input_handler(arguments, &size, &amp);
    //End of input stuff

    shell_body(arguments, amp);
    
    setbuf(stdout, 0);
    setbuf(stderr, 0);

    free(arguments);
    
    ++count;
  }
  return 0;
}

void shell_body(char **args, int amp){
   if(strcmp(args[0], "cd") == 0){
      chdir(args[1]);
    }else if(strcmp(args[0], "exit") == 0){
      exit(0);
    }else if(strcmp(args[0], "wait") == 0){
      wait((int *)0);
    }else{
      pid_t pid = start_process();
    
      if(pid == 0)
	start_child(pid, args);

      if(!amp){
	int status;
	waitpid(pid, &status, WUNTRACED);
      }
    
    }

}

pid_t start_process(){
   pid_t pid;
   pid = fork();
   if(pid < 0){
     printf("error creating new process\n");
     return -1;
   }
   return pid;
}

void input_handler(char **args, int *size, int *amp){
    char input[MAXIMUM_INPUT];
    get_input(input, MAXIMUM_INPUT);
    parse_input(args, size, input, amp);
}

void get_input(char *args, const int SIZE){
  printf("shell>");
  fgets(args, SIZE, stdin);
  //Removing first instance of \n
  char *p = strchr(args, '\n');
  if (p)  *p = 0;
}

void start_child(pid_t pid, char **args){
  if(execvp(args[0], args) == -1)
    printf("%s\n", strerror(errno));
}

void parse_input(char **args, int *size, char *string, int *amp){
  char *token;
  token = strtok(string, DELIMITER);

  *size = 0;
  while(token != NULL){
    args[*size] = token;
    *size += 1;
    token = strtok(NULL, DELIMITER);
  }

  if(strcmp(args[*size - 1], "&") == 0){
    *amp = 1;
    args[*size - 1] = NULL;
    --(*size);
  }else
    args[*size] = NULL;
}

void print_arguments(char **args, int *size){
  int i;
  for(i = 0; i < (*size); ++i)
    printf("%s\n", args[i]);
}

