-----------------------------------------------------------------------------------------

**Strumenti per la programmazione C**
---
*Compilazione C*
	UNIX fornisce il compilatore *gcc*, conforme allo standard POSIX. Il compilatore gcc può eseguire diverse funzioni, come la *compilazione*, il *debugging*, ed il *linking*.
```Bash
gcc [-c] [-o] [-v] [-g] [-lX] [-E] [-S]
#c : compila (si ferma alla compilazione)
#o : nomina (rinomina il file di output)
#lX : link lib (linka la libreria libX)
#g : debug (fornisce informazioni utili al debug)
#v : verbose (genera informazioni dettagliate)
#E : avvisa il compilatore di fermarsi al preprocessing
#S : avvisa il compilatore di fermarsi all'assembly
```
-
	*Compilazione*
		Tramite la compilazione, si converte il file sorgente in eseguibile, attraverso le fasi di:
			*preprocessing* : fornisce le macro per la sostituzione ripetitiva di stringhe
			*assembly* : fornisce i nomi per le locazioni di memoria
			*linking* : fornisce un modo per il riuso di codice eseguibile in programmi multipli
		*Codice Oggetto*
			Il codice oggetto (file *.o*) è il sorgente compilato, che verrà unito agli altri file oggetto per creare l'eseguibile finale.
		*Linking*
			La fase di linking collega tutti i file del progetto al fine di generare l'eseguibile, unendo i codici delle librerie al sorgente del progetto, al fine di permettere l'esecuzione del codice.
			Il linking può essere *statico* o *dinamico*.
			*Statico*
				Tutto il codice oggetto viene copiato nell'eseguibile, al fine di rendere più veloce l'esecuzione, ma si spreca più spazio
				(*gcc-static main.c -pthread*)
			*Dinamico*
				Il codice oggetto viene caricato in memoria direttamente dai file di libreria, sprecando meno spazio ma rallentando l'esecuzione.
				(*gcc main.c -pthread*)
		*Debugger*
			Dopo aver eseguito *gcc -g*, possiamo andare a *debuggare* il codice, ovvero analizzare il comportamento del sorgente ad ogni passo. Ciò è utile se ad esempio vogliamo analizzare degli errori presenti nel codice (come ad esempio il *segmentation fault*).
			Esistono diverse operazioni possibili tramite il debugger **GDB**, standard di Linux/UNIX. I comandi permettono:
				*Step* : Esegue il codice passo passo, andando alla prossima linea
				*Print* : Stampa il valore di una variabile
				*Whatis* : Stampa il tipo di una variabile
				*List* : Analizza il codice sorgente
				*Break* : Stabilire dei breakpoint
				*Display* : Visualizzare espressioni
			Per avviare gdb, si usa:
				*gcc -g < file >*
				*gdb a.out*
				Successivamente si possono usare i comandi sopra citati per analizzare il codice ed il suo andamento.
			Durante la creazione dell'eseguibile, il compilatore memorizza informazioni aggiuntive sul programma, tramite la **tabella dei simboli**. 
				Questa struttura dati mantiene la lista di nomi di variabili utilizzati dal programma, e il programma è compilato senza ottimizzazione.
			E' utile impostare dei *breakpoint* durante l'esecuzione. Essi infatti ci permettono di analizzare specifiche parti del processo, e controllare che tutto funzioni per bene. Inserendo un breakpoint, si dice al debugger di eseguire il codice fino a quel punto e poi di mettere in pausa l'esecuzione. Questa può ripartire tramite tre comandi:
				*Step* : esegue la prossima istruzione e rimette in pausa.
				*Next* : uguale a step, ma se la prossima istruzione è una chiamata ad una function, esegue tutti i passaggi
				*Continue* : continua l'esecuzione fino al prossimo breakpoint o alla fine.
			Per rimuovere i breakpoint, si usa il comando *clear*
		*Segmentation Fault*
			Un segmentation fault è un accesso illegale alla memoria, ovvero il processo tenta di accedere ad un'area di memoria oltre il registro limite assegnatogli (*PSW*). Un classico esempio di segmentation fault è dovuto al tentativo d'accesso di una locazione di memoria oltre la dimensione stabilita di un array 
				$int arr[5]; x = arr[7]$ 
				In questo caso l'errore è facilmente risolvibile
			oppure all'accesso di un array non inizializzato
				$int *buff; x = buff[3]$
				In questo caso va usata una function di allocazione della memoria per inizializzare le posizioni dell'array (*malloc, calloc, realloc*).
		*Ciclo infinito*
			Un programma è in un ciclo infinito quando la condizione del ciclo non viene mai aggiornata, oppure non arriva mai alla condizione d'uscita
				$int \ i=0;while(i<5)\{i--;i++;\}$

