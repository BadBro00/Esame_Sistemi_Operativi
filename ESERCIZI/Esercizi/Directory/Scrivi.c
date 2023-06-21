/*Scrivere un programma che scriva la stringa "ABCDEFGHILMNOPQRSTUVZ" su un file 'output.txt'*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
	int fd;
	char buf[21] = "ABCDEFGHILMNOPQRSTUVZ";
	fd = open("output.txt",O_CREAT|O_RDWR,S_IRUSR|S_IWUSR);
	if(fd == -1){
		perror("open");
		exit(-1);
	}
	int bytes_written;
	if((bytes_written = write(fd,buf,sizeof(buf))) != 21){
		perror("write");
		exit(-2);
	}
	
	close(fd);
	
	exit(0);
}
