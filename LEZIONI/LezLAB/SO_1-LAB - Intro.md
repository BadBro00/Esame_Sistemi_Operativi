----------------------------------------------------------------------------------------
**SISTEMI OPERATIVI**
---
*File System*
	Il filesystem di Unix è un insieme di file e directory organizzato in maniera gerarchica; la radice (****root****) del filesystem è una directory rappresentata dal simbolo `/`. Una directory è una tabella che contiene un nome e un puntatore ad una struttura di informazioni per ciascun file o directory in essa contenuto; gli attributi contenuti in tale struttura riguardano il tipo di file, la dimensione, il proprietario, i permessi, ecc…
`
#include <sys/types.h>
#include <dirent.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[ ])
{
	DIR * dp;
	struct dirent * dirp;
	if (argc != 2)
		printf("a single argument (the dir name) is required");
	if ( (dp = opendir(argv[1])) == NULL)
		printf("can't open %s", argv[1]);
	while ( (dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);
	closedir(dp);
	exit(0);
}
`
Eseguendo questo codice, si otterrà una stampa, se possibile, dei file nella directory specificata come parametro:
`
$ ./a.out /dev
.
..
console
tty
mem
kmem
null
mouse
ecc...
`

--------------------------
*I/O*
	*File I/O*
 		Quando un programma apre o crea un file, il kernel ritorna un intero, che funge da *descrittore di file*, che verrà usato per accedere al file. Vi sono tre file descriptor standard, assegnati al boot:
   0 per lo **standard input**
   1 per lo **standard output**
   2 per lo **standard error**
   E' possibile poi *redirigere* l'input o l'output di un file o di un comando, tramite `<` o `>`:
`
ls > output.txt    //l'output di ls verrà scritto sul file output.txt
`
`file.txt < wc     //il comando wc prenderà come input il contenuto di file.txt
`

---------
**I/O Non Bufferizzato**
	Le principali funzioni di I/O, della libreria *stdio*, forniscono un'interfaccia bufferizzata ai metodi di I/O di UNIX. Le funzioni *printf*,*scanf*,ecc...
 	Le systemcall di UNIX per l'I/O non sono bufferizzate, e quindi bisognerà specificare la dimensione dei dati da scambiare. Le funzioni *read*,*write*,ecc infatti richiedono di indicare il numero di *bytes* su cui operare.

---------
**Programmi/Processi**
	Un programma è un qualunque file eseguibile, posto all'interno del File System UNIX. Un processo è *un programma in esecuzione, che usa le risorse ad esso allocate.