*Organizzazione del codice*
	Un programma efficiente è suddiviso in moduli, ovvero parti di codice di piccola dimensione, che svolgono un'unica funzione. In questo modo se dovessimo cambiare una parte del programma, sarà necessario ricompilare unicamente quella, e tutto il programma potrebbe comunque essere eseguito. Inoltre, ciò rende più facile il debugging e il controllo degli errori.
	Se un programma (*file*) utilizza una funzione, definita in un altro file, deve contenere *il prototipo* della function, e la "libreria" (*il file che contiene la dichiarazione della function*) dev'essere inclusa.

**UTILITY MAKE**
	Si potrebbe usare uno shell script per compilare un programma suddiviso in moduli.
	Ad esempio, per compilare un programma contenente i file *reverse.c*, *palindroma.c* e *reverse.h*:
```Bash
#!/bin/bash
if [ reverse.o -ot reverse.c ] || [ reverse.o -ot reverse.h ];7
then Gcc -c reverse.c 
fi 
if [ palindroma.o -ot palindroma.c ] || [ palindroma.o -ot palindroma.h ] || [ palindroma.o -ot reverse.h ]; 
then Gcc -c palindroma.c
#ecc…
```
.
	Il comando *make* consente la manutenzione e l'aggiornamento dei programmi:
		Controlla se i file sono stati modificati dopo l'ultima esecuzione
		Compila i sorgenti modificati dopo i corrispondenti file oggetto
		Ricostruisce la versione aggiornata del programma intero.
	Il comando $make [-f \ makefile]$ aggiorna un "progetto" sulla base di *regole di dipendenza*, contenute nel file **makefile**, ma con l'opzione -f si può specificare un makefile diverso, che per convenzione deve avere suffisso *.make*.
	Il makefile contiene regole/blocchi del tipo:
		$targetList : dependencyList$
		$[TAB] : commandList$
		Dove
			targetList è l'insieme dei programmi target
			dependencyList è l'insieme dei programmi da cui i target dipendono
			commandList è un insieme di comandi da eseguire
			ogni riga di commandList inizia con un TAB!
		All'interno del makefile, si possono inserire commenti tramite #.
		*Regole Makefile*
			Una linea di dipendenza definisce la relazione tra un file dipendente o target (a sinistra del carattere : ) e uno o più file di dipendenza 
			Una linea di comando o regola definisce le operazioni che make deve effettuare per passare da un file di dipendenza al target 
			Una linea di comando del makefile è eseguita se i relativi file di dipendenza sono stati modificati più recentemente dei file dipendenti associati 
			Digitando make si ottiene l'esecuzione delle linee di comando relative al primo file dipendente
			Se i file di dipendenza sono superati (non esistono), vengono eseguite anche le linee di comando necessarie al loro aggiornamento (loro creazione)
		Una **Macro** è un assegnamento di una stringa ad un nome, che da quel momento la *rappresenta*. Il valore della macro è quindi riferibile tramite 
		$\$(nome)$ o $\$\{nome\}$.
			Ad esempio, possiamo assegnare la stringa *"/usr/bin"* alla macro *PATH*. In tal modo, possiamo ad esempio cercare il file *file.c* nel percorso *PATH* invece che dover specificare sempre *"/usr/bin"*.

*Compressione dei file*
	In UNIX i file compressi e gli archivi sono indicati dal *.tar*, che è anche un comando.
	Con *tar* si possono estrarre e comprimere i file, tramite le opzioni appropriate:
```Bash
tar [-c] [-x] [-f] [-v]
#c : Crea un archivio
#x : Estrae i file dall'archivio
#f : Prende i nomi dei file da estrarre dal file FILE
#v : Crea archivio con nome NOME_ARCHIVIO
```
-
	Tar è il metodo più comunemente usato per comprimere ed estrarre i file, ma possono essere usati anche gzip/gunzip e zip/unzip, o bzip2.
	*Tar da solo non ha la capacità di comprimere i file*, ma la **versione GNU** di tar supporta le opzioni a riga di comando z(gzip), j(bzip2), e Z(bzip2), che abilitano la compressione.	

--------------------------------------------------------------------------------