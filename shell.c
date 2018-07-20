#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAXIMUM_INPUT 1024

void parseInput(char **args);

int main(){
  pid_t nProcess;
  nProcess = fork();

  char *arguments[10];
  parseInput(arguments);
  if(nProcess <= 0)
    execlp(arguments[0], arguments[0], arguments[1], arguments[2], (char *)0);    
  
  if(nProcess > 0){
    printf("Parent execution is finished\n");
  }
  else{
    printf("Child execution is finished\n");
  }

  wait((int *)0);
  return 0;
}


void parseInput(char **args){
  char string[MAXIMUM_INPUT];
  strcpy(string, "cp file.txt file2.txt");
  const char delimiter[2] = " ";
  char *token;

  token = strtok(string, delimiter);

  int counter = 0;
  while(token != NULL){
    args[counter] = token;
    ++counter;
    token = strtok(NULL, delimiter);
  }

  int i;
  for(i = 0; i < counter; ++i){
    printf("%s\n", args[i]);
  }

}
