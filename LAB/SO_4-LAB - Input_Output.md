-----------------------------------------------------------------------------------------

**INPUT/OUTPUT UNIX**
---
*Redirezione*
	Tutto l'I/O, inclusi *pipe*. *socket* e *file*, è gestito dal kernel mediante i *file descriptor*, cioè un intero positivo che rappresenta univocamente un file aperto, e viene usato come indice di una tabella dei file descriptor mantenuta ed usata dal kernel.
	Ogni processo figlio *eredita dal padre la propria tabella dei descrittori del file*, **ma i primi tre (0,1,2) sono assegnati al terminale** per avere i canali standard di input e output. All'apertura o creazione di un file, *il primo intero libero (**il più piccolo**) verrà assegnato al file*.
	Quando un file descriptor è assegnato ad altro che non sia un terminale, si parla di *redirezione di I/O*. La shell esegue la redirezione chiudendo il descrittore associato ad un canale standard, e assegna quel descrittore ad un file.

*Pipe*
	Le pipe costituiscono una forma di *InterProcess Communication* di UNIX.
		Una pipe consente ai processi di *comunicare* fra di loro.
		E' un meccanismo per cui **l'output di un comando è inviato in input ad un altro comando**, dove *il flusso di dati avviene in un'unica direzione*
		La shell implementa le pipe *aprendo e chiudendo i descrittori di file*. Tuttavia, invece di assegnare i descrittori ad un file, li assegna ad un *descrittore di pipe* (**tramite una systemcall**)
		In sostanza, *una pipe è un buffer kernel da cui ambo i processi possono condividere dati*, eliminando così la necessità di file temporanei intermedi.
	L'output di un comando è inviato al buffer, che quando è pieno o quando il comando ha terminato, viene letto dal processo che riceve tale input. Il kernel sincronizza le attività, in modo che un processo attenda mentre l'altro legge da o scrive nel buffer.
```Bash
who | wc
```
-
	Questo snippet esegue una pipeline (*ovvero una sequenza di comandi a mo' di pipe*). Volendo eseguire la sequenza di comandi senza pipe:
```Bash
who > outputfile
wc outputfile
rm outputfile
```
-

**SEGNALI**
---
*Inviare segnali*
	Per inviare un segnale ad un processo, si usa il comando *kill*, tramite PID del processo.
```Bash
kill [-s segnale] <pid>
```
-
	Per elencare tutti i segnali, si usa *kill -l*
	Per inviare un segnale di stop si usa *kill -s stop < PID >*
	Per far riprendere l'esecuzione al processo si usa *kill -s cont < PID >*
	Tutti i processi avviati da shell vengono eseguiti in *foreground*, assumendo il controllo del terminale. Tuttavia, è possibile farli runnare in *background*, usando il comando $<nomecomando> \&$ 
	Altri modi per intervenire sulla modalità d'esecuzione sono:
		*Ctrl+Z* : sospende un processo foreground in esecuzione
		*fg* : ripristina in foreground un processo sospeso
		*bg* : ripristina in background un processo sospeso
		*jobs* : mostra tutti i processi *in background*

**LINK**
	I link sono *scorciatoie* per accedere ai file o alle directory, che vengono usate frequentemente, condivise, usate attraverso nomi differenti.
	Permettono di avere più di un punto d'accesso per lo stesso file o directory, ma le informazioni rimangono in un'unica copia.
	Abbiamo due tipi di link:
	*Soft Link*
		Sono simili ai collegamenti di Windows : il file creato contiene solo il nome del riferimento.
		![[Pasted image 20230508171407.png]]
		Un link *simbolico* corrisponde ad un file speciale, che contiene il path name del file collegato:
			Quando accediamo al file tramite link simbolico, il path name viene seguito per recuperare le informazioni relative al file.
			In questo caso, la cancellazione del link simbolico non modifica il file originale. La cancellazione del file da parte dell'owner rende automaticamente il file inaccessibile a tutti i link simbolici ad esso collegati.
			Lo svantaggio di questa tecnica è il maggior spreco di memoria e la maggior lentezza nell'accesso.
	*Hard Link*
		Non viene creato alcun file, si fa riferimento agli stessi dati fisici, ed i due nomi diventano equivalenti.
		![[Pasted image 20230508171445.png]]
		Un link permette di accedere ad un file utilizzando un nuovo path name. Se utilizzo un *hard link* i due file faranno riferimento allo stesso i-node
			Il numero di hard link che fanno riferimento ad un i-node è memorizzato in un campo dell'i-node stesso (*count*)
		Quando un utente cancella un link ad un file, il contatore viene decrementato, é*ma l'i-node sarà eliminato solo quando il counter raggiunge lo 0*.
		Questa soluzione ha il pregio di risparmiare memoria e di permettere accessi veloci ai file collegati, ma può generare soluzioni anomale, in cui un file continua ad essere presente nel FS anche dopo che l'owner effettivo lo ha rimosso *con successo*

**Input/Output in UNIX**
---

*Gestione dei file*
	Le system call per la gestione dei file permettono di manipolare:
		1) file *regolari*
		2) directory
		3) file *speciali*
			1) *Link Simbolici*
			2) Dispositivi (*terminali, stampanti..*)
			3) Meccanismi di IPC (*pipe, socket,...*)
	Le system call seguenti realizzano le operazioni di base per la gestione dei file:
		1) *open()* : apre o crea un file
		2) *read()* : legge dati da un file
		3) *write()* : scrive dati su un file
		4) *lseek()* : sposta l'offset del file
		5) *close()* : chiude il file
	*Condivisione di file*
		UNIX supporta la condivisione dei file aperti fra vari processi. Il kernel usa tre strutture dati per rappresentare un file aperto: le relazioni tra essi determinano l'effetto che un processo ha su di un altro rispetto alla condivisione di file.
			1) *Ogni processo ha un'entrata nella tabella dei processi* :
				all'interno di ogni entrata nella tabella c'è una *tabella di descrittori di file* aperti. A ciascun descrittore sono associati *i flag* del descrittore, e *un puntatoe all'entrata della tabella dei file*.
			2) Il kernel mantiene una *tabella di file* per tutti i file aperti, ciascuna entrata contenente :
				*I flag* dello stato del file (read, write, append, ...)
				L'*offset* corrente del file
				*un puntatore all'entrata della tabella dei v-node* per il file
			3) Ogni file *o device* aperto ha una *struttura v-node che contiene informazioni sul tipo di file e puntatori a funzioni che operano sul file*:
				Il v-node contiene anche *l'i-node* per il file
				Queste informazioni sono lette da disco all'apertura del file.
		Linux non possiede v-node, ma è usata una generica struttura i-node. Sebbene l'implementazione cambi, il v-node è **concettualmente identico**.
		![[Pasted image 20230508172959.png]]
		Con due processi aventi lo stesso file aperto:
			Un processo ha il file aperto sul descrittore 3
			L'altro processo avrà il processo aperto sul descrittore 4
			Ogni processo che apre il file ha la propria entrata nella tabella dei file, sebbene sia richiesta, per un dato file, solo una singola entrata della tabella dei v-node. La ragione per cui ciascun processo ha la sua entrata è che *ogni processo ha il suo offset per lo stesso file*.
		![[Pasted image 20230508173208.png]]

