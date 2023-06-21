/*
Scrivere un programma Linux C che stampi a video il contenuto di un file a byte alterni, ovvero un carattere sì e uno no.
Il nome del file viene passato da riga di comando.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
	int fd;
	char *str = "FORZA NAPOLI";
	char *buff;
	if(argc != 2){
		fprintf(stderr,"Uso: ./a.out <nome file>\n");
		exit(-1);
	}
	if(fd = (open(argv[1],O_CREAT,S_IRUSR|S_IWUSR)) < 1){
		perror("open");
		exit(-2);
	}
	//write(fd,str,sizeof(str));
	while(read(fd,buff,sizeof(char*))){
		lseek(fd,SEEK_CUR,1*sizeof(char));
		write(1,buff,sizeof(char));
	}
	close(fd);
	return 0;
}
