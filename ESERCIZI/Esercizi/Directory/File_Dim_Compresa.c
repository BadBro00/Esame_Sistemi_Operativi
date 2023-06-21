/*
Scrivere un programma in C che presi 3 parametri da riga di comando(il primo è una directory e i successivi sono due interi) elenchi tutti i file in tale directory
la cui grandezza è compresa (estremi inclusi) fra i due valori.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc,char *argv[]){
	char *nomedir;
	DIR *dp;
	struct dirent *dir;
	struct stat fs;
	if(argc != 4){
		fprintf(stderr,"Uso: ./a.out <directory> <int> <int>\n");
		exit(-1);
	}
	nomedir = argv[1];
	int minDim = atoi(argv[2]);
	int maxDim = atoi(argv[3]);
	printf("\t\t|RECAP:|\n\t\t|DIRECTORY : [%s]|\n\t|MIN DIM: [%d]|\tMAX DIM: [%d]|\n",nomedir,minDim,maxDim);
	dp = opendir(nomedir);
	if(!dp){
		perror("opendir");
	}
	while(dir = readdir(dp)){
		int r = stat(dir->d_name,&fs);
		if(fs.st_size >= minDim && fs.st_size <= maxDim){
			printf("|NOME: [%s]|\n|DIM: [%ld]|\n|PERM: [%X]|\n\n",dir->d_name,fs.st_size,fs.st_mode);
		}
	}
	exit(0);
}
