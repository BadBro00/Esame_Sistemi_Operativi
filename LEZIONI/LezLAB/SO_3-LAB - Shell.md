-----------------------------------------------------------------------------------------
**SHELL UNIX**
---
*Shell di Linux*
	La shell è un programma speciale, usato come interfaccia fra l'utente ed il kernel. La shell può eseguire i comandi, come il kernel, ma è a tutti gli effetti un processo.
	Dopo il login, viene avviata la shell, che resta in attesa di un comando. Quando questo viene inserito, è responsabilità della shell:
		Fare il parsing della stringa di input per ottenere la sequenza di comandi
		Gestire i simboli *wildcard*, le pipe, la redirezione, ed il controllo dei job
		Cercare un comando, e se trovato, eseguirlo
	Esistono tre shell predominanti su Linux, e queste sono:
		*Bourne Shell* 
		*Bourne Again Shell*
		*Korn Shell*
		*C Shell*
	Le shell presenti sul sistema che possono essere usate dall'utente sono indicate nel file */etc/shells*.
	*Usi della shell*
		*Interprete dei comandi*
			La shell può fungere da interprete dei comandi, svolgendo la seguente sequenza di passi:
				1) Esegue il parsing della stringa di input in *token*
				2) Se dal parsing trova un comando, lo ricerca
				3) Se il comando viene trovato tra i comandi interni alla shell, e se lo trova ne avvia l'esecuzione
		*Personalizzazione Ambiente Utente*
			La shell può personalizzare l'ambiente dell'utente, tramite i *file d'inizializzazione* della shell. Questi contengono le definizioni per impostare:
				1) Il terminale e le caratteristiche della finestra
				2) Le variabili che definiscono i percorsi di ricerca, permessi, prompt e tipo di terminale
				3) Le variabili richieste per applicazioni specifiche
				4) La Bash fornisce anche ulteriori personalizzazioni per l'aggiunta della storia, per gli alias e variabili built-in, impostate per proteggere l'utente dal danneggiare file, fare logout in modo inavvertito o notificare l'utente quando un job è completo.
		*Linguaggio di programmazione Interpretato*
			Gli *shell script* consistono di comandi *elencati in un file*, e sono creati con un editor e contengono comandi UNIX/Linux inframezzati con costrutti fondamentali di programmazione, quali assegnamenti di variabili, test
			condizionali e cicli.
			Gli script non vanno compilati, e la shell interpreta ogni linea come se fosse immessa da tastiera.

*Startup sistema e Shell di Login*
	Quando viene avviato il sistema, il primo processo a partire è *init*, con PID 1. Esso poi crea un processo *getty*, che
		Apre i canali di comunicazione standard (0,1,2), e pone sullo schermo un prompt di login.
	Viene poi eseguito il programma */bin/login* che 
		Richiede una password, la crittografa e la confronta con quella contenuta nel file */etc/passwd*
	In caso di corrispondenza imposta un ambiente iniziale, e avvia il processo */bin/bash*, cioè la shell
	Il processo bash
		Cerca il file di sistema */etc/profile* ed esegue i suoi comandi.
		Poi cerca nella home il file di inizializzazione *.bash_profile* e ne esegue i comandi.
		Successivamente esegue un comando dal file d'ambiente, solitamente *.bashrc*, ed infine appare il prompt di default ($) sullo schermo.
	![[Pasted image 20230502160948.png]]
	Alle variabili *HOME*, *SHELL*, *USER* e *LOGNAME* sono assegnati i valori estratti da */etc/passwd*, e viene impostata la variabile *PATH* alle directory in cui si trovano le utility usate più frequentemente. Quando il programma login ha terminato, esegue l'ultima riga del file *passwd*, che è la shell di login. Essa controlla la directory *home* per verificare se esistono file di inizializzazione specifici della shell, e in caso li esegue.
	*Parsing riga di comando*
		Quando si inserisce un comando, la shell analizza l'input e lo divide in token, separando le parole agli spazi. La riga di comando è divisa dal carattere *newline* (*\n*).
		La shell controlla se la parola in esame è un comando built-in o un programma eseguibile, localizzato da qualche parte su disco:
			Se è *built-in*, esegue il comando internamente
			Altrimenti, lo ricerca all'interno delle directory specificate in *PATH* per sapere dove risiede il programma:
				Se viene trovato, la shell fa *fork*, ed esegue il processo
				La shell intanto attenderà la terminazione e, se necessario, riporterà lo stato del programma terminante.
	*Tipi di comandi*
		Quando viene eseguito un comando, esso corrisponderà a:
			1) Un *comando built-in*
			2) Un *alias* : abbreviazioni di comandi (*mv*,*ls*,..)
			3) Un programma eseguibile *su disco*
			4) Una funzione : gruppi di comandi raggruppati in routine
		La shell utilizza la variabile *PATH* per localizzare i programmi su disco, e crea un processo figlio prima che il programma venga eseguito.
		Quando la shell è pronta per eseguire il comando, valuta il tipo di comando secondo l'ordine:
			Alias
			Keyword
			Funzione
			Built-In
			Eseguibile

