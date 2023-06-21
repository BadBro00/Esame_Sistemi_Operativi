/*
Scrivere un programma Linux C che, preso in input un file completo di path, restituisca lo UID del proprietario, la grandezza del file e tutti i permessi associati.
*/

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr,"Uso: ./a.out <nomefile>\n");
		exit(-1);
	}
	struct stat fs;
	int r = stat(argv[1],&fs);
	printf("UID:%d\nDIM:%ld\nPermessi:\n",(int)fs.st_uid,fs.st_size);
	printf( (fs.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fs.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fs.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fs.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fs.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fs.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fs.st_mode & S_IROTH) ? "r" : "-");
    printf( (fs.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fs.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n");
	return 0;
}
