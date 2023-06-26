/*Scrivere un programma POSIX C che crei una pipe che esegua il comando ls -l | wc -w*/ 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char *argv){
  int pipefd[2];
  pid_t pidFiglio;
  if(pidFiglio = fork() == -1){
    perror("fork");
  }
  if(pidFiglio == 0){
    execve("ls","ls","-l",NULL);
  }else{
    execve("wc","wc","-w",NULL);
  }
  return 0;
}
