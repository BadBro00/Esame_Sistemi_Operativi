/*
Un processo padre crea M (con M pari) processi figli. Ciascun figlio Fi è identificato da una variabile intera i(0,1,2,3,...). Si gestiscano i casi:
	1- Se il primo argomento dato in input al programma è uguale al carattere 'p' (che sta per pari), ogni processo figlio Fi con i pari manda un segnale
	(SIGUSR1) al processi (i+1)-simo.
	
	2- Se il primo argomento dato in input è uguale al carattere 'm' (che sta per metà), ogni processo figlio Fi con i < M/2 manda un segnale
	(SIGUSR1)  all'altra metà dei processi, ovvero al processo (i+m/2)-simo.
	
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int nsig;
void handler(int signo){
	nsig = signo;
	printf("Sono il processo: %d\nRicevuto segnale : %d\n\n",getpid(),signo);
}
int main (int argc,char *argv[]){
	signal(SIGUSR1,handler);
	if(argc != 3){
		fprintf(stderr,"Uso: ./a.out <int> <m/p>\n");
		exit(-1);
	}
	char scelta = argv[2][0];
	int M = atoi(argv[1]);
	int vars[M];
	pid_t pidsProc[M];
	pid_t pids[M];
	pidsProc[0] = getpid();
	for(int i=0;i<M;i++){
		if(fork() == 0){
			pidsProc[i] = getpid();
		}else{
			printf("Creato processo: %d\n",getpid());
		}
		vars[i] = i;
		sleep(3);
		pids[i] = 0;
	}
	/*
	int k=0;
	while(k<M){
		if(pids[k] == 0){
			printf("Processo: %d\nMio indice: %d\n",pidsProc[k],vars[k]);
		}
		k++;
	}
	*/
	printf("\n\n\n");
	if(scelta == 109 || scelta == 77){
		//printf("\tScelto META'\n");
		for(int i=0;i<M;i=i+2){
			printf("Sono il processo: %d\nInvio segnale: %d al processo con i: %d\n",getpid(),SIGUSR1,i+1);
			kill(pidsProc[i+1],SIGUSR1);
		}
	}else if(scelta == 80 || scelta == 112){
		for(int i=0;i<M/2;i++){
			if(pids[i] != 0)
				printf("Hai scelto \tPARI\n");
			else{
				printf("Sono il processo: %d\nInvio segnale: %d al processo con i: %d\n",pidsProc[i],SIGUSR1,i+M/2);
				kill(pidsProc[i+M/2],SIGUSR1);
			}
		}
	}
}
