/*
Data una matrice n*n (n pari) di interi, generata casualmente ed allocata dinamicamente, con n argomento da riga di comando:
creare n thread che prelevano casualmente un elemento dalla riga di competenza (thread i-simo->riga i-sima),
	e lo inseriscano concorrentemente in un vetore di (n+1)/2 elementi.
Un (n+1)-simo thread attende il riempimento del vettore per stampare il contenuto dello stesso, e per stampare il numero di elementi inserito da ciascun thread.
Usare mutex e variabili di condizione
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

struct shared{
	int n;
	int **mat;
	int *buff;
	int *counter;
	pthread_cond_t condVar;
	pthread_mutex_t mutex;
}shared;

void* routine(void* args){
	int i = *(int*)args;
	printf("Thread %ld, il mio idx è %d\n",pthread_self(),i);
	int rand_el = rand()%shared.n;
	int elem = shared.mat[i][rand_el];
	shared.buff[i] = elem;
	shared.counter[i]++;
	pthread_cond_wait(&shared.condVar,&shared.mutex);
	pthread_exit(NULL);
}

void* last(void* args){
	pthread_cond_broadcast(&shared.condVar);
	for(int i=0;i<shared.n;i++){
		printf("Thread %d ha inserito %d elementi\n",i,shared.counter[i]);
		printf("%d ",shared.buff[i]);
	}
	pthread_cond_destroy(&shared.condVar);
	pthread_exit(NULL);
}

void mat_init(){
	shared.mat = malloc(shared.n*sizeof(int*));
	for(int i=0;i<shared.n;i++)
		shared.mat[i] = malloc(shared.n*sizeof(int));
	for(int i=0;i<shared.n;i++)
		for(int j=0;j<shared.n;j++)
			shared.mat[i][j] = rand()%256;
}

void prt_mat(){
	for(int i=0;i<shared.n;i++){
		for(int j=0;j<shared.n;j++){
			printf(" %d ",shared.mat[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]){
	srand(time(NULL));
	if(argc != 2){
		fprintf(stderr,"Uso: ./a.out <int>\n");
		exit(-1);
	}
	shared.n = atoi(argv[1]);
	pthread_t tids[shared.n];
	pthread_t lastTid;
	shared.buff = malloc(shared.n*sizeof(int));
	shared.counter = malloc(shared.n*sizeof(int));
	if(shared.n <= 1){
		fprintf(stderr,"Uso <int> maggiore di 1\n");
		exit(-2);
	}
	printf("n vale : %d\n",shared.n);
	mat_init();
	prt_mat();
	int ret = pthread_cond_init(&shared.condVar,NULL);
	for(int i=0;i<shared.n;i++){
		pthread_create(&tids[i],NULL,routine,(void*)&i);
	}
	for(int j=0;j<shared.n;j++)
		pthread_join(tids[j],NULL);
	pthread_create(&lastTid,NULL,last,NULL);
	pthread_join(lastTid,NULL);
}