*Processi e Shell*
	Una shell è un processo in esecuzione, ma la shell può far avviare altri programmi ed interfacciarsi col kernel
	*Processi in esecuzione*
		Il comando *ps* visualizza un elenco dei processi attivi nel sistema. Vi sono diverse varianti, come *ps aux* o *pstree*
		ps possiede molte opzioni utili a visualizzare diversi tipi di processi:
```Bash
ps [aux] [tree] [-a] [-x] [-e]
#aux : mostra informazioni aggiuntive sui processi (tty,start,stat,...)
#tree : mostra i processi in una gerarchia ad albero
#a : (all) mostra tutti i processi
#x : mostra i processi non controllati da terminale
#e : mostra
```
-
	*Proprietà e Permessi*
		Effettuato il login, la shell è dotata di un'identità:
			Un *Real User ID* (UID)
			Uno o più *Grup ID*(GID)
			Un *Effective User ID* e un *Effective Group ID* (EUID+GID)
		E' possibile usare il comando *id* per conoscere tali valorif
	*Permessi*
		Ogni file UNIX/Linux ha un insieme di permessi ad esso associati per controllare chi può:
			Leggere (*r*)
			Scrivere (*w*)
			Eseguire (*x*)
		Un totale di nove bit esprime tutto ciò che ciascun utente può fare con il file. Questi nove bit sono la combinazione dei permessi dei vari utenti e delle azioni che possono fare per ciascun tipo, sul file:
			3 bit sono riservati all'utente : *r w x* in qualunque combinazione sono i permessi che l'utente ha sul file. Sono i tre bit più a sinistra.
			3 bit sono riservati al grouppo : *r w x* in qualunque combinazione sono i permessi che *gli utenti appartenenti al gruppo* hanno sul file. Sono i tre bit centrali.
			Gli ultimi tre bit sono riservati agli altri (*Others*) : *r w x* in qualunque combinazione sono i permessi che *gli utenti esterni al gruppo del proprietario del file* hanno sul file. Sono gli ultimi tre bit a destra.
		![[Pasted image 20230503150038.png]]
		Quando un file viene creato, gli vengono impostati dei permessi di default. Per cambiare i permessi su un file, bisogna essere il proprietario. Sui permessi di un file può essere applicata una *maschera* per nascondere alcuni valori e quindi negare alcuni permessi ad alcuni utenti. Tale maschera può essere impostata tramite *umask()* o da shell. Inizialmente, umask vale *000*, non nascondendo alcun bit di permesso, ma può essere impostata in un qualunque valore intermedio, fino a *777*, nascondendo tutti i bit di permesso.
	*Cambiare Permessi e Proprietà*
		Tramite il comando *chmod*, si possono :
			*Cambiare i permessi* dei file e delle directory
			Solo *il proprietario o root* possono cambiare i permessi su un file o una directory
			Un gruppo può avere un qualunque numero di membri, ma *il proprietario del file può cambiare i permessi del gruppo su un file in modo che il gruppo possa beneficiare di permessi speciali*
			Per vedere i permessi di un file, si può usare il comando *ls -l < nomefile >*
```Bash
chmod [-a] [-g] [-u] [-o] {+} {-} <permessi> <nomefile> 
#a : tutti gli utenti
#g : utenti del gruppo
#o : others
#u : user

#+ : aggiungere permessi
#- : togliere permessi

#permessi : r (read) ; w (write) ; x (execute)
```
-
		Tramite il comando *chown* invece si può modificare *il proprietario* del file
		Sui sistemi Linux solo root può cambiare il proprietario di un file
		Sui sistemi UNIX solo il proprietario o root possono cambiare il proprietario
	*Impersonare altri utenti*
		Tramite il comando *su*, si può assumere l'identità di un altro utente, per un certo periodo di tempo (ad es, per eseguire un comando). 
		$su <nome\_user>$ permette di impersonare l'utente scelto, mentre $su <root>$ permette di impersonare il superuser. Si può usare anche $su$ senza parametri, in quel caso *per default si impersona root*.
		A seguito del comando, **si chiede sempre la password dell'utente scelto**.

