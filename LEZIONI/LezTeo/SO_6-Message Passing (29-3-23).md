
**INTERPROCESS COMMUNICATION**
---

*Scambio Messaggi*
	I processi si scambiano messaggi tramite IPC. Lo scambio di messaggi si adatta a diverse situazioni in cui lo scambio di informazioni fra processi gioca un ruolo fondamentale.
	Uno dei suoi usi più importanti è nel modello *Client-Server*, in cui un processo **server** fornisce un servizio, e altri processi detti **client**, gli inviano messaggi per utilizzare tale servizio.

*Panoramica*
	Quando i processi interagiscono fra loro, devono farlo rispettando alcune condizioni:
	1) Devono essere sincronizzati per garantire la *mutua esclusione*
	2) Hanno bisogno di scambiarsi informazioni per *cooperare* fra loro 
	Un modo per soddisfarle entrambe è lo scambio di messaggi, che possono essere scambiati fra processi in esecuzione sullo stesso computer o fra processi su macchine diverse, connesse tramite una rete.
	Il message passing è implementato mediante le *primitive bloccanti* : **send()** e **recieve()**. Per scambiarsi messaggi, i processi devono essere in parte sincronizzati.

*Send Bloccanti e Non-Bloccanti*
	Distinguiamo una send bloccante da una non-bloccante per i seguenti motivi:
	1) Una send *bloccante* blocca il processo mittente finchè il messaggio da inviare *non viene consegnato* al destinatario
		Questo matodo di message passing prende il nome di **Scambio Sincrono** (*rendez-vous*)
	2) Una send *non-bloccante* consente al mittente di proseguire la sua esecuzione dopo la chiamata send, senza preoccuparsi dell'immediata consegna
		Questa metodologia prende il nome di **Scambio Asincrono**
	**MP Sincrono**
		Il Message Passing *Sincrono* fornisce alcune proprietà per i processi utente e semplifica le azioni del kernel.
		Un processo mittente ha la garanzia che il messaggio venga consegnato, prima di continuare la sua esecuzione.
		Il kernel consegna un messaggio immediatamente se il processo destinatario ha già effettuato una chiamata *recieve* per ricevere il messaggio; altrimenti, **blocca** il mittente finchè il destinatario non la effettua.
		L'uso del MP Sincrono (*send bloccanti*) può ritardare un processo mittente in alcune situazioni
	**MP Asincrono**
			Il message passing *Asincrono* (mediante send *non-bloccanti*), migliora la concorrenza fra mittente e destinatario, consentendo al mittente di continuare la sua esecuzione. 
			Per realizzare questa metodologia, il kernel esegue il *buffering* del messaggio:
				Quando un processo invoca la send, il kernel alloca un buffer nell'area di sistema, e copia il messaggio nel buffer. In questo modo, *il mittente è libero di accedere all'area di memoria che conteneva il testo del messaggio*.
			Tuttavia, questa organizzazione presenta due svantaggi:
			*Spreco di memoria*
				Quando molti messaggi sono in attesa di essere consegnati, rimarranno in un'area di memoria bloccata agli altri processi, riducendo così quella disponibile.
			*Spreco di CPU*
				In questa tecnica, la CPU deve copiare il messaggio nel buffer, e una volta che il destinatario invoca la recieve, deve copiare il messaggio dal buffer al destinatario

**IMCB**
	Il kernel costruisce una struttura, chiamata *Interprocess Message Control Block*, che memorizza le informazioni necessarie alla consegna del messaggio. Siccome i messaggi possono essere molteplici, nella struttura dati c'è un puntatore necessario a costruire una lista di messaggi, che serve per lo scambio

