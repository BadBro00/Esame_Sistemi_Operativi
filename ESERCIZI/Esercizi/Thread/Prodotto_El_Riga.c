/*
	Scrivere un codice in POSIX C che effettua il prodotto degli elementi di ogni riga fra due matrici A e B.
	Ogni thread fa il prodotto degli elementi della sua riga di competenza.
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

struct shared{
	sem_t *CritSec;
	int *buff;
	int m,i;
	int totsum;
	pthread_cond_t condVar;
	pthread_mutex_t mutex;
}shared;
int **matA,**matB;

void* do_last(void* args){
	struct shared s = *(struct shared *)args;
	pthread_cond_wait(&shared.condVar,&shared.mutex);
	for(int i=0;i<shared.m;i++){
		printf("buff[%d] = %d\n",i,shared.buff[i]);
		shared.totsum += shared.buff[i];
	}
	pthread_exit(NULL);
}
void* do_ops(void* args){
	struct shared s = *(struct shared *)args;
	int idx = s.i;
	int buf_idx;
	for(int j=0;j<shared.m;j++){
		sem_wait(shared.CritSec);
		shared.buff[buf_idx++] += matA[idx][j] * matB[idx][j];
		sem_post(shared.CritSec);
	}
	if(idx == shared.m-1){
		pthread_cond_signal(&shared.condVar);
	}
	pthread_exit(NULL);
}
void matA_init(){
	matA = malloc(shared.m*sizeof(int*));
	for(int i=0;i<shared.m;i++){
		matA[i] = malloc(shared.m*sizeof(int));
	}
	for(int i=0;i<shared.m;i++){
		for(int j=0;j<shared.m;j++){
			matA[i][j] = rand()%256;
		}
	}
}
void matB_init(){
	matB = malloc(shared.m*sizeof(int*));
	for(int i=0;i<shared.m;i++){
		matB[i] = malloc(shared.m*sizeof(int));
	}
	for(int i=0;i<shared.m;i++){
		for(int j=0;j<shared.m;j++){
			matB[i][j] = rand()%256;
		}
	}
}
void prt_mats(){
printf("-----------------MAT-A-----------\n");
	for(int i=0;i<shared.m;i++){
		for(int j=0;j<shared.m;j++){
			printf(" %d ", matA[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
printf("-----------------MAT-B-----------\n");
	for(int i=0;i<shared.m;i++){
		for(int j=0;j<shared.m;j++){
			printf(" %d ", matB[i][j]);
		}
		printf("\n");
	}
}
void prt_buff(){
	for(int i=0;i<shared.m;i++){
		printf("buff[%d] = %d\n",i,shared.buff[i]);
	}
}
int main(int argc,char *argv[]){
	shared.CritSec = sem_open("semCS",O_CREAT,S_IRUSR | S_IWUSR,1);
	if(argc < 2){
		fprintf(stderr,"Uso: ./a.out <dim>\n");
		exit(-1);
	}
	shared.m = atoi(argv[1]);
	shared.buff = malloc(shared.m*sizeof(int));
	if(shared.m<1){
		fprintf(stderr,"Uso <dim> >= 2!\n");
		exit(-2);
	}
	matA_init();
	matB_init();
	prt_mats();printf("\n");
	pthread_t tids[shared.m];
	for(int i=0;i<shared.m;i++){
		shared.i = i;
		printf("TID: %lu\nIDX: %d\n",pthread_self(),shared.i);
		pthread_create(&tids[i],NULL,&do_ops,&shared);
	}
	pthread_t tidLast;
	for(int i=0;i<shared.m;i++){
		pthread_join(tids[i],NULL);
	}
	if(w8 = 1){
		pthread_create(&tidLast,NULL,&do_last,&shared);
	}
	pthread_join(tidLast,NULL);
	printf("\n\ttotsum = %d\n",shared.totsum);
	exit(0);
}
