#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int nsig;
void handler(int signo){
	printf("Ciao dall'handler\n");
	nsig = signo;
}
int main(){
	signal(SIGUSR1,handler);
	int pid = 0;
	int wstatus;
	pid_t pidFiglio,w;
	pid = fork();
	pidFiglio = getpid();
	if(pid == pidFiglio){
		sleep(10);
		if(nsig == SIGUSR1){
			printf("ricevuto segnale\n");
			exit(0);
		}
	}else{
		kill(pid,SIGUSR1);
		w = waitpid(pidFiglio,&wstatus,WUNTRACED|WCONTINUED);
	}
}
