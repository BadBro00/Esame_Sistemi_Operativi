/*
ES 3)
Scrivere un programma C che crei m thread (m parametro da riga di comando), che vadano a svolgere il prodotto delle matrici A(K*m) e B(m*P).
K e P sono costanti definite nel codice sorgente. Al termine dei calcoli, un thread (m+1)-simo, che era in attesa, procederà a stampare la matrice risultato.
-------------------------------------
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int K = 4;
const int P = 5;

struct shared{
	pthread_cond_t myCond;
	int m,idx;
	int **m1,**m2,**prd_mat;
	pthread_mutex_t mutex;
	pthread_t *tids;
}shared;

//Routine
void* do_ops(void* args){
	struct shared sh = *(struct shared *)args;
	for(int i=0;i<K;i++){ //Ciclo sulle righe
			for(int j=0;j<P;j++){ //Ciclo sulle colonne
				sh.prd_mat[i][j] += sh.m1[i][sh.idx]*sh.m2[sh.idx][j]; 
				//Stabilisco il prodotto in base a i e j e uso l'indice del thread al posto del 3o for
			}
	}
	//Se sono l'ultimo thread,effettuo una signal sulla condition per risvegliare il thread m+1-simo
	if(sh.idx == shared.m-1){
		pthread_cond_signal(&sh.myCond);
	}
	pthread_exit(NULL);
}
//Routine per il thread m+1-simo
void* last(void* args){ 
	struct shared sh = *(struct shared *)args;
	//Effettuo la wait sulla condition variable e mi blocco nel caso gli altri non abbiano terminato
	pthread_cond_wait(&shared.myCond,&shared.mutex);
	//Printo la matrice
	for(int i=0;i<K;i++){
		for(int j=0;j<P;j++){
			printf(" %d ",shared.prd_mat[i][j]);
		}
		printf("\n");
	}
	pthread_exit(NULL);
}

void mats_init(){
	//Allocazione ed inizializzazione delle matrici (K*m),(m*P) e (K*P)
	//m1(K*m)
	shared.m1 = malloc(K*sizeof(int*));
	for(int i=0;i<K;i++){
		shared.m1[i] = malloc(shared.m*sizeof(int));
	}
	//m2(m*P)
	shared.m2 = malloc(shared.m*sizeof(int*));
	for(int i=0;i<shared.m;i++){
		shared.m2[i] = malloc(P*sizeof(int));
	}
	//Inizializzo m1
	for(int i=0;i<K;i++){
		for(int j=0;j<shared.m;j++){
			shared.m1[i][j] = rand()%256;
		}
	}
	//Inizializzo m2
	for(int i=0;i<shared.m;i++){
		for(int j=0;j<P;j++){
			shared.m2[i][j] = rand()%256;
		}
	}
	//Matrice prodotto (K*P)
	shared.prd_mat = malloc(K*sizeof(int*));
	for(int i=0;i<K;i++){
		shared.prd_mat[i] = malloc(P*sizeof(int));
	}
	//Inizializzo la matrice prodotto
	for(int i=0;i<K;i++){
		for(int j=0;j<P;j++){
			shared.prd_mat[i][j] = 0;
		}
	}
}
//Function di stampa delle due matrici
void prt_mats(){
	printf("----------------M1-------------\n");
	for(int i=0;i<K;i++){
		for(int j=0;j<shared.m;j++){
			printf(" %d ",shared.m1[i][j]);
		}
		printf("\n");
	}
	printf("---------------M2-------------\n");
	for(int i=0;i<shared.m;i++){
		for(int j=0;j<P;j++){
			printf(" %d ",shared.m2[i][j]);
		}
		printf("\n");
	}
}
//Function di stampa della matrice prodotto
void prt_prod(){
	printf("----------------MAT-PROD------------\n");
	for(int i=0;i<K;i++){
		for(int j=0;j<P;j++){
			printf(" %d ",shared.prd_mat[i][j]);
		}
		printf("\n");
	}
}

int main(int argc,char *argv[]){
	srand(time(NULL)); //Inizializzo il seed di srand
	//Error handling degli argomenti
	if(argc != 2){
		fprintf(stderr,"Uso: ./a.out <int>\n");
		exit(-1);
	}
	struct shared sh;
	sh.m = shared.m = atoi(argv[1]);
	//Se il parametro passato è troppo piccolo, esco
	if(sh.m < 2){
		fprintf(stderr,"Il parametro dev'essere >= 2!\n");
		exit(-2);
	}
	//Alloco dinamicamente l'array tids
	sh.tids = malloc(sh.m*sizeof(pthread_t));
	
	mats_init();
	prt_mats();
	//Creo i vari thread tramite for
	for(int i=0;i<sh.m;i++){
		int *idx = malloc(sizeof(int));
		*idx = i;
		pthread_create(&sh.tids[i],NULL,(void *)&do_ops,idx);
		
	}
	//Joino gli m thread
	for(int i=0;i<sh.m;i++){
		pthread_join(sh.tids[i],NULL);
	}
	//Creazione dell'ultimo thread, che rimarrà in attesa
	pthread_t lasTid;
	pthread_create(&lasTid,NULL,&last,&sh);
	//Dealloco la memoria ed esco
	free(sh.m1);
	free(sh.m2);
	free(sh.prd_mat);
	exit(0);
}
