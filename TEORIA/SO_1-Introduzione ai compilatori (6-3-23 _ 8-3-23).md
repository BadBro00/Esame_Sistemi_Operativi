https://help.obsidian.md/How+to/Format+your+notes
----------------------------------------------------------------------
**I) SO, Computer e Programmi Utente**
---
*Kernel*
	Il kernel e' il cuore del SO, un insieme di routine che costituiscono il nucleo del SO. Implementa le funzioni di controllo, fornisce un insieme di servizi per i programmi utente, e si trova in memoria durante il funzionamento del SO.
	Il kernel deve assicurarsi che non vi siano **interferenze** fra i programmi utente e fra programmi utente e SO.
	Il kernel funziona ad *Interrupt*, che dirottano la CPU verso routine di gestione degli stessi.

*CPU*
	La CPU ha due modalita' operative:
	*Modalita' Kernel*
		La CPU puo' eseguire tutte le istruzioni, comprese quelle **privilegiate** (*systemcall*)
		Il kernel opera con la CPU in tale modalita' per controllare tutte le operazioni
	*Modalita' Utente*
		La CPU esegue i programmi utente e non puo' eseguire istruzioni che interferiscano con altri programmi o con il SO.
	*Registri*
		La CPU ha bisogno di registri per mantenere dati ed informazioni sull'esecuzione dei vari processi ed istruzioni. I due registri sono:
		*General Purpouse Registers*
			Detti anche "**Registri accessibili ai programmatori**", mantengono dati, indirizzi, valori o stack pointer, durante l'esecuzione di un programma
		*Program Status Word*
			Insieme di registri **di controllo**, che forniscono informazioni sullo stato della CPU e che ne influenzano le operazioni.
			E' formato da vari campi:
			**Program Counter**
				Contiene l'indirizzo della prossima istruzione
			**Condition Code**
				Indica alcune caratteristiche del risultato di un'istruzione aritmetica, viene usato nell'istruzione di *salto condizionato*
			**Mode**
				Indica la modalita' d'uso della CPU: 0 per Kernel, 1 per Utente
			**Memory Protection Information**
				Contiene informazioni relative alla protezione della memoria, e quanta memoria necessiti il programma in esecuzione, tramite due campi (*registro base e registro limite*)
			**Interrupt Mask**
				Definisce una "*maschera*", che blocca alcuni interrupt. E' definibile a *bit*, oppure a *valore* (di priorita')
			**Interrupt Code**
				Descrive la condizione o l'evento che ha causato l'ultimo interrupt. E' usato dalle routine di gestione
		Tutte le informazioni riguardo la CPU sono dunque contenute in quello che viene chiamato "**Stato della CPU**", ovvero l'unione fra le informazioni del PSW e dei GPR.

Per usare i dati, la CPU utilizza diversi tipi di **memoria**
	*Memoria Centrale* (**RAM**)
		La memoria centrale e' quella che si interfaccia direttamente con la CPU. Essa possiede buona capienza, con un buon compresso di velocita'. In essa vengono conservati i dati utili (anche successivamente) per le operazioni, e i processi in esecuzione.
	*Memoria Cache*
		La memoria Cache si trova in varie parti dell'architettura, ed e' divisa in tre livelli:
		*Cache L1*
			Si trova all'interno del processore, e' la piu' rapida fra tutte le memorie, ed e' quella che viene utilizzata dalla CPU
		*Cache L2*
			E' la seconda per distanza dalla CPU. Viene acceduta solo se i dati non vengono trovati nella L1. Nella maggior parte dei casi, e' saldata vicino al socket sulla motherboard.
		*Cache L3*
			E' la cache piu' distante dal processore, serve principalmente a mantenere informazioni come i comandi del processore e i dati piu' frequentemente usati, per evitare bottleneck fra CPU e RAM.
	*Disco*
		Il disco e' l'unita' di memoria piu' capiente. Esso contiene **tutte** le informazioni del computer, ed e' la piu' lenta. Con il termine "disco", si intende *tutta la restante parte della memoria*, esclusa Cache e RAM.
	Il tempo effettivo di accesso in memoria da parte della CPU e' indicato dalla seguente equazione:
	$T_{ema} = h * T_{cache} + (1-h)*(T_{tra}+T_{cache}) = T_{cache}+(1-h)*T_{tra}$
	Dove:
	$T_{ema} = Time \ of \ Estimated \ Memory \ Access$
	$T_{Tra} = Time \ of \ Transport$
	$T_{cache} = Time \ of \ Cache \ Access$
	*Protezione Memoria*
		La Protezione della memoria e' implementata controllando se un indirizzo di memoria al quale un processo vuole accedere e' all'interno dell'intervallo ad esso assegnatogli:
		$base + limite - 1$
		Con 
		*base* 
			Il registro da cui iniziano le istruzioni del programma
		*limite*
			Il registro al quale terminano le istruzioni del programma
		Se un processo tenta di accedere ad un'area oltre quella prestabilita, viene generato un interrupt (*Violazione di accesso alla memoria*)
	*Protezione Cache*
		La protezione cache utilizza il metodo che memorizza l'identificativo del programma le cui istruzioni o dati sono caricati in un blocco della cache, e solo a quel punto al programma e' consentito l'accesso al contenuto del blocco. Quando il programma genera un indirizzo logico contenuto in un blocco della cache, si verifica un hit solo se l'identificativo del programma coincide con l'identificativo del blocco

