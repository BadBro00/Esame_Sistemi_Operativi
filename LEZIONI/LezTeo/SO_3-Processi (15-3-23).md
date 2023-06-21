**Processi e Programmi**
---
*Processo:*
	Programma in esecuzione che utilizza le risorse ad esso allocate.
	Un processo è composto da sei parti:
	*ID*
		Codice identificativo univoco assegnatogli dal SO (**PID**)
	*Codice*
		Il codice sorgente del processo
	*Dati*
		L'insieme dei dati utilizzati durante l'esecuzione
	*Stack*
		L'insieme dei parametri delle function e routine utilizzate dal processo, e gli indirizzi di ritorno
	*Risorse*
		L'insieme delle risorse utilizzate durante l'esecuzione
	*Stato CPU*
		"Screenshot" dell'esecuzione, formato dall'unione di PSW e GPR

*Processo Figlio*
	Un programma in esecuzione può avere le sue istruzioni eseguite da uno o più processi. Se un programma crea altri processi durante la sua esecuzione, essi vengono detti **processi figli**.
	I processi figli sono generati dal programma tramite una *system call* ( **fork()** )
	Il SO crea il nuovo processo, imposta tutti i dati necessari per la sua esecuzione, e lo inserisce nella coda di scheduling.
	*Albero dei Processi*
		Dopo che un processo crea un figlio, si viene a generare un **Albero dei Processi**, dove padre e figli sono connessi da "rami", e tramite questi si forma una "cronologia"
	*Vantaggi*
		Uno dei benefici portati dai processi figli è il multitasking dell'applicazione, ma sostanzialmente si va a diminuire il tempo necessario all'elaborazione dato che ogni processo effettua una piccola parte del codice, risultando in un minor tempo d'attesa generale per il completamento delle istruzioni.
	I processi figli possono avere una specifica *priorità*, che indica quando dev'essere schedulato. In questo modo possiamo far svolgere alcune istruzioni prima di altre.
	Inoltre, l'uso di processi figli salvaguardia il padre da errori o fallimenti, perchè terminando il figlio non si va a toccare il padre, che può recuperare lo stato del figlio ma continuerà la sua esecuzione.

