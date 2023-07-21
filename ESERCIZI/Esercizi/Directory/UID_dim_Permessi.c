/*
[INCOMPLETO -> CON ERRORI]
Scrivere un programma che, preso in input un file completo di percorso, restituisca lo UID del proprietario, la grandezza del file e tutti i permessi.
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc,char *argv[]){
	if(argc != 2){
		fprintf(stderr,"Uso: ./a.out <file>\n");
		exit(-1);
	}
	char *nome_file = argv[1];
	struct stat fs;
	int res = stat(nome_file,&fs);
	if(res < 0){
		perror("stat");
		exit(-2);
	}
	printf("\t\t[%s]\n\t|UID: %d|\n\t|Dimensione: %ld|\n\t|Permessi (hex): %X|\n",nome_file,fs.st_uid,fs.st_size,fs.st_mode);
	printf("\t|Permessi (rwx): ");
	printf((fs.st_mode & S_IRUSR) ? "r" : "-");
	printf((fs.st_mode & S_IWUSR) ? "w" : "-");
	printf((fs.st_mode & S_IXUSR) ? "x" : "-");
	printf("-");
	printf((fs.st_mode & S_IRGRP) ? "r" : "-");
	printf((fs.st_mode & S_IWGRP) ? "w" : "-");
	printf((fs.st_mode & S_IXGRP) ? "x" : "-");
	printf("-");
	printf((fs.st_mode & S_IROTH) ? "r" : "-");
	printf((fs.st_mode & S_IWOTH) ? "w" : "-");
	printf((fs.st_mode & S_IXOTH) ? "x" : "-");
	printf("|\n");
	exit(0);
}
