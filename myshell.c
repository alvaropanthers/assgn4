#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAXIMUM_INPUT 1024

void parseInput();

int main(){
  
  pid_t pid, ppid, nProcess;
  nProcess = fork();
  printf("My  PID is:%d\n\n", (pid = getpid()));
  printf("Par PID is:%d\n\n", (ppid = getppid()));
  parseInput();
  
  execlp("ls", "ls", "-l", (char *)0);
  
  int i;
  if(nProcess > 0){
    //    for(i=0; i < 1000; i++ )
    //      printf("\t\t\tPARENT %d\n", i);
    printf("Parent execution is finished\n");
  }
  else{
    //    for(i=0; i < 1000; i++ )
    //      printf("\t\t\tCHILD %d\n", i);
    printf("Child execution is finished\n");
  }
  
  return 0;
}


void parseInput(){
  char string[MAXIMUM_INPUT];
  strcpy(string, "cp test.txt newFile.txt");
  const char delimeter[2] = " ";
  char *token;

  token = strtok(string, delimeter);

  while(token != NULL){
    printf(" %s\n", token);
    token = strtok(NULL, delimeter);
  }

}