**OPERAZIONI ATOMICHE**
	Sui file possono venir aggiunti dei byte (*tramite append()*), oppure scritti altri dati (*tramite write()*)
	Questo tipo di operazioni non comporta alcun problema per un *unico* processo, ma se ci sono più processi a svolgere tali operazioni, possono verificarsi dei problemi, detti **race condition**.
	![[Pasted image 20230509122926.png]]
	L'operazione *posizionati e scrivi* non è un'unica operazione, ma consiste di due sotto-azioni, dunque viene definita *non atomica*. Le operazioni **atomiche** sono quelle operazioni che vengono svolte in un'unico istante. Una qualsiasi operazione che richiede *più di una chiamata ad una function **può essere interrotta***. Quindi, si può avere il caso in cui un processo comincia l'esecuzione di *posizionati*, arriva al punto prestabilito, ma viene interrotto, e parte l'azione di un altro processo. Quando quest ultimo termina o viene bloccato, il processo interrotto prima riparte da dove si era fermato, quindi scrivendo al punto in cui si trovava. Può capitare che quel punto contiene dati di altri processi, andando quindi a *sovrascriverli*.
	Un modo per eseguire l'operazione *posizionati e scrivi* in maniera atomica, è quello di usare la macro **O_APPEND** all'apertura del file per *ogni processo*.

*Duplicare i descrittori*
	Le system call *dup()* e *dup2()* permettono di duplicare un file descriptor, con una differenza : 
		*dup()* lo fa **sul primo descrittore libero**
		*dup2()* lo fa **su uno specifico**, *passato per parametro*
	Duplicando il file descriptor, si prende un nuovo descrittore, che punta alla stessa entry della tabella dei file aperti, quindi non ci sono problemi.
	![[Pasted image 20230509123457.png]]

**Gestione degli errori**
---
*Systemcall*
	Una system call di solito ritorna -1 al fallimento, e 0 se riesce, ma dipende dai casi.
	Per controllare il valore di fallimento, o le situazioni di errore in generale, ci sono due modi standard:
	*errno* :
		E' un intero che rappresenta le costanti d'errore relative alle situazioni di errore avvenute.
		Per utilizzare errno, si include la libreria *errno.h*, che contiene le correlazioni tra le costanti d'errore ed i valori assunti dall'intero.
	*perror()* :
		Questa system call stampa un messaggio d'errore che informa il programmatore sulla situazione.
		Per utilizzarla, si include la libreria *error.h*, che contiene i valori d'errore e le relative stringhe da stampare.
	Alcuni valori d'errore standard sono:
		*EPERM 1* : Operation non permitted
		*ENOENT 2* : No such file or directory
		*ESRCH 3* : No such process
		*EINTR 4* : Interrupted system call
		*EIO 5* : I/O Error
	Quando una system call fallisce, *sovrascrive il valore di errno*, permettendoci quindi di risalire all'errore avvenuto.

-----------------------------------------------------------------------------------------