*Denominazione Diretta ed Indiretta*
	Una problematica molto importante nello scambio di messaggi è l'*identificazione* (Naming) di mittente e destinatario.
	Questo può essere fatto direttamente nella send e nella recieve, ma può anche essere omesso, ed il kernel li deduce in altro modo.
	*Indirizzamento **DIRETTO***
		Con l'indirizzamento diretto, entrambi i processi dichiarano i rispettivi nomi.
		Abbiamo due possibili metodi per farlo:
		*Nomi Simmetrici*
			I processi mittente e destinatario specificano i rispettivi *nomi*. In questo modo, un processo può decidere da quale ricevere un messaggio. Ciò è però difficoltoso quando, ad esempio, processi di due applicazioni diverse vogliono comunicare
		*Nomi Asimmetrici*
			Con questa tecnica, il destinatario non fornisce il *nome* del processo dal quale vuole ricevere un messaggio.
	*Indirizzamento **INDIRETTO***
		I processi non specificano i relativi nomi nelle istruzioni send e recieve.
		In questo caso i messaggi non viaggiano direttamente da mittente a destinatario, ma *vengono inviati ad una struttura dati condivisa* che si compone di code, che contengono contemporaneamente i messaggi. 
		Questa struttura prende il nome di **Mailbox**, e possiede le seguenti caratteristiche:
		1) Ha nome unico (*non esistono mailbox omonime*)
		2) Solo il proprietario (*tipicamente il processo che l'ha creata*) può ricevere i messaggi dalla mailbox
		3) *Ciascun processo che è a conoscenza del nome* della mailbox può inviare messaggi (al processo utente)
		Le relazioni fra mittenti e destinatari possono essere:
		*Uno a Uno*
			Esiste un ricevitore cui è assegnato un mittente (*Comunicazione Privata*)
		*Uno a Molti*
			Un mittente invia un messaggio a più destinatari (*Messaggi Broadcast*)
		*Molti a Uno*
			Utile per applicazioni di tipo *client-server*, dove si ha un solo ricevitore e un certo numero di client (*La mailbox viene chiamata **PORTA***)
		*Molti a Molti*
			Trattasi di processi server che devono servire più processi client
		L'associazione dei processi con le mailbox può essere *statica* o *dinamica*.
		Spesso una mailbox è associata staticamente ad un solo processo in particolare se la relazione fra mittente e destinatario è di tipo *uno a uno*, *molti a uno* o *uno a molti*.
		Se la relazione è *molti a molti*, si utilizzano mailbox con associazioni dinamiche, nel cui caso si usano altre primitive (*connect* e *disconnect*)
		**VANTAGGI MAILBOX**
			L'utilizzo della mailbox fornisce vari vantaggi:
			*Anonimato del Destinatario*
				Una mailbox consente al mittente di non conoscere l'identità del destinatario
			*Classificazione dei messaggi*
				Un processo può creare diverse mailbox, e usarne ciascuna per ricevere un certo tipo di messaggi

#ProdCons  *SCAMBIO MESSAGGI*
```C
//Pi                                     //Pj
begin                                    begin
	Parbegin                                Parbegin
		var buffer : ...;                       var area_messaggio : ...;
		repeat                                  repeat
			{/*Produci*/}                          recieve(Pi,area_mesaggio);
			seng(Pj,buffer);                       {/*Consuma*/}
			{/*Resto ciclo*/}                      {/*Resto ciclo*/}
		forever;                                forever;
	Parend;                                 Parend;
end;                                     end;
```
-
	Il processo Pi produce l'elemento, lo inserisce nel buffer, e poi invia il messaggio con il contenuto del buffer a Pj, che lo riceve nell'*area_messaggio*, e consuma l'elemento dato dal messaggio. La chiamata *send* blocca Pi finchè Pj non riceve il messaggio e quindi consuma l'elemento, e la chiamata *recieve* blocca Pj finchè Pi non gli invia il messaggio.
	Questa soluzione è però *restrittiva*, perchè ci obbliga ad avere un processo produttore e uno consumatore.
	Per implementare più processi, occorre usare le tecniche di sincronizzazione.

**ALTRI SISTEMI DI MESSAGE PASSING**
---
*Pipe*
	Una pipe è un meccanismo FIFO di message passing per il trasferimento di dati fra processi lettori e scrittori.
	Unix fornisce due tipi di pipe:
	*Pipe con nome*
		Corrisponde ad un elemento all'interno di una directory e quindi può essere usata da qualsiasi processo mediante la systemcall *open*. Questo tipo di pipe viene mantenuta nel sistema finchè non è rimossa attraverso *unlink*
	*Pipe Anonima*
		Non corrisponde ad alcun elemento in una directory, e *può essere usata solo dal creatore e dai suoi discendenti* nell'albero dei processi.
	Il kernel cancella una pipe anonima quando *non esistono più lettori o scrittori*. Il kernel tratta una pipe come *una coda* mantenendo *due offset*, uno usato per la lettura e uno per la scrittura. Quest'organizzazione fa sì che nessun processo possa modificare gli offset, se non mediante lettura e scrittura.
	I dati scritti nella pipe vengono inseriti mediante l'offset di scrittura che *viene incrementato del numero di byte scritti*. I dati scritti da più scrittori vengono mischiati se scritti in maniera interfogliata.
	Se una pipe è piena, *il processo che vuole scrivere viene posto in sleep*.

*Socket*
	Una socket è un canale di comunicazione. I processi client e server *creano ciascuno una socket* che saranno connesse per creare il canale di comunicazione, allo scopo di inviare e ricevere i messaggi. 
	Il server collega la sua socket ad un indirizzo *valido nel dominio in cui la socket sarà utilizzata*. A questo punto, l'indirizzo sarà reso noto nel dominio. Un processo client utilizza l'indirizzo per eseguire una *connect* tra la propria socket e quella del server.
	La socket viene creata dal processo server mediante la systemcall *socket(dominio,tipo,protocollo)*, che restituisce un identificatore di socket. Un client crea una socket e tenta di connetterla alla socket del server mediante la systemcall *connect(cs,server_socket_addr,server_socket_addrlen)*
	La comunicazione fra socket avviene mediante le systemcall *read* e *write*, oppure *send* e *recieve*.