*Memory Management Unit*
	La MMU e' un dispositivo HW che aiuta il computer a simulare una memoria maggiore di quella realmente disponibile, commutando indirizzi logici in fisici, tramite alcune tecniche come la **paginazione**

*I/O e DMA*
	Nei moderni computer, il sistema di Input/Output e' affidato ad un componente detto **Direct Memory Access**, che e' *un microprocessore separato dalla CPU*, che gestisce le operazioni di I/O escludendo la CPU. Questo fa si che la CPU non venga interrotta dall'esecuzione di processi o istruzioni, consentendone quindi un uso piu' *efficiente*
	Le operazioni di I/O possono essere di tre tipi:
	1) *I/O Programmato*
		Il trasferimento di dati fra la periferica di I/O e la memoria avviene attraverso la CPU, che *non puo' eseguire alcun'altra istruzione durante il trasferimento*
	2) *I/O Interrupt*
		Dove la CPU e' libera di eseguire altre istruzioni dopo quelle di I/O. Un interrupt viene generato quando i dati devono essere trasferiti, e la CPU esegue la *routine di servizio dell'interrupt* che gestisce il trasferimento dei byte.
	3) *I/O con DMA*
		In questa tipologia, il trasferimento di dati avviene direttamente sul bus principale. **La CPU *non e' coinvolta* nel trasferimento**, ed il controller DMA *genera un interrupt* quando il trasferimento e' terminato.

*Interrupt*
	Gli interrupt sono **segnali**, inviati da un processo al sistema operativo, che definiscono una risorsa fatta a quest ultimo, come ad esempio la richiesta di una risorsa.
	Alla ricezione dell'interrupt, il SO salva lo stato della CPU, carica i nuovi contenuti nel GPR e PSW nei quali la CPU esegue le istruzioni di una routine di gestione (*ISR*)
	*Priorita'*
		Ad ogni interrupt e' assegnata una priorita', che definisce una "coda" di importanza, e la CPU servira' sempre l'interrupt a priorita' piu' elevata.
	*Classi di Interrupt*
		Vi sono diversi tipi di interrupt:
		*I/O*
			Fine di un'operazione, o verificarsi di condizioni o malfunzionamento
		*Timer*
			Interrupt generato dalla scadenza di un timer
		*Program*
			1) *Se generato dall'HW*, indica il verificarsi di una condizione (Over/Under flow, violazione di protezione,...)
			2) *Se generato da un programma utente*, e' una richiesta di servizi (processi figli, risorse,...)
	Il gestore di interrupt si compone di tre passi:
	*Impostare il codice* : 
		Imposta il codice dell'interrupt nel campo **IC** del PSW in base alla causa che l'ha generato. In questo modo il SO sa quale routine richiamare
	*Salvare il PSW* :
		Effettua il salvataggio dello stato della CPU, per poter riprenderne l'utilizzo nello stato in cui si trovava al momento dell'interrupt
	*Caricamento vettore interrupt*
		Carica il vettore di interrupt, trova la routine appropriata, e la richiama per farne eseguire le istruzioni.
		Nel vettore di gestione interrupt vi sono diversi vettori di interrupt : in base alla classe si accede al vettore corrispondente, e si richiama la routine appropriata, e si caricano le informazioni dal vettore nei campi PC,IM ed M.