/*
Si realizzi  un programma C sotto Linux che, con l'ausilio della libreria pthread, lanci m thread per calcolare il prodotto di due matrici (k*m) e (m*p).
Non appena sarà calcolata la matrice prodotto, un (m+1)-simo thread aggiuntivo, che era in attesa, provvederà a stampare la matrice risultato. 
Le matrici devono essere allocate dinamicamente, e usare le variabili di condizione.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//DICHIARAZIONE COSTANTI
#define k 2
#define p 3
//STRUTTURA CONTENENTE DATI CONDIVISI
struct shared{
	int m;
	int **mat1,**mat2;
	int **matProd;
	int ridx,cidx;
	pthread_cond_t condvar;
	pthread_mutex_t mutex;
}shared;
//ROUTINE DEGLI M THREAD
void* routine(void* args){
	int idx = *(int*)args;
	pthread_mutex_lock(&shared.mutex);
	printf("Row idx: %d, Column idx: %d\n",shared.ridx,shared.cidx);
	shared.matProd[shared.ridx][shared.cidx] += shared.mat1[shared.ridx][idx]*shared.mat2[idx][shared.cidx];
	//TODO AGGIUSTARE L'AUMENTO DELLE RIGHE DOPO TUTTI I PRODOTTI DEI THREAD
	if(shared.ridx < k && shared.cidx < p){
		shared.ridx++;
		shared.cidx++;
	}
	if(idx == (shared.m-1)){
		pthread_cond_signal(&shared.condvar);
	}
	pthread_mutex_unlock(&shared.mutex);
	pthread_exit(NULL);
}
//ROUTINE DELL'ULTIMO THREAD
void* lastOp(void* args){
	printf("Ultimo thread [%ld], attendo\n",pthread_self());
	pthread_cond_wait(&shared.condvar,&shared.mutex);
	for(int i=0;i<k;i++){
		for(int j=0;j<p;j++){
			printf(" %d ", shared.matProd[i][j]);
		}
		printf("\n");
	}
	pthread_exit(NULL);
}

void mat_init(){
	//ALLOCAZIONE MATRICI CONDIVISE
	shared.mat1 = malloc(k*sizeof(int*));
	for(int i=0;i<k;i++){
		shared.mat1[i] = malloc(shared.m*sizeof(int));
	}
	shared.mat2 = malloc(shared.m*sizeof(int*));
	for(int i=0;i<shared.m;i++){
		shared.mat2[i] = malloc(p*sizeof(int));
	}
	//INIZIALIZZAZIONE
	for(int i=0;i<k;i++){
		for(int j=0;j<shared.m;j++){
			shared.mat1[i][j] = rand()%256;
		}
	}
	for(int i=0;i<shared.m;i++){
		for(int j=0;j<p;j++){
			shared.mat2[i][j] = rand()%256;
		}
	}
	//ALLOCAZIONE E INIZIALIZZAZIONE MATRICE PRODOTTO
	shared.matProd = malloc(k*sizeof(int*));
	for(int i=0;i<k;i++)
		shared.matProd[i] = malloc(p*sizeof(int));
	for(int i=0;i<k;i++)
		for(int j=0;j<p;j++)
			shared.matProd[i][j] = 0;

}
//STAMPA DELLE MATRICI
void prt_mats(){
	printf("-----------MAT 1------------\n");
	for(int i=0;i<k;i++){
		for(int j=0;j<shared.m;j++){
			printf(" %d ", shared.mat1[i][j]);
		}
		printf("\n");
	}
	printf("-----------MAT 2------------\n");
	for(int i=0;i<shared.m;i++){
		for(int j=0;j<p;j++){
			printf(" %d ", shared.mat2[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[]){
	pthread_cond_init(&shared.condvar,NULL);
	srand(time(NULL));
	if(argc != 2){
		fprintf(stderr,"Uso: ./a.out <int>\n");
		exit(-1);
	}
	shared.m = atoi(argv[1]);
	if(shared.m < 2){
		fprintf(stderr,"Uso int >= 2\n");
		exit(-2);
	}
	mat_init();
	prt_mats();
	pthread_t tids[shared.m];
	pthread_t last;
	for(int i=0;i<shared.m;i++){
		pthread_create(&tids[i],NULL,routine,(void*)&i);
	}
	printf("crete last\n");
	pthread_create(&last,NULL,lastOp,NULL);
	for(int i=0;i<shared.m;i++){
		pthread_join(tids[i],NULL);
	}
	printf("join last\n");
	pthread_join(last,NULL);
	return 0;
}
