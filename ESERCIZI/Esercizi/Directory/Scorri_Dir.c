/*
Scrivere un programma in POSIX C che provveda a scorrere la directory passata come argomento e stampi la dimensione dei file in tale directory che hanno permessi di lettura e scrittura per l'utente (USR) e gli altri (OTH)
*/

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
  DIR *dp;
  struct dirent *dir;
  struct stat fs;
  dp = opendir(argv[1]);
  while((dir = readdir(dp)) != NULL){
    int r = stat(dir->d_name,&fs);
    if(S_ISREG(fs.st_mode)){
    	//if(fs.st_mode == S_IRUSR || S_IWUSR || S_IROTH || S_IWOTH){
    	if (S_ISREG(fs.st_mode) &&
            (fs.st_mode & S_IRUSR) && (fs.st_mode & S_IWUSR) &&
            (fs.st_mode & S_IROTH) && (fs.st_mode & S_IWOTH)) {
            printf("%s (%ld bytes)\n", dir->d_name, fs.st_size);
        }
    }
  }
}
