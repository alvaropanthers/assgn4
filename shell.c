#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAXIMUM_INPUT 1024
#define DELIMITER " "

void parse_input(char **args, int *size, char *string);
void start_child(pid_t pid, char **args, int *size);
void print_arguments(char **args, int *size);
void get_input(char *args, const int SIZE);

int main(){

  while(1){
    pid_t nProcess;
    nProcess = fork();
    if(nProcess < 0){
      printf("error creating new process\n");
      return -1;
    }
  
    int size = MAXIMUM_INPUT / 2;
    char **arguments = (char **)malloc(size);

  
    if(nProcess == 0)
      start_child(nProcess, arguments, &size);
    
    wait((int *)0);
  }
  return 0;
}

void start_child(pid_t pid, char **args, int *size){
  char input[MAXIMUM_INPUT];
  get_input(input, MAXIMUM_INPUT);

  parse_input(args, size, input);

  if(execvp(args[0], args) == -1)
    printf("%s\n", strerror(errno));
}

void parse_input(char **args, int *size, char *string){
  char *token;
  token = strtok(string, DELIMITER);

  *size = 0;
  while(token != NULL){
    args[*size] = token;
    *size += 1;
    token = strtok(NULL, DELIMITER);
  }

  args[*size] = NULL;
}

void get_input(char *args, const int SIZE){
  printf("shell>");
  fgets(args, SIZE, stdin);
  //Removing first instance of \n
  char *p = strchr(args, '\n');
  if (p)  *p = 0;
}

void print_arguments(char **args, int *size){
  int i;
  for(i = 0; i < (*size); ++i)
    printf("%s\n", args[i]);
}

