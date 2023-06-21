/*
Scrivere un programma Linux C che crei due thread che eseguono la function "incrementa", che a sua volta accede alle variabili globali glob.a e glob.b
	di una struttura dati condivisa glob, e ne incrementi il valore di 1 per 100 volte.
Al termine, quando i due thread avranno terminato con gli incrementi, il thread principale stamperà a video i valori di glob.a e glob.b.
Per la gestione della sincronizzazione, si usino i mutex allocati dinamicamente
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct glob{
	int a;
	int b;
	pthread_mutex_t mutex;
}glob;

void* incrementa(){
	pthread_mutex_lock(&glob.mutex);
	for(int i=0;i<100;i++){
		glob.a++;
		glob.b++;
	}
	pthread_mutex_unlock(&glob.mutex);
	pthread_exit(NULL);
}

int main(int argc,char *argv[]){
	pthread_t tids[2];
	if(argc != 1){
		fprintf(stderr,"Uso: ./a.out\n");
		exit(-1);
	}
	pthread_mutex_init(&glob.mutex,NULL);
	for(int i=0;i<2;i++)
		pthread_create(&tids[i],NULL,incrementa,NULL);
	for(int i=0;i<2;i++)
		pthread_join(tids[i],NULL);
	printf("Thread principale (main)\n\tI valori di glob.a e glob.b sono\n\t\tglob.a %d\tglob.b %d\n",glob.a,glob.b);
}
