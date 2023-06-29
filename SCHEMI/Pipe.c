/*Scrivere un programma POSIX C che implementi la pipe ls -l | wc -w*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    int fd[2];
    pid_t pid1, pid2;
    if (pipe(fd) < 0)
        perror("pipe error"), exit(1);
    else if ((pid1 = fork()) < 0)
        perror("fork error"), exit(1);
    else if (pid1 == 0){
        /* ls */
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", "-l", (char *)0);
        perror("exec ls");
        exit(1);
    }
    else if ((pid2 = fork()) < 0)
        perror("fork error"), exit(1);
    else if (pid2 == 0){
        /* wc */
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("wc", "wc", "-w", (char *)0);
        perror("exec wc");
        exit(1);
    }
    else{
        close(fd[0]);
        close(fd[1]);
    }
    return 0;
}