*Stato di un processo e Transizioni*
	Un processo può avere diversi *stati*, di cui quattro sono i principali:
	*Ready*
		Il processo è pronto all'esecuzione, è inserito nella coda del dispatcher, e "attende" il suo turno
	*Blocked*
		Il processo è in attesa di un evento, come l'allocazione di una risorsa
	*Running*
		Il processo è in esecuzione
	*Terminated*
		Il processo ha terminato la sua esecuzione (*in modo normale o anormale*)
	Inoltre, abbiamo altri stati per definire le operazioni di **Swap** da parte del SO:
	**Swapping programmi**
		Lo swapping è una tecnica tramite la quale il SO riesce a tenere in memoria diversi processi, oppure ad eseguire istruzioni aventi indirizzi molto distanti. Consiste nel tenere in memoria (*centrale*) solo le istruzioni **necessarie al funzionamento**, mentre quelle che non servono vengono appunto *swappate* nel disco con altre. Avendo memoria (centrale) limitata, il sistema deve mantenere solamente i programmi e le istruzioni necessarie al funzionamento, quindi quando le istruzioni o i processi non devono necessariamente essere più in memoria, effettua operazioni di *swap-out*, mentre per prendere istruzioni o processi che devono essere eseguiti effettua operazioni di *swap-in*. Questo avviene soprattutto quando un processo è schedulato oppure prelazionato.
		*Swap-in*
			Operazione grazie alla quale il SO porta in memoria *centrale* un processo (o un'istruzione) dal disco
		*Swap-out*
			Operazione grazie alla quale il SO porta nel disco dalla memoria *cenrale* un processo (o un'istruzione)
	Grazie a queste, abbiamo gli stati aggiuntivi:
	*Swapped-Ready*
		Il processo swappato era nello stato Ready prima dello swap. Quando verrà riportato in memoria, verrà aggiunto alla coda dei processi *ready*
	*Swapped-Blocked*
		Il processo era nello stato *Blocked* al momento dello swap. Quando verrà riportato in memoria, dovrà attendere fino a che la condizione di blocco non verrà risolta.

*Contesto del processo e Process Control Block*
	Il contesto del processo racchiude *tutte* le informazioni necessarie per l'esecuzione (e il suo controllo) da parte del SO.
	Il contesto del processo è affiancato dal **PCB**, che contiene informazioni specifiche sul processo stesso.
	*Process Context*
		Il contesto contiene informazioni sullo stato del processo:
		*Memory Info*
			Informazioni sulla memoria allocata al processo
		*Resource Info*
			Informazioni sulle risorse allocate
		*File Pointers*
			Informazioni relative ai file usati dal processo
		*Code*
			Codice del processo
		*Data*
			Dati usati nell'esecuzione
		*Stack*
			Stack del processo
	*Process Control Block*
		Il PCB contiene informazioni sull'esecuzione e sul processo stesso:
		*PID*
			Identificativo del processo
		*Stato del processo*
			Informazione sullo stato *attuale* del processo
		*GPR*
			Contenuto del GPR, utile per l'esecuzione
		*PC value*
			Contiene l'indirizzo della prossima istruzione del processo

*Concorrenza e Parallelismo*
	*Parallelismo*
		Esecuzione di più programmi in contemporanea: Possibile solo con più CPU/core
	*Concorrenza*
		Esecuzione di più programmi quasi simultaneamente su una macchina monoprocessore, gestita da Context Switch e Scheduling (*Round Robin*)

*Commutazione di Processi*
	L'overhead della commutazione è douto alla dimensione delle informazioni sullo stato del processo.
	Alcune architetture forniscono istruzioni speciali per semplificare queste commutazioni.
	L'occorrenza di un evento *non sempre è seguita da una commutazione*.
	La commutazione è anche dovuta a volte dall'esaurimento del tempo massimo assegnabile della CPU al processo (*time slice*)

**EVENTI** E SEGNALI
---

*Tipi di Eventi*
	Gli eventi che si possono verificare durante l'esecuzione del SO sono di diversi tipi:
	*Timer*
		Interrupt *a tempo* (ad esempio il trascorrere della *time slice* o dovuta ad una *system call*)
	*I/O*
		Interrupt dovuto ad un'operazione di I/O (*iniziata o terminata*)
	*Memory*
		Interrupt dovuto all'accesso di un'area di memoria *non allocata al processo*
	*Risorse*
		Interrupt dovuto all'assegnazione di risorse da parte del SO
	*Process*
		Dovuto alla creazione (o terminazione) di un processo
		**Creazione**
			Dovuto ad una system call -> *Interrupt Software*
			La routine crea un nuovo *PCB*, assegna un ID univoco e una priorità al nuovo processo, inserisce tali info nel PCB insieme al PPID (*parent process ID*), determina la quantità di memoria da allocare per lo spazio d'indirizzamento del processo, e dispone il tutto per l'allocazione
			Eventualmente, dal kernel sono associate al processo risorse standard (*Canali di I/O std*)
			Inserisce le informazioni sulla memoria e sulle risorse nel contesto del nuovo processo, e imposta il processo a *Ready* nel PCB e lo immette in una lista di PCB (*lista processi ready*)
		**Terminazione**
			Dovuto ad una system call -> *Interrupt Software*
			Quando un processo invoca una system call per la terminazione di se stesso o di un figlio, il kernel ritarda la terminazione effettiva fino al momento in cui le operazioni di I/O avviate dal processo non terminano, rilascia la memoria e risorse allocate (*sulla base del contesto*), lo stato del processo è posto a *Terminated*, e il PCB del processo non viene rimosso finchè il padre non ne preleva lo stato di terminazione. (*Il processo è ora nello "stato" **ZOMBIE***)
			Il kernel prende l'id del padre dal PCB del figlio e controlla il campo *info evento* del PCB del padre per verificare se il padre era in attesa della terminazione del figlio, e viene notificato tramite segnale (*sincrono*), oppure tramite una *system call* ( **wait()** ) eseguita dal padre.
			Solo adesso, o nel caso in cui il padre *non fosse in attesa della terminazione*, il suo PCB viene effettivamente rimosso dalla lista, e quindi il processo è terminato definitivamente.
	*Message Passing*
		Dovuto all'invio o ricezione di **messaggi**
	*Signal*
		Dovuto all'invio o ricezione di **segnali**
	*HW*
		Dovuto a malfunzionamenti HW
	*SW*
		Dovuto a richieste di un processo, oppure ad eccezioni da parte di programmi
	Il SO al verificarsi di un evento effettua diverse operazioni:
	**Context Save**
		Salva il contesto del processo, e lo stato della CPU
	**Event Handling**
		Gestione dell'evento, da una *Interrupt Service Routine* e un *Handler*
	**Scheduling**
		Decisione di quale processo dev'essere eseguito (*Scheduler*)
	**Dispatching**
		Esecuzione di un processo (*Dispatcher*)

*Event Control Block*
	Al verificarsi di un evento, il SO deve trovare il processo influenzato (*anche dall'interrupt*).
	Per rendere questa ricerca meno costosa e più efficiente, il SO usa un **ECB**, che contiene tre campi:
	*Descrizione Evento*
		Contiene una "descrizione" dell'evento che si è generato (*Codice*)
	*ID Processo*
		Mantiene il **PID** del processo che ha subito l'interrupt
	*Puntatore ECB*
		Puntatore al prossimo ECB nella lista
	Vi sono due azioni che possono accadere dovute alla gestione dell'evento:
	**Block**
		Azione che modifica lo stato di un processo in *Blocked*
	**Unblock**
		Azione che cerca un processo la cui richiesta è *feasible*, e cambia il suo stato in *Ready*
	Ciascuna di queste può essere seguita da *Dispatch* o *Schedule*
		*Richiesta risorsa*
			Una systemcall per la richiesta di una risorsa *implica un'azione di **Block*** se la richiesta non può essere subito garantita, altrimenti il processo viene direttamente sottoposto a *Dispatching*
		*Rilascio Risorsa*
			Al rilascio di una risorsa da parte di un processo, *viene eseguita un'azione di **Unblock*** se un altro processo era in attesa della risorsa, poichè quest ultimo può avere *priorità maggiore*. Anche in questo caso, lo scheduling non viene effettuato se nessun processo è stato bloccato in conseguenza dell'evento.

*Segnali*
	Un segnale è utilizzato per notificare una situazione *di eccezione* ad un processo e dunque consentirgli di gestirla immediatamente.
	Alcuni esempi sono
		*Overflow/Underflow*
		*Condizioni Processi Figli*
		*Utilizzo risorse*
		*Comunicazioni d'emergenza Utente-Processo*
	Alcuni tipi di segnali possono essere inviati *dai processi utente*. 
	*Sincroni e Asincroni*
		Un segnale inviato ad un processo a causa di una condizione nel suo funzionamento è detto **Sincrono**, mentre quello inviato per altre cause è detto **Asincrono**
	Per utilizzare i segnali, un processo effettua una *system call* ( **kill()** o **raise()** ), specificando una routine da eseguire (*signal handler*), ma può ometterla, facendo utilizzare *l'handler di default*, che effettua operazioni di default (*ad esempio la terminazione del processo*)
	La gestione del segnale nel processo è implementata allo stesso modo della gestione degli interrupt.