**DIRECTORY DI LAVORO**
	*Current Directory*
		Ad un utente che ha effettuato il login, viene assegnata una directory nel file system detta *home directory*.
		La directory di lavoro è ereditata dai processi generati dalla shell. Un processo può cambiare la directory di lavoro tramite il comando *cd*, ma  questo cambiamento non avrà effetto sul processo padre (che può essere anche la shell).
		Il comando *cd* è un comando built-in della shell:
			Ogni shell ha la propria copia del comando cd : un comando built-in è eseguito direttamente dalla shell, come *parte del codice della shell*. La shell non esegue system call *fork* o *exec* per eseguire comandi built-in.
			Se un'altra shell (script) è generata dal processo shell padre, ed è eseguito un comando *cd* dalla shell figlia, il risultato sarà locale alla shell figlia, cioè la directory di lavoro cambierà solo per la shell figlia : quando il processo shell figlio termina, la shell padre si troverà nella stessa directory in cui si trovava quando ha creato la shell figlia.
	*Variabili*
		La shell può definire due tipi di variabili: *locali* e *di ambiente*. Le variabili contengono informazioni usate per la personalizzazione della shell e informazioni richieste da altri processi, in modo da poter funzionare.
		*Locali*
			Sono private alla shell che le ha create, e non sono passate ad alcun processo generato dalla shell
		*d'Ambiente*
			Sono passate da padre a figlio. Alcune variabili d'ambiente sono ereditate dalla shell di login dal programma */bin/login*, altre sono create nei file d'inizializzazione dell'utente, negli script o da riga di comando.
		Se una variabile d'ambiente è impostata in una shell figlia, non arriverà alla shell padre. Il comando built-in *set* mostra le variabili locali e d'ambiente, mentre il comando *env* solo quelle d'ambiente.


**BASH**
	*Comando set*
		Il comando built-in set prende opzioni quando è usata l'opzione *-o* : le opzioni consentono di personalizzare l'*ambiente* della shell. Tali opzioni possono essere attivate o disattivate normalmente nel file *.bashrc*
```Bash
set -o [option] #Attiva l'opzione
set +o [option] #Disattiva l'opzione
set -[a-z] #Attiva l'abbreviazione per un'opzione
set +[a-z] #Disattiva l'abbreviazione per un'opzione
```
-
	*Comandi Shell*
		Tutti i comandi eseguiti vengono memorizzati nel file di sistema *.bash_history*. Per visualizzare i comandi presenti in tale file, che è nascosto, si può usare *ls -a* per visualizzare il file e poi *cat* per leggerlo, oppure usare il comando *history* per leggere direttamente i comandi eseguiti, che equivale a *cat .bash_history*.
			Digitando *history* si ottiene un output del genere:
			1 ls
			2 cd < dir >
			3 cat < file >
			E inserendo il comando !3 si ri-esegue il comando cat < file >, ottenendo quindi l'output a schermo.
		I principali comandi per ottenere informazioni sullo stato del sistema Linux sono:
			*date* : indica la data e l'ora del sistema
			*who* : indica gli utilizzatori connessi al sistema
			*cal* : visualizza il calendario
			*man* : visualizza la documentazione integrata (manuale Linux)
	*Alias*
		Un alias è un'abbreviazione di un comando, definita dall'utente della bash : sono utili se un comando ha una serie di opzioni ed argomenti, o se la sintassi è difficile da ricordare.
		Gli alias di solito sono impostati nel file *.bashrc*, ma quelli impostati da riga di comando *non sono ereditati dalle subshell*, che esegue il file *.bashrc* che non conterrà gli alias impostati da riga di comando.
		Il comando built-in *alias* riporta tutti gli alias impostati.
		Per creare un alias, si può usare *alias*, tramite $alias < alias > \ = \ < comando >$.
		Per cancellare un alias, si può usare *unalias*, o per disattivarlo *temporaneamente* si può inserire il nome dell'alias *preceduto da \\*.
	*Comandi frequenti per la gestione delle directory*
		![[Pasted image 20230503160426.png]]
		*whoami* serve a capire come siamo loggati nella macchina
		*ls < directory >* serve ad elencare i file nella directory
		*touch (-a) (-c)*  è usato per modificare gli istanti di accesso e modifica al file, o crearlo se non esiste
		*cp < sorg > < dest >* copia un file 
		*mv < nome1 > < nome2 > (rinomina)/ < sorg > < dest >(sposta)* sposta o rinomina un file
		*rm < nome >* rimuove un file
		*find < dir > < nome > (cerca il file nella dir) / < nome > (cerca il file ovunque) /  < ctime >  (cerca i file creti in ctime giorni) / < size > (cerca i file tramite size)* cerca i file in base a nome, dimensione, data di creazione
		*sort (-r) < nome >* ordina i file in ordine alfabetico

-----------------------------------------------------------------------------------------
