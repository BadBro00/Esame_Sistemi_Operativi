/*
ES 4

Scrivere un programma che, presi due parametri da riga di comando (il primo sarà il percorso di una directory, il secondo un intero che
rappresenta i permessi nel formato ottale), faccia il parsing della directory e stampi i nomi, i permessi e le date di ultima modifica dei file
contenuti in tale directory, per cui i permessi corrispondano a quelli passati come parametro.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc,char *argv[]){
	if(argc != 3){
		fprintf(stderr,"Uso: ./a.out <dir> <permessi>\n");
		exit(-1);
	}
	int perm = atoi(argv[2]);
	char *path = argv[1];
	execl("cd", path, NULL);
	DIR *dp;
	struct dirent *dir;
	struct stat fs;
	dp = opendir(path);
	while(dir = readdir(dp)){
		int r = stat(dir->d_name,&fs);
		if(r < 0){
			perror("stat");
			exit(-2);
		}
		if((fs.st_mode & perm) && (S_ISREG(fs.st_mode)|S_ISDIR(fs.st_mode))){
			printf("Nome :%s\nPermessi: %X\nD.U.M.: %s\n",dir->d_name,fs.st_mode,ctime(&fs.st_mtime));
			printf("\n|Permessi (rwx): ");
			printf((fs.st_mode & S_IRUSR) ? "r" : "-");
			printf((fs.st_mode & S_IWUSR) ? "w" : "-");
			printf((fs.st_mode & S_IXUSR) ? "x" : "-");
			printf((fs.st_mode & S_IRGRP) ? "r" : "-");
			printf((fs.st_mode & S_IWGRP) ? "w" : "-");
			printf((fs.st_mode & S_IXGRP) ? "x" : "-");
			printf((fs.st_mode & S_IROTH) ? "r" : "-");
			printf((fs.st_mode & S_IWOTH) ? "w" : "-");
			printf((fs.st_mode & S_IXOTH) ? "x" : "-");
			printf("|\n");
		}
	}
	printf("\n\n|Termino...|\n");
	exit(0);
}
