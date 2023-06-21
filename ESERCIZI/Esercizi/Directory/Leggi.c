/*Scrivere un programma che legga da un file output.txt e stampi a schermo il contenuto del file, che è la stringa "ABCDEFGHILMNOPQRSTUVZ"*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
	int fd;
	if((fd = open("output.txt",0,S_IRUSR|S_IWUSR|S_IXUSR)) < 3){
		perror("open");
		exit(-1);
	}
	int offset = 3;
	char buff[2];
	int nbytes = 0;
	while(nbytes = read(fd,buff,(offset)) != EOF){
		if(buff[0] == 'Z' || buff[1] == 'Z'){
			write(1,"Z",sizeof("Z"));
			exit(0);
		}
		write(1,buff,sizeof(buff));
		lseek(fd,offset*sizeof(char),SEEK_CUR);
		lseek(fd,-1*sizeof(char),SEEK_CUR);
	}
	printf("\n");
	exit(0);
}
