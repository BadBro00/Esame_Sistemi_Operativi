/*Scrivere un programma POSIX che legge un file input passato come argomento e stampi il suo contenuto in ordine inverso*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr,"Uso: ./a.out <nomefile.txt>\n");
		exit(-1);
	}
	char* nomefile = argv[1];
	int fd;
	if((fd = open(nomefile,0,S_IRUSR)) == -1){
		perror("open");
		exit(-2);
	}
	char buff[10];
	lseek(fd,-1*sizeof(char),SEEK_END);
	while(read(fd,buff,sizeof(buff))){
		write(1,buff,sizeof(buff));
		lseek(fd,-2*sizeof(char),SEEK_CUR);
	}
	exit(0);
}
