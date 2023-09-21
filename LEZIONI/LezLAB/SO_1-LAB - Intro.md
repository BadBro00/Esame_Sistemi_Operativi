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
	Un programma è un qualunque file eseguibile, posto all'interno del File System UNIX. Un processo è *un programma in esecuzione, che usa le risorse ad esso allocate. Ciascun processo è identificato da un intero univoco nel sistema, *quando il processo è in esecuzione*. Se il processo termina, o la sua esecuzione si interrompe, il suo identificativo (**PID**) può essere assegnato ad un altro processo.
`
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(void)
{
	printf("hello world from process ID %d\n", getpid());
	exit(0);
}
`
L'esecuzione di questo codice fornirà un output del tipo:
`
$ ./a.out
hello world from process ID 851
`
Se ri-eseguissimo questo codice ad un diverso istante, avremmo:
`
$ ./a.out
Hello world from process ID 854
`
Questo perchè appunto il process ID del programma è stato assegnato ad un altro processo.

*Controllo Processi*
	Esistono tre function principali per il controllo dei processi, e sono:
 `fork`
 `getpid`
 `wait`
In ordine:
	1) fork() : Crea un processo figlio, copiando lo spazio d'indirizzamento del padre
 	2) getpid() : Ottiene il PID del processo che la invoca
  	3) wait() : Attende una condizione su un certo processo, o gruppo di processi
Il seguente codice legge i comandi passati dallo **standard input** (*la tastiera*), e li *esegue*
` 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 255
int main(void){
	char buf[MAXLINE];
	pid_t pid;
	int status;
	printf("%% "); /* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		buf[strlen(buf) - 1] = 0; /* replace newline with null */
		if ((pid = fork()) < 0)
			printf("fork error");
		else if (pid == 0) { /* child */
			execlp(buf, buf, (char *) 0);
			printf("couldn't execute: %s", buf);
			exit(127);
		}
		if ((pid = waitpid(pid, &status, 0)) < 0) {
			printf("waitpid error");
			printf("%% ");
		}
	} 
	exit(0);
}
`
Facendo un esempio di esecuzione, avremmo un output del tipo:
`
$ ./a.out
% date
Sun Mar 1 03:04:47 EDT 2009
% pwd
/home/eugenio/prova
% ls
Makefile
a.out
Prova.c
% ^D
$
`
Notiamo che il simbolo *%* è semplicemente il simbolo per dar input alla shell durante l'esecuzione del codice sopra citato.

------------

**SEGNALI**
 	Un segnale è un metodo per inviare messaggi ad un processo, o notificargli una situazione eccezionale. Alcuni segnali possono essere inviati anche dalla tastiera, tramite input di alcuni comandi speciali, come *Ctrl+C* (**SIGINT**) o *Ctrl+Z* (**TSTP**).
  Alla ricezione di un segnale, il processo può eseguire diverse azioni:
	1) Effettuare l'azione di default
 	2) Eseguire un'azione diversa
  	3) Ignorare il segnale
   Di solito, la 1° richiede la terminazione dell'esecuzione, ma può essere utile non fermare l'esecuzione del processo. Perciò, viene solitamente implementato un *handler*, che gestisce l'azione da far svolgere al processo. Se invece un processo volesse ignorare il segnale, può farlo, ma il segnale non andrebbe perso, venendo salvato (come codice) nel campo IC del PSW.
