----------------------------------------------------------------------------------------
**SISTEMI OPERATIVI**
---
*Sistema Operativo*
	I SO forniscono *servizi*, come eseguire un programma, allocare la memoria ecc.
	*UNIX*
		SO multiutente e multitasking, cioè più utenti possono avere più processi/task in esecuzione in contemporanea
		E' un ambiente di *sviluppo software*, cioè fornisce utilità di sistema, editor, compilatori, ecc.
		E' stato progettato per essere *indipendente dall'HW* e portatile, essendo scritto in C
		E' formato da un *kernel*, ovvero un insieme di operazioni essenziali di dimensione ridotta, che fornisce la base per tutte le operazioni che può eseguire. L'indipendenza dall'HW è assicurata scrivendo il codice in C invece che in un linguaggio assembly/macchina, e ciò lo rende *portabile*, dovendo semplicemente ricompilare il codice in un altro sistema HW.
	*Kernel*
		Il kernel è l'insieme di funzioni principali del SO, composto da *systemcall*, che sono semplicemente le funzioni principali tramite le quali funziona il sistema, e tramite le quali le funzioni *esterne* (librerie ecc) funzionano.
		Ad esempio, la funzione **printf()** usa la syscall **write()** per scrivere.
	*Shell*
		La shell è un'applicazione speciale, in grado di *eseguire comandi*, fornendo un'*interfaccia con il kernel*. Tramite la shell possiamo eseguire system call come **ls**,**write**, ecc.
	*Autenticazione*
		In Linux/UNIX, l'autenticazione avviene inserendo un nome utente ed una password. Questa combinazione viene cercata nel file $/etc/passwd$, dove il nome utente è in chiaro, e la pw è *cifrata*. Oltre a queste informazioni, vi sono anche lo **User ID**, ovvero un identificativo dell'utente, il **Group ID**, cioè un numero che identifica il *gruppo* al quale l'utente appartiene, la **Home**, cioè la directory assegnata all'utente dalla quale partono le directory dell'utente, e la **shell usata**, cioè la shell che viene assegnata all'utente.
	*File/Dir*
		Il FS di UNIX è formato da un insieme di file e directory, che è organizzato in maniera gerarchica. La *root* è una directory dalla quale partono tutte le altre (*solitamente /*).
		La *directory* è una tabella che contiene un nome ed un puntatore ad una struttura di informazioni, per ciascun file o directory in essa contenuto. Gli attributi di tale struttura riguardano la *dimensione*, il *tipo di file*, il *proprietario*, ecc.
		Tramite il comando $ls$, si possono visualizzare gli elementi (file/dir ecc) contenuti in una directory
	*I/O*
		Quando un programma apre o crea un file, viene creato un *descrittore di file* (fd) che è un intero non negativo, che identifica il programma aperto. Tutte le operazioni sul file verranno svolte tramite il fd, e dunque sempre sullo stesso file. All'avvio, la shell apre tre descrittori *standard*, ovvero **standard input (0)** cioè la tastiera, **standard output (1)** cioè lo schermo, e **standard error (2)**, sempre lo schermo. Questi rimarranno sempre i descrittori di default per queste tre componenti, a meno di una duplicazione dei descrittori (*dup()/dup2()*) e successiva chiusura (*close()*).
		Si possono *redirigire* gli output e gli input dei file verso altri file, mediante gli operatori *> <*.
		Con questo snippet vediamo come:
 ```Bash
$ ./a.out "ecco l'output"
"ecco l'output"
$ ./a.out > output.txt
$
$ cat output.txt
"ecco l'output"
$ echo "sono il nuovo input" > input.txt
$ ./a.out < input.txt > output.txt
$ cat output.txt
"sono il nuovo input"
```
-
	*Standard I/O*
		Le funzioni standard di Input/Output di UNIX forniscono un'interfaccia *bufferizzata* alle function di I/O non bufferizzato.
		Le function risiedono nella libreria *<stdio.h>*, e consentono di non doversi preoccupare della scelta ottimale della dimensione del buffer per le operazioni di I/O. Un ulteriore vantaggio è quello di rendere più semplice il trattamento delle *linee di input*:
			La function *fgets()* legge un'intera riga, mentre la function *read()* legge solo un certo numero di byte.
 ```C
 #include <stdio.h>
 int main(void) {
	 int c; 
	 while ((c = getc(stdin)) != EOF) 
		 if (putc(c,stdout) == EOF){ 
			 printf(“errore di output\n”);
			 exit(1);
		 }
	 if (ferror(stdin)){
		 printf(“errore di input\n”);
		 exit(1);
	 }
	 exit(0);
 }
```
 -
	 *Programmi e Processi*
		 Un programma è un file eseguibile che risiede nel file system. Un processo è *un programma in esecuzione, che usa le risorse ad esso allocate*. All'esecuzione, il programma viene caricato in memoria, ed eseguito dal kernel, quando riceve una chiamata ad una function della famiglia *exec()*. Ciascun processo è identificato da un **Process ID**, un intero non negativo univoco nel sistema *finchè tale processo è in esecuzione*. Il kernel di UNIX utilizza il *riciclo* del PID, cioè eseguendo due volte lo stesso programma, ad istanti differenti, *è possibile che il PID del processo cambi*. Ciò avviene perchè qualche altro processo ha ricevuto il PID del processo che ha appena terminato l'esecuzione.
		 Ci sono tre function principali per la gestione dei processi:
			 *fork()* : Crea un processo **figlio**
			 *exec()* : Inizia l'esecuzione di un processo
			 *waitpid()* : Attende lo stato di terminazione di un processo
		In questo snippet possiamo vedere come creando un processo figlio, possiamo fargli eseguire dei comandi, passati da input, e se il processo figlio sta eseguendo delle istruzioni, il padre aspetterà che esso termini tramite la waitpid():
```C
#include <error.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 255
int main(void) {
	char buf[MAXLINE];
	pid_t pid;
	int status;
	printf("%% ");
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		buf[strlen(buf) - 1] = 0;
		if ( (pid = fork()) < 0)
			perror("fork");
		else if (pid == 0) {
			execlp(buf, buf, (char *) 0);
			fprintf("couldn't execute: %s", buf);
			exit(127);
		}
		if ( (pid = waitpid(pid, &status, 0)) < 0)
			perror("waitpid");
		printf("%% ");
	}
	exit(0);
}
```
-
	*Gestione Errori*
		Per segnalare una situazione di errore, le funzioni UNIX ritornano un valore negativo, e l'intero *errno* è inizializzato ad un valore che fornisce ulteriori informazioni sull'errore. Nell'header *<errno.h>* si trovano le corrispondenze fra tali valori e le costanti numeriche associate.
		Le function per la gestione degli errori sono:
			*strerror(int errnum)* : Associa un messaggio d'errore al valore di errno
			*perror(const char * msg)* : Stampa la stringa puntata da msg, e una breve descrizione dell'errore.
	*Segnali*
		Una tecnica per notificare ad un processo l'avvenimento di una situazione d'errore è quella di inviargli un *segnale*.
		Ad esempio, se premiamo Ctrl+C inviamo un segnale **SIGINT** al processo in esecuzione.
		Un processo che riceve un segnale può svolgere una di tre azioni:
			- Ignorare il segnale
			- Eseguire l'azione di default
			- Eseguire un'azione specifica
		Per eseguire un'azione specifica, un processo può dichiarare un *handler*, ovvero una routine, che viene eseguita al posto dell'azione di default, e si possono specificare anche azioni diverse dalle classiche.
	*System Call*
		Tutti i SO forniscono interfacce attraverso cui si possono richiedere servizi al kernel. UNIX fornisce le *systemcall*, che sono punti d'accesso al kernel, cioè funzioni che quando invocate vengono eseguite dalla CPU in modalità kernel (0), infatti vengono dette *istruzioni privilegiate*. 
		Le *funzioni di libreria* mettono a disposizione dei servizi, che sono effettivamente *wrapper* delle chiamate di sistema. Le chiamate alle funzioni di libreria, come ad esempio *printf()*, sono effettivamente chiamate a delle systemcall, che vengono eseguite con i parametri delle function di libreria.
			Ad esempio, una chiamata *printf()* richiama la system call *write()*, con i parametri della function *printf()*
		La differenza fra system call e funzioni di libreria è che le funzioni di libreria **non sono punti d'accesso al kernel**, anche se utilizzano le system call. Infatti, l'esecuzione di una funzione di libreria non richiede il kernel, mentre le system call lo richiedono. Inoltre, solo alcune funzioni di libreria utilizzano le system call, mentre altre (come *atoi*) non coinvolgono il kernel.
		Per utilizzare le system call, nel codice bisogna includere alcuni header (*file d'intestazione*), in cui sono definiti i richiami delle function alle system call.

----------------------------------------------------------------------------------------

