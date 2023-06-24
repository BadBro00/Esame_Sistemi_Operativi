-----------------------------------------------------------------------------------------
**Gestione dei Processi**
---
*Definizione di un Processo*
	Un processo è costituito da istruzioni e dati ed è memorizzato in un file.
	*Avvio di un processo*
		Un processo può essere avviato da shell o da codice (tramite chiamata ad *exec*). Quando si esegue un programma, viene prima eseguita una routine di start-up speciale, specificata come indirizzo di partenza del programma eseguibile, che prende:
			- Valori passati dal kernel in *argv[]* tramite riga di comando
			- Variabili d'ambiente
		Successivamente, è chiamata la funzione *main()*, che ha come parametri *argc* che è il numero degli argomenti, e *argv* che è il vettore degli argomenti, in formato stringa.
	*Terminazione di un processo*
		Esistono 8 modi per terminare un processo:
		*Terminazione normale*
			1) Chiamata alla funzione *exit()*
			2) Ritorno dal main
			3) Chiamata a *_exit()* o *_Exit()*
			4) Ritorno dell'ultimo thread dalla sua routine d'avvio
			5) Chiamata a *pthread_exit()* dell'ultimo thread
		*Terminazione anomala*
			1) Chiamata di *abrt*
			2) Ricezione di un segnale
			3) Risposta dell'ultimo thread ad una richiesta di cancellazione
		**La routine d'avvio fa in modo che quando la funzione del main ritorna venga chiamata la function exit()**
	*Inizio e fine di un programma C*
		![[Pasted image 20230510104045.png]]
	*Argomenti da riga di comando*
		Quando è eseguito un programma, il processo che esegue l'exec può passare degli argomenti da linea di comando al nuovo programma.
		*Environment List*
			Ad ogni programma è passata una lista dell'ambiente, cioè un array di puntatori a stringhe, in cui ogni puntatore contiene l'indirizzo di una stringa C, terminata con NULL (*\0*), e l'indirizzo dell'array è contenuto nella variabile *environ*.
			Per convenzione, l'ambiente consiste in stringhe *nome = valore*
			![[Pasted image 20230510104408.png]]
		*Struttura della memoria per un programma*
			Un programma C è composto da vari "pezzi":
				*Segmento di testo*
					Contiene le istruzioni e i dati, sia *condivisibili* sia *a sola lettura*
				*Segmento di dati inizializzati*
					Contiene variabili globali e statiche inizializzate nel programma
				*Segmento di dati non inizializzati*
					Contiene le variabili a cui non è stato assegnato un valore iniziale nel programma
				*Stack*
					Contiene le variabili automatiche, con le informazioni salvate *ogni volta che viene chiamata una funzione*. Mantiene quindi indirizzi di ritorno e registri. La funzione chiamata *alloca spazio* per le variabili automatiche e temporanee.
				*Heap*
					Luogo in cui avviene l'allocazione dinamica della memoria *tra il segmento di dati non inizializzati e lo stack*
			![[Pasted image 20230510104944.png]]
			Tramite il comando *size*, possiamo vedere la dimensione in byte dei segmenti di testo, dati e bss.
			![[Pasted image 20230510105031.png]]
	*Controllo dei processi*
		Un processo consiste nell'insieme di eventi che accadono durante l'esecuzione di un programma : esso è un'entità dinamica cui è associato un insieme di informazioni necessarie per la corretta esecuzione e gestione da parte del SO.
		Il processo UNIX mantiene spazi di indirizzamento *separati* per dati e codice, ed ogni processo ha uno spazio d'indirizzamento dei dati privato, per cui è necessario usare una forma di comunicazione interprocessi per scambiarsi informazioni e dati. Invece, lo spazio d'indirizzamento del codice è *condivisibile*, più processi possono essere eseguiti facendo riferimento alla stessa area di codice della memoria centrale.
	*Caratteristiche dei processi UNIX*
		Nel caso di un processo pesante con codice *rientrante*, i dati non vengono condivisi, ma il codice è condivisibile con altri processi.
		*Stati del processo*
			In UNIX esistono vari *stati* in cui un processo può trovarsi, in base alle situazioni che si verificano durante l'esecuzione.
			Gli stati sono:
				*Ready*
					Il processo è pronto per l'esecuzione, ma non è stato schedulato
				*Running*
					Il processo sta usando CPUburst per eseguire le sue istruzioni
				*Blocked*
					Il processo è in attesa di un evento
				*Terminated*
					Il processo ha terminato (*in qualunque modo*) la sua esecuzione
			Esistono anche stati aggiuntivi, dettati dal fatto che un processo può essere *swappato*, cioè posto temporaneamente nel disco prima di aver terminato, per far spazio ad un altro processo.
			Tali stati sono:
				*Swapped Ready*
					Se il processo swappato si trovava nello stato ready, bisogna poi riporlo nella coda dei processi ready
				*Swapped Blocked*
					Se il processo era in attesa di un evento, deve essere posto nella coda dei processi blocked se tale evento non si è verificato
			Infine, abbiamo lo stato *zombi*, in cui il processo **ha terminato**, ma il padre deve prelevare lo stato di terminazione
			![[Pasted image 20230510113657.png]]
		*Rappresentazione dei processi*
			Il codice dei processi è *rientrante*, cioè più processi possono condividere lo stesso codice (*segmento di testo*), per cui:
				Codice e dati sono separati
				Il SO gestisce una struttura dati *globale* in cui sono contenuti i puntatori ai segmenti di testo (eventualmente condivisi) dei processi (*Text Table*)
				L'elemento di tale struttura dati è detto *Text Structure*, e contiene tra gli altri elementi :
					Un puntatore al segmento di testo (se il processo è swapped, *il riferimento alla memoria secondaria*)
					Numero dei processi che lo condividono
			Il *Process Control Block* è rappresentato da due strutture dati:
				*Process Structure*
					Contiene le informazioni necessarie al sistema per la gestione del processo, *a prescindere dallo stato*
				*User Structure*
					Mantiene le informazioni necessarie *solo se il processo è in memoria centrale*
				![[Pasted image 20230510114234.png]]
			*Immagine di un processo*
				L'immagine di un processo è l'insieme delle aree di memoria e delle strutture dati associate al processo. Non tutta l'immagine è accessibile in mode User (1). Ogni processo può essere soggetto a *swapping*, in quanto *non tutta l'immagine può essere trasferito in memoria*: vi sono la parte *swappabile* e la parte *residente*
				![[Pasted image 20230510114516.png]]
				In UNIX l'immagine di un processo è divisa in :
					*Process Structure*
						Kernel, Residente. E' l'elemento della process table associato al processo
					*Text Structure*
						Kernel, Residente. E' l'elemento della Text Table associato al codice del processo
					*Area dati globali utente*
						User, Swappable. E' suddivisa nei due segmenti di dati
					*Stack, Heap Utente*
						User, Swappable. Sono le aree dinamiche associate al processo eseguito
					*Stack Kernel*
						Kernel, Swappable. Stack di sistema associato al processo per le chiamate a system call
					*U-Area*
						Kernel, Swappable. Struttura dati contenente i dati necessari al kernel per la gestione del processo quando è residente.
		*Processi*
			All'avvio del SO, vi è solo un programma in memoria, cioè *init()*. Tale processo è invocato dal kernel dopo la procedura *bootstrap*, e ha sempre PID uguale a 1. Init crea i processi *getty()* responsabili di gestire i login degli utenti.
			Il processo con PID 0 è lo *scheduler*, noto anche come *swapper* : a tale processo non corrisponde alcun file su disco perchè è parte del kernel, e dunque è *un processo di sistema*.
		![[Pasted image 20230510143229.png]]
		*Creazione di processi*
			Quando un processo è duplicato, il processo padre ed il figlio sono virtualmente identici : il processo figlio eredita tutte le variabili del processo padre, ma differisce per alcuni aspetti ad esempio il PID, PPID e risorse a runtime.
			Quando un processo figlio termina tramite *exit()*, il padre riceve un segnale che il figlio ha terminato, e può prelevarne lo stato di terminazione, tramite *waitpid()*, o meno.
		*Terminazione di processi*
			In UNIX, la terminazione di un processo consiste in una serie di operazioni che lasciano il sistema in stato *coerente*: 
				Chiusura dei file aperti
				Rimozione dell'immagine dalla memoria
				Eventuale segnalazione al padre
			Per gestire quest ultimo aspetto, UNIX impiega le sistem call *exit()* per il figlio, e *wait()* (*waitpid()*) per il padre, in modo coerente:
				Tramite *exit()*, avviene la terminazione dell'esecuzione del processo figlio
				Tramite *wait()*, il padre attende la terminazione del processo figlio.
			*Processi Zombi*
				Un processo che termina non scompare dal sistema *finchè il padre non ne preleva lo stato di terminazione*:
					Un processo che sta aspettando che il padre prelevi il suo stato di terminazione è detto *zombie* (**defunct**)
					Se il padre non termina e non esegue mai una *waitpid()*, il processo rimarrà sempre in stato *defunct*
					Un processo zombi non ha aree di codice, dati o pil allocate, quindi non usa molte risorse di sistema, ma *ha un PCB allocato* nella tabella dei processi (*di grandezza fissa*).
			*Processi adottati*
				Se un processo padre termina prima di un figlio, quest ultimo viene detto *orfano*. Il kernel assicura che tutti i processi orfani siano adottati da *init()*, e assegna loro PPID 1. Quando un processo adottato da init termina :
				Il processo adottato non diventa zombi, perchè init è scritto in modo che se un qualsiasi processo figlio termina, richiami la function *waitpid()* per determinarne lo stato d'uscita. **In questo modo, init previene la proliferazione di processi zombie**.
			*Race Conditions*
				Le race condition si verificano quando possono esserci più operazioni che modificano gli stessi dati in contemporanea. Il risultato finale dipende dall'ordine in cui i processi vengono eseguiti. In generale, non è prevedibile quale processo venga schedulato prima di tutti gli altri, o l'ordine dello scheduling, per cui si cerca di progettare una soluzione che sia indipendente dall'ordine di schedulazione.
				Per evitare le race condition, si devono usare metodi di segnalazione o forme di IPC.
	*Esecuzione di comandi da shell*
		L'esecuzione di comandi corrisponde ad una serie di stringhe, separate da spazi. La prima di queste stringhe corrisponde al *comando* da eseguire, mentre le rimanenti sono *gli argomenti* del comando. Ogni comando termina con un *exit status* che identifica la terminazione del comando, ed è un intero che può assumere diversi valori:
			- 0 : l'esecuzione del comando è riuscita con successo
			- n>0 : l'esecuzione è fallita
			- 128+n : l'esecuzione è terminata in seguito al segnale numero
		L'esecuzione di un comando *sospende temporaneamente la shell*, fino a quando non termina.
		![[Pasted image 20230515140244.png]]
	*Esecuzione di una pipeline da shell*
		L'operatore *pipe* ( **|** ) consente alla shell di connettere tra loro due comandi, nell'ordine in cui vengono scritti. La pipeline *com1 | com2 | com3* eseguirà prima *com1*, poi il suo output verrà fornito come input del comando *com2*, e lo stesso accadrà tra l'output di *com2* e l'input di *com3*
		![[Pasted image 20230515144536.png]]
	*Liste di Comandi*
		Le liste di comandi consentono di eseguire in maniera sequenziale più comandi, come se costituissero un unico comando. La sintassi è:
			*com1 [; com2]  [;]*
			Dove com1 e com2 possono essere pipeline
		L'exit status corrisponde all'exit status dell'*ultimo* comando. La shell attende che *tutti* i comandi nella lista abbiano terminato l'esecuzione, prima di restituire il prompt. *Non c'è collegamento fra input di un comando ed output di un altro*.
		![[Pasted image 20230531082425.png]]
	**SEGNALI**
		I segnali sono usati per notificare una situazione d'eccezione o d'errore ai processi. Un processo può inviare ad un altro processo un segnale, *rendendoli così una forma di IPC*. La sorgente principale di segnali inviati è il Kernel, e le situazioni eccezionali, che generano eventi affinchè il kernel invii segnali, sono di tre tipi:
			1) *Eccezione HW* :
				L'HW ha individuato una condizione d'errore che notifica al kernel, che ne invia a sua volta uno al processo
			2) *Digitazione carattere speciale* :
				L'utente durante l'esecuzione di un processo può digitare alcuni comandi nel terminale (*Ctrl+C, Ctrl+Z,..*), che sono detti *caratteri speciali*, che influenzano l'esecuzione.
			3) *Evento SW* : 
				Un evento SW nasce da un processo del sistema o dell'utente, come ad esempio la terminazione di un figlio, oppure se l'output è disponibile su un file, ecc..
		Ogni segnale è definito da un *intero*, la cui corrispondenza con il segnale è definita nella libreria *signa.h*,  nella forma simbolica *SIGXXXX*. I segnali ricadono in due categorie:
			*Segnali Tradizionali* : Usati dal kernel per notificare gli eventi relativi ai processi
			*Segnali Real-Time*
		La *disposizione* per un segnale è l'indicazione al kernel su *cosa fare in seguito alla ricezione del segnale*. Ogni processo può eseguire un'azione di default, ignorarlo oppure *eseguire un'azione definita dal programmatore* (**handler**)
		Un segnale è stato *generato* quando si verifica un evento nel SO; è *consegnato* quando è intrapresa un'azione da parte del processo cui arriva il segnale; è invece *pendente* se è stato generato ma non ancora consegnato.
		![[Pasted image 20230601101331.png]]
		Un processo che riceve un segnale deve anche *chiedere al kernel che azione intraprendere*. L'azione che eseguirà è una fra *ignorare il segnale*, *eseguire l'azione di default* oppure *eseguire un handler* (**intercettare il segnale**). Solitamente l'azione di default fa terminare il processo, ma possono esserci situazioni diverse.
	*Gestore Segnali*
		L'invocazione di un gestore puo' *interrompere il flusso principale di un programma* in qualsiasi momento. 
		Il kernel invoca il gestore per conto del processo, e quando il gestore *ritorna*, **l'esecuzione del programma riprende nel punto in cui era stata interrotta dal gestore**.
	*Segnali ed avvio dei programmi*
		Quando un programma viene eseguito, l'azione di default associata a ciascun segnale e' quella di *default*, o di *ignorarlo*. Tutti i segnali sono impostati all'azione di default, *a meno che il processo che invoca exit stia ignorando il segnale*. 
		I processi creati tramite fork *ereditano la disposizione dei segnali* dei genitori.
		Un segnale intercettato in un processo **non puo' essere intercettato da un eseguibile avviato con exec**.
	*Segnali Inaffidabili*
		Nelle prime versioni di UNIX, i segnali erano inaffidabili, in quanto potevano andar persi. Un processo aveva poco controllo sul segnale. 
		Talvolta ha senso *catturare* il segnale, ma non **ignorarlo**, in modo da poterne ricordare l'occorrenza.
		Il processo non ha la possibilita' di bloccare il segnale quando si verifica, ma puo' al piu' ignorarlo. Ci sono casi in cui e' necessario prevenire, *ma ricordare*, l'occorrenza di un segnale.
	*Rientranza delle Funzioni*
		Non tutte le chiamate di sistema e le funzioni di libreria possono essere invocate con sicurezza dal gestore.
		Per spiegare la *rientranza* delle funzioni, si deve capire a fondo la **differenza fra programmi mono e multi thread**:
			1) I classici programmi UNIX hanno *un unico thread in esecuzione*:
				La CPU elabora le istruzioni per un *singolo flusso logico di esecuzione* attraverso il programma.
			2) In un programma *multithread*, ci sono piu' flussi logici indipendenti e *concorrenti* di esecuzione, all'interno dello stesso processo.
			3) Il concetto di thread multipli d'esecuzione e' rilevante per programmi *che impiegano i gestori dei segnali*.
		Un gestore puo' interrompere in modo *asincrono* l'esecuzione di un programma **in un qualunque istante temporale**. E' come se il programma e il gestore costituissero due thread di esecuzione indipendenti (**sebbene non concorrenti**) all'interno dello stesso processo.
		Una funzione e' detta **rientrante** se *puo' essere eseguita **simultaneamente** in modo sicuro da piu' thread di esecuzione nello stesso processo*:
			Se la funzione ottiene i risultati previsti *indipendentemente dallo stato d'esecuzione di qualsiasi altro thread*.
		Una funzione e' invece detta **non rientrante** se la mutua esclusione alla funzione dev'essere assicurare tramite uso di semafori o disabilitando le interruzioni durante le sezioni critiche.
			In generale, le funzioni **non rientranti**:
				1) Invocano *malloc* e/o *free*
				2) E' noto che usano strutture dati *statiche*
				3) Sono parte della libreria *stdio*
			Le funzioni *rientranti*:
				1) *Non mantengono dati statici* in chiamate successive
				2) *Non restituiscono puntatori a dati statici*, ma sono tutti passati da chi invoca la funzione
				3) *Usano dati locali* o assicurano protezione a quelli globali *effettuandone copie locali*
				4) *Non richiamano funzioni non rientranti*
	*Segnali Affidabili*
		E' necessario prendere precauzioni all'interno della funzione di gestione del segnale, *per evitare race condition*. UNIX contiene caratteristiche che permettono di bloccare l'eventuale elaborazione dei segnali:
			*Maschera dei segnali*
				La maschera dei segnali *maschera* alcuni segnali per evitare che alcuni (a bassa priorita', oppure alcuni scelti dall'utente) arrivino a bloccare l'esecuzione del processo.
				Tipicamente i segnali possono essere messi in corrispondenza con ciascun bit di un intero. *il numero di segnali differenti che possono occorrere puo' superare il numero di bit in un intero*. POSIX definisce il tipo di dato **sigset_t** per contenere un insieme di segnali ed un insieme di funzioni per manipolarlo.
			*Interruzione e Riavvio di syscall*
				Immaginiamo di definire un handler per un certo segnale, e di effettuare una chiamata bloccante (*es read che si blocca finche' non riceve un dato input*). Mentre la syscall e' bloccata, il segnale per cui abbiamo ricevuto il gestore e' consegnato, ed e' invocato il gestore.
				**Cosa accade quando il gestore ritorna?**
				Di default, la syscall fallirebbe con errore **EINTR (*Interrupted Function)***, ma spesso preferiamo continuare l'esecuzione della syscall interrotta.
				Per fare cio', possiamo usare del codice per *riavviare una system call interrotta da un gestore di un segnale*.
				Dobbiamo comunque ricordarci che *svolgendo queste operazioni dobbiamo comunque **gestire l'errore EINTR** della syscall*.
	*Segnali per il controllo dei Job*
		*Gruppi di processi*
			Ogni processo e' membro di un *gruppo di processi*. Un gruppo di processi ha associato un identificatore **PGID** (*Process Group ID*).
			Un processo figlio eredita il PGID del padre.
			Ad ogni processo puo' essere associato un *terminale di controllo, che tipicamente e' il terminale da cui il processo viene lanciato*.
			Ad ogni terminale e' associato un *processo di controllo*:
				1) Se il terminale individua un **metacarattere**, come *Ctrl+C*, spedisce il segnale appropriato a *tutti i processi nel gruppo del suo processo di controllo*
				2) Se un processo tenta di leggere dal suo terminale, e *non e' membro del gruppo del processo di controllo di quel terminale*, riceve un segnale **SIGTTIN** che normalmente lo sospende (**SIGTTOU** se invece cerca di scriverci)
		*Gruppi e Terminale : uso nella Shell*
			All'avvio di una shell interattiva, la shell e' il processo di controllo del terminale da cui e' lanciata.
			Se la shell esegue un comando in *foreground*:
				1) La shell figlio si mette in un diverso gruppo, *assume il controllo del terminale*, ed esegue il comando
				2) Ogni segnale generato dal terminale *viene indirizzato al comando* e non alla shell originaria 
				3) Quando il comando termina, *la shell originaria riprende il controllo del terminale*.
			Se la shell esegue un comando in *background*:
				1) La shell figlio si mette in un gruppo diverso ed esegue il comando, *senza assumere il controllo del terminale*.
				2) Ogni segnale generato dal terminale *continua ad essere indirizzato alla shell originaria*
				3) Se il comando in background tenta di leggere dal suo terminale di controllo, *viene sospeso da un segnale **SIGTTIN***

-----------------------------------------------------------------------------------------
