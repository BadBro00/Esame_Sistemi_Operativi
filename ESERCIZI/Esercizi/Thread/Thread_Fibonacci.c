/*
Facendo uso della libreria Pthread, realizzare un programma in cui unthread scrittore, dato un intero N da riga di comando (dove10<N<=15), 
scrive in un file nella prima posizione, uno alla volta edogni ½ secondo, la sequenza di Fibonacci di ordine N,
alternandosi conun thread lettore che legge, uno alla volta dalla prima posizione del file, i numeri scritti dal thread scrittore.
Un terzo thread attende lalettura dell’ N-esimo intero, quindi stampa a video il messaggio “Operazioni concluse, arrivederci dal thread: tid”,
attende 5 secondi etermina.
*/

#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>

struct shared{
	int N;
	int fd;
	int x,y;
	char* buff;
	sem_t scr,leg,sta;
}shared;

void* scrivi(void* args){
	while(shared.x <= shared.N){
		printf("Thread: %ld, scrittore\n",pthread_self());
		sem_wait(&shared.scr);
		shared.x += shared.y;
		write(shared.fd,&shared.x,sizeof(int));
		sem_post(&shared.leg);
	}
	pthread_exit(NULL);
}

void* leggi(void* args){
	while(shared.x <= shared.N){
		printf("Thread: %ld, lettore\n",pthread_self());
		sem_wait(&shared.leg);
		read(shared.fd,shared.buff,sizeof(shared.buff));
		sem_post(&shared.sta);
	}
	pthread_exit(NULL);
}

void* stampa(void* args){
	while(shared.x <= shared.N){
		printf("Thread: %ld, stampante\n",pthread_self());
		sem_wait(&shared.sta);
		int elem = atoi(shared.buff);
		write(1,&elem,sizeof(elem));
		sem_post(&shared.scr);
	}
	pthread_exit(NULL);
}


int main(int argc, char *argv[]){
	shared.x = 0;shared.y = 1;
	sem_init(&shared.scr,0,1);
	sem_init(&shared.leg,0,0);
	sem_init(&shared.sta,0,0);
	if (argc != 2){
		fprintf(stderr,"Uso: ./a.out <int>\n");
		exit(-1);
	}
	shared.N = atoi(argv[1]);
	if(shared.N < 10 || shared.N > 15){
		fprintf(stderr,"Uso: 10<int<=15\n");
		exit(-2);
	}
	if(shared.fd = open("file.txt",O_CREAT|O_EXCL,S_IRUSR|S_IWUSR|S_IXUSR) < 1){
		perror("open");
		exit(-3);
	}
	pthread_t lett,scritt,stamp;
	pthread_create(&scritt,NULL,scrivi,NULL);
	pthread_create(&lett,NULL,leggi,NULL);	
	pthread_create(&stamp,NULL,stampa,NULL);
	pthread_join(lett,NULL);
	pthread_join(scritt,NULL);
	pthread_join(stamp,NULL);
	close(shared.fd);
	return 0;
}
