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

void get_input(char *args, const int SIZE){
  fgets(args, SIZE, stdin);
  char *p = strchr(args, '\n');
  if (p)  *p = 0;
}

void start_child(pid_t pid, char **args, int *size){
  char input[10];
  get_input(input, 10);

  parse_input(args, size, input);
  print_arguments(args, size);

  if(execvp(args[0], args) == -1)
    printf("%s\n", strerror(errno));
}

void print_arguments(char **args, int *size){
  int i;
  for(i = 0; i < (*size); ++i)
    printf("%s\n", args[i]);
  
}

void parse_input(char **args, int *size, char *string){
  const char delimiter[2] = DELIMITER;
  char *token;

  token = strtok(string, delimiter);

  *size = 0;
  while(token != NULL){
    args[*size] = token;
    *size += 1;
    token = strtok(NULL, delimiter);
  }

  args[*size] = NULL;

  //Shrink block
  args = realloc(args, *size);
}
