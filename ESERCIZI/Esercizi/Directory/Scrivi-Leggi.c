/*
Scrivere un programma C “scrivi.c” che
utilizzando la funzione primitiva “write”, scriva
in un file “alfabeto.txt” la seguente stringa di
caratteri:
“ABCDEFGHILMNOPQRSTUVZ”*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[]){
	char *buff = "ABCDEFGHILMNOPQRSTUVZ";
	int fd;
	if((fd = open("alfabeto.txt",O_CREAT|O_EXCL,S_IWUSR|S_IRUSR|S_IXUSR)) < 3){
		perror("open");
		exit(-1);
	}else{
		printf("File Aperto, con fd = %d\n",fd);
	}
//	printf("Scrivo\n");
	lseek(fd,SEEK_SET,0);
	write(fd,buff,sizeof(buff));
	close(fd);
	exit(0);
}
