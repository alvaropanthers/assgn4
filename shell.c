#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAXIMUM_INPUT 1024
#define DELIMITER " "

void parse_input(char **args, int *size);
void start_child(pid_t pid, char **args, int *size);
void print_arguments(char **args, int *size);

int main(){
  pid_t nProcess;
  nProcess = fork();
  if(nProcess < 0){
    printf("error creating new process\n");
    return -1;
  }
  
  int size = 10;
  char **arguments = (char **)malloc(size);

  if(nProcess == 0)
    start_child(nProcess, arguments, &size);
  
  if(nProcess > 0){
    printf("Parent execution is finished\n");
  }
  else{
    printf("Child execution is finished\n");
  }

  wait((int *)0);
  return 0;
}

void start_child(pid_t pid, char **args, int *size){
  parse_input(args, size);
  print_arguments(args, size);

  printf("type = %s\n", args[0]);
  int i;
  if(pid <= 0)
    execvp(args[0], args);    
}

void print_arguments(char **args, int *size){
  int i;
  for(i = 0; i < (*size); ++i)
    printf("%s\n", args[i]);
  
}

void parse_input(char **args, int *size){
  char string[MAXIMUM_INPUT];
  strcpy(string, "echo helloworld!");
  const char delimiter[2] = DELIMITER;
  char *token;

  token = strtok(string, delimiter);

  *size = 0;
  while(token != NULL){
    args[*size] = token;
    *size += 1;
    token = strtok(NULL, delimiter);
  }

  //Shrink block
  args = realloc(args, *size);
}
