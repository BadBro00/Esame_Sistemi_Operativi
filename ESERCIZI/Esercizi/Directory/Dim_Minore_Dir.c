/*Scrivere un programma POSIX C che presa una directory da riga di comando ne stampi i dettagli (nome,data ultimo accesso,permessi) relativi al file con dimensione minore in tutti quelli nella directory*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

int n;

int get_min_idx(int arr[],int dim){
  int m = arr[0];
  int m_idx;
  for(int i=0;i<dim;i++) 
    if(arr[i] < m){
      m = arr[i];
      m_idx = i;
    }
  return m_idx;
}

int main(int argc, char *argv[]){
    //Check argomenti
    if(argc != 2){
      fprintf(stderr,"Uso: ./a.out <directory>\n");
      exit(-1);
    }
    //Definizione variabili
    struct dirent *dir;
    struct stat fs;
    DIR *dp;
    //Check functions
    if(dp = opendir(argv[1]) < 0){ 
      fprintf(stderr,"Error with opendir()\n");
      exit(-2);
    }
    while(dir = readdir(dp)){
      n++;
    }
    closedir(dir);
    int dim_array[n];
    char *pathnames;
    pathnames = malloc(n*sizeof(char*));
    dp = opendir(argv[1]);
    int r,i=0;
    while( (dir = readdir(dp)) != NULL){
        if (r = stat(dir_d->name,&fs) < 0){
          fprintf(stderr,"Error with stat()\n");
          exit(-1);
        }
      dim_array[i++] = fs.st_size;
      pathnames[i++] = dir_d->name;
  }
  closedir(dir);
  int min_idx = get_min_idx(dim_array,n);
  stat(pathnames[min_idx],&fs);
  printf("Nome : %s\nData Ultimo Accesso : %s\nPermessi %X\n",pathnames[min_idx],(ctime)&fs.st_atime,fs.st_mode);
}
