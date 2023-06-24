
-----------------------------------------------------------------------------------------

**INTER-PROCESS COMMUNICATION**
---

*Differenza Segnalazione azioni e Scambio dati*
	La gestione della sincronizzazione in UNIX riguarda due aspetti : Lo *scambio di dati* e la *segnalazione di azioni*.
	Lo scambio di dati avviene attraverso:
		1) *PIPE* : Operazioni di I/O su code FIFO, *sincronizzate dal SO*
		2) *Messaggi* : Invio e ricezione di messaggi tipizzati *su coda FIFO*
		3) *Memoria Condivisa* : Allocata e rilasciata tramite SystemCall
	La segnalazione di azioni avviene attraverso:
		1) *Segnali* : Ovvero Interrupt *SW*
		2) *Semafori* : Una generalizzazione dei classici semafori.
	L'IPC tratta di meccanismi che permettono la comunicazione fra due o piu' processi e lo scambio di informazioni. I processi che possono comunicare possono trovarsi:
		Sulla stessa macchina (*Segnali, Pipe, FIFO, Socket*)
		Su macchine diverse (*Socket*)
	La comunicazione puo' essere finalizzata a:
		*Cooperazione*
			I processi scambiano dati *per ottenere un risultato comune*
		*Sincronizzazione* 
			Lo scambio di informazione permette a processi indipendenti ma *correlati* di schedulare correttamente la propria attivita'
	**PIPE ANONIME**
		Il termine pipe e' utilizzato per indicare situazioni in cui si connette un *flusso di dati da un processo ad un altro*. Le pipe sono implementate in UNIX per *connettere l'output di un comando/processo all'input di un altro*.
		```
		$ cmd1 | cmd2
		```
		Le pipe *anonime* sono presenti in tutte le versioni di UNIX.
		Le pipe *con nome* (dette **FIFO**) invece sono presenti in SystemV, e BSD per compatibilita').
		Una pipe *anonima* e' un canale di comunicazione, mantenuto a *livello kernel*, che unisce due processi. E' *unidirezionale* e permette comunicazione solo fra *processi con un antenato in comune*.
		Una pipe presenta *due lati di accesso*, in e out, associati ciascun ad un *file descriptor*. Memorizza il suo input in un buffer, tipicamente di dimensione ~4KB. Quando un processo ha terminato di usarla, chiude la pipe.
		Il flusso di dati *avviene in modalita' Half-Duplex*, cioe' in una singola direzione. La pipe e' *subordinata all'organizzazione gerarchica dei processi*, ovvero che l*unico modo che due processi hanno per comunicare e' che un eventuale antenato in comune abbia predisposto una pipe per questo fine*.
		Ogni volta che si digita una sequenza di comandi in una pipeline da eseguire nella shell, *la shell stessa crea un processo separato per ciascun comando, e unisce l'output di uno all'input dell'altro*.
		**LETTURA**
			Se un processo legge da una pipe:
				1) Se il lato *scrittura* e' stato chiuso, la ```read``` restituisce 0, indicando la fine dell'input.
				2) Se la pipe *e' vuota*, ma il lato di scrittura e' ancora aperto, la ```read``` si sospende *finche' non ci sono input*
				3) Se il processo *tenta di leggere piu' byte* di quelli presenti nel buffer, i byte disponibili vengono letti, e la ```read``` restituisce il numero di byte letti.
		**SCRITTURA**
			Se un processo scrive su una pipe:
				1) Se il lato di lettura e' chiuso, ```write``` fallisce ritornando -1, ed allo scrittore e' inviato un segnale **SIGPIPE**, con errno impostato a **EPIPE**
				2) Se si scrivono *meno byte* di quelli massimi, la ```write``` e' eseguita in modo *atomico*.
				3) Se si scrivono *piu' byte* di quelli massimi, *non c'e' garanzia di atomicita'*.
		*Comunicazione tramite Pipe*
			Quando un processo scrittore *invia diversi messaggi*, di lunghezza variabile, occorre fissare *un protocollo di comunicazione*, che permetta al lettore di individuare la fine *di ogni messaggio*.
			Alcune possibilita' sono:
				1) Inviare *la lunghezza del messaggio*, prima del messaggio stesso
				2) Terminare un messaggio *con un carattere speciale* (```\0, \n```).
		*Pipe ed exec()*
			I due processi comunicanti devono conoscere i descrittori della pipeline. Finora si e' sfruttato lo sdoppiamento delle variabili locali, e che un figlio erediti la tabella dei descrittori del padre.
			Una ```exec``` non altera la tavola dei descrittori, anche se si perde lo spazio di memoria ereditato dal padre prima dell'exec.
			Supponendo di voler implementare la pipeline ```$ ls | wc -w```:
				1) Il padre esegue ```fork()```
				2) Il padre esegue ```exec('ls')```
				3) Il figlio esegue ```exec('wc -w')```
	**FIFO**
		Scambiare soltanto dati fra processi legati fra loro e' una limitazione, poiche' talvolta e' necessario che processi *non in relazione fra loro* siano in grado di scambiarsi dati.
		Questo e' possibile tramite le *FIFO*, pipe che possono connettere due (*o piu'*) processi qualsiasi. La FIFO infatti e' *un tipo speciale di file*, che si comporta come una pipe senza nome.
		*Creazione*
			Le fifo vengono create tramite ```mkfifo```, che implica le macro *O_CREAT|O_EXCL*, che quindi restituisce errore *EEXIST* se la FIFO esiste nel sistema.
			Se non e' desiderata la creazione di una nuova FIFO, e' necessaria ```open``` anziche' ```mkfifo```
		*Accesso*
			Una caratteristica utile delle pipe con nome e' che *risiedono nel FS*, per cui possiamo usarle in comandi in cui *usiamo path/nomi di file*.
			Ad esempio, possiamo usare ```cat < /tmp/myfifo``` per leggere, o ```echo "ciao" > myfifo```
		*Comunicazione Client-Server*
			Un utilizzo delle FIFO consiste nell'*inviare dati fra Client e Server*. Se abbiamo un server contattato da numerosi client, ogni client puo' inviare la sua richiesta ad una FIFO *creata dal server*.
			Poiche' possono esserci scrittori multipli per la FIFO, *le richieste inviate al server devono sempre essere minori di PIPE_BUF*.
	**SOCKET**
		Due o piu' processi *sullo stesso host* comunicano usando una qualche forma di IPC, definita dal SO.
		Due o piu' processi, *su differenti host*, connessi ad una rete, comunicano scambiandosi messaggi.
		*Architettura Client-Server*
			Nei sistemi operativi moderni, i servizi disponibili in rete si basano principalmente sul modello Client-Server. Tale architettura consente ai sistemi di condividere risorse e cooperare per il raggiungimento di un obiettivo.
				*Server* : Host sempre attivo, con IP fisso
				*Client* : 
					Comunica con il server
					Puo' farlo in qualunque momento
					Puo' avere *IP dinamici*
					*Non comunica direttamente con gli altri client*
			Un processo invia o riceve messaggi alla o dalla sua socket, visibile come un *varco*:
				Un processo che vuole inviare un messaggio, lo fa *uscire* dal suo varco
				Il processo *presuppone l'esistenza di un'infrastruttura esterna* che trasportera' il suo messaggio fino al varco del destinatario.
			Affinche' un host invii il suo messaggio ad un altro, il mittente deve *identificare il destinatario*. E' sufficiente conoscere l'IP dell'host su cui e' in esecuzione il processo per identificare il processo stesso? **NO**:
				Su un host sono in esecuzione molteplici processi
				*Bisogna identificare l'host attraverso l'IP*, e il processo mediante i *numeri di porta*, che sono associati ai processi in esecuzione.
				**ESEMPIO**:
					Non basta conoscere l'IP *127.0.0.1*, ma ci servira' anche il numero di porta *0*, formando quindi un indirizzo completo *127.0.0.1:0*.
		*Servizi del protocollo di trasporto*
			Esistono due principali protocolli di trasporto:
				**TCP** (*Transfer Control Protocol*)
					Orientato alla connessione : *E' richiesto un setup fra Client e Server*
					*Trasporto affidabile* fra mittente e destinatario
					*Controllo del flusso* : Il mittente non vuole *sovraccaricare* il destinatario
					*Controllo congestione* : *Strozza* il mittente quando la rete e' sovraccaricata
				**UDP** (*User Datagram Protocol*)
					*Trasferimento Inaffidabile* fra mittente e destinatario
					Non offre i servizi del TCP, ma utile per quando non e' richiesto un servizio affidabile (es chiamate)
		*Programmazione tramite Socket*
			Le applicazioni di rete consistono di una coppia di programmi, che risiedono su host differenti. Quando questi vengono eseguiti, si crea un processo Client e un processo Server, che comunicano tramite *Socket*. 
			*Programmazione Socket TCP*
				Il client deve *contattare* il server:
					Il processo server *dev'essere in esecuzione*
					Il server *deve aver creato una socket* per essere contattato
				Il client *contatta* il server:
					*Creando una socket TCP*
					Specificando IP e numero di porta del server
					Alla creazione della Socket, il client TCP *stabilisce una connessione con il server*
				Quando viene contattato dal Client, il Server TCP *crea una nuova socket* per comunicare con il Client:
					Cio' consente al Server *di comunicare con diversi Client*
					I numeri di porta *origine* vengono usati per distinguere i client
			*Programmazione Socket UDP*
				Non vi e' *connessione* fra client e server:
					*Non c'e' Handshake*
					Il mittente allega *esplicitamente* IP e porta di destinazione ad ogni pacchetto
					Il server *deve estrarre* l'IP e la porta del mittente dal pacchetto ricevuto
					I dati trasmessi *possono perdersi*, o arrivare *in un ordine diverso*
		Le socket sono create nell'ambito di un *dominio* di comunicazione che determina:
			1) Il *metodo per identificare* una Socket (**formato di un indirizzo**)
			2) Il *range della comunicazione* della Socket (**Stesso host o host diversi**)
		I due modi principali per comunicare in rete sono:
			*Connection Oriented Model*
			*Connectionless Oriented Model*
		In corrispondenza dei due paradigmi, abbiamo i seguenti tipi di Socket:
			*Stream Socket* : 
				Forniscono stream di dati *affidabili*, duplex, ordinati
				Nel dominio Internet sono supportati dal *TCP*
			*Datagram Socket* :
				Trasferiscono messaggi di dimensione *variabile*
				Preservano i confini ma non l'*ordine* o l'*arrivo*
				Supportate nel dominio Internet dall'*UDP*
		*Connessioni Socket TCP*
			Un'applicazione server crea una Socket che e' *una risorsa associata univocamente al processo Server*.
			Il processo Server *assegna un nome alla Socket*:
				Per le socket *locali* si usa il filename
				Per le socket *di rete* il nome corrisponde ad un *identificatore di servizio*, come il *numero di porta* o il *punto di accesso*, rilevanti per la particolare rete cui i Client possono connettersi.
			L'identificatore consente al SO di *instradare le connessioni in arrivo* specificando un nome particolare di porta, al corretto processo Server. Tale nome e' assegnato tramite ```bind```. Il processo Server aspetta poi che un Client si connetta alla Socket, tramite ```listen```, e accetta la connessione tramite ```accept```.
			All'esecuzione di ```accept```, viene creata una nuova socket, *distinta da quella dotata di nome*:
				Questa socket viene usata *unicamente per parlare con il Client specifico*
				