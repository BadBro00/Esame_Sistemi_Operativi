/*
Scrivere un programma in C e Posix che prende da riga di comando N interi tra 5 e 20. Il valore di N è costante ed indicato nel sorgente.
Il programma avvia N thread che hanno il seguente comportamento:
	1-Ogni thread va in sospensione (invocando la funzione sleep() ) per un numero di secondi pari al valore del corrispondente parametro e poi stampa il suo indice.
	2-Alla fine del perioso di attesa, ogni thread stampa il messaggio: "Thread #: sveglio!"
	3-Tutti i thread si sincronizzano fra loro (utilizzando semafori basati su memoria)
	4-Dopo aver atteso il termine di tutti i thread, ciascuno stampa a video il messaggio "Thread #: terminato.."
-------------------------------------------
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const int N=5;
sem_t *sem;
int *numbers;

void* do_ops(void* args){
	int idx = *(int *)args;
	printf("Thread #%lu (IDX: %d) avviato\n",pthread_self(),idx);
	sleep(idx);
	sem_wait(sem);
	printf("Thread #%lu (IDX: %d) sveglio\n", pthread_self(),idx);
	sem_post(sem);
	sem_wait(sem);
	printf("Thread #%lu (IDX: %d) termina..\n",pthread_self(),idx);
	sem_post(sem);
}
int main(int argc,char *argv[]){
	numbers = malloc(N*sizeof(int));
	sem = sem_open("tmp",O_CREAT|O_EXCL,S_IRUSR|S_IWUSR,1);
	if(argc != N+1){
		fprintf(stderr,"Uso: ./a.out %d <int>\n",N);
		exit(-1);
	}
	for(int i=0;i<N;i++){
		numbers[i] = atoi(argv[i+1]);
		if(numbers[i] < 5 || numbers[i] > 20){
			fprintf(stderr,"Numero %d non valido\n",i);
			exit(-2);
		}
	}
	for(int i=0;i<N;i++){
		printf("IDX: %d\n",numbers[i]);
	}
	pthread_t tids[N];
	for(int i=0;i<N;i++){
		pthread_create(&tids[i],NULL,&do_ops,&numbers[i]);
	}
	for(int i=0;i<N;i++){
		pthread_join(tids[i],NULL);
	}
	sem_close(sem);	
	return 0;
}
