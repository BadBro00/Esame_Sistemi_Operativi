**STALLI**
---
*Deadlock*
	Un deadlock è una situazione in cui *un insieme di processi attende indefinitivamente degli eventi*.
	Un deadlock pregiudica il servizio utente, il throughput e l'efficienza delle risorse.
	Un deadlock si verifica quando due o più processi si bloccano a vicenda, attendendo che uno esegua una certa azione che serve all'altro e viceversa. Ogni processo è dunque in attesa di un evento *che potrebbe non verificarsi mai*
	In un SO, i deadlock possono essere di vario tipo, come
	*Deadlock generato da risorse*
		Un processo rimane in attesa di una risorsa *bloccata* da un altro processo.
	*Deadlock di sincronizzazione*
		Un processo rimane in attesa di un'operazione di un altro processo, che però *non la effettua*
	*Deadlock di comunicazione*
		Un processo rimane in attesa di un messaggio da parte di un altro processo, che però *non lo invia*

*Risoluzione*
	Solitamente, un SO dovrebbe principalmente risolvere i *Deadlock di Risorse*, in quanto l'allocazione delle risorse è una responsabilità del SO.
	Un SO gestisce numerose risorse di tipo diverso, che vengono usate dai processi. Le risorse possono essere sia HW che SW.
	Usiamo il termine
	*Unità di risorsa*
		Per definire una risorsa di un certo tipo
	*Classe di risorse*
		Per indicare l'insieme di tutte le risorse di quel tipo
	Per la gestione delle risorse, il kernel gestisce una **Tabella delle Risorse**, per tenere traccia dello stato di allocazione di ciascun'unità di risorsa.
	Quando un processo *richiede* una risorsa, bisogna verificare se essa è *allocata* o meno ad un altro processo:
	*Se risulta allocata*
		Il processo che la richiede diventa *Blocked*
	*Se risulta libera*
		Il processo *acquisisce* la risorsa, e il processo va nello stato *Ready*
	Per poter utilizzare una risorsa, è necessaria la seguente sequenza di eventi:
	1) *Richiesta* della risorsa
	2) *Allocazione* della risorsa
	3) *Rilascio* della risorsa

*Deadlock di Risorsa*
	Un deadlock dovuto alle risorse si verifica quando queste quattro condizioni si verificano allo stesso istante:
	*Condizione di mutua esclusione*
		Almeno una delle risorse del sistema dev'essere **non condivisibile** (libera o utilizzata da un processo a volta)
	*Condizione di possesso e attesa*
		Un processo continua a tenere la risorsa, ma *al contempo è in attesa di altre risorse* per completare le operazioni
	*Condizione di assenza di prelazione*
		Una risorsa allocata ad un processo non può essere rimossa in modo forzato da questo processo per essere assegnata ad un altro
	*Condizione di attesa circolare*
		Esiste nel sistema una catena circolare dei processi, ognuno dei quali aspetta il rilascio di una risorsa da parte del processo che lo segue
	E' **essenziale** anche un'altra condizione: *Nessun annullamento di richieste di risorse*
		Un processo bloccato su una richesta di una risorsa non può annullarla
	Per stabilire se un insieme di processi è in *deadlock*, è necessario **analizzare lo stato di allocazione delle risorse di un sistema**. Per rappresentarlo, si usano due tipi di modelli : il modello basato su *grafo*, o il modello basato su *matrice*

**MODELLI**
---
**Modello basato su Grafo**
	*RRAG*
		![[Pasted image 20230403112739.png]]
		Un *grafo di richiesta risorse* (**RRAG**) contiene due tipi di nodi:
		*Nodi processi*
			Indicano un processo, e sono rappresentati da cerchi
		*Nodi risorsa*
			Indicano una *classe* di risorsa, e sono rappresentati da rettangoli al cui interno il numero di punti indica *il numero di unità di risorsa di quella classe*.
		Per collegare i nodi risorsa ed i nodi processo si usano archi che possono essere di due tipi:
		*Arco di Allocazione*
			Diretto da un nodo risorsa ad un nodo processo, indica che la risorsa è allocata al processo
		*Arco di Richiesta*
			Diretto da un nodo processo ad un nodo risorsa, indica che il processo è bloccato sulla richiesta della risorsa
	*WFG*
		Un *grafo di attesa* (**WFG**) viene usato quando una classe di risorsa *contiene una sola unità di risorsa*
		Il WFG contiene un solo tipo di nodi, detti *nodi processo*. Un arco nel WFG rappresenta il fatto che $P_i$ ha richiesto una risorsa attualmente allocata a $P_j$, ovvero che *$P_i$ *sta attendendo che il processo $P_j$ rilasci la risorsa*
		![[Pasted image 20230403112756.png]]
		In base al numero di risorse, se un grafo contiene *cicli*, **può** verificarsi un deadlock
		Un *cammino* è una sequenza di archi tale che il nodo di destinazione di un arco è il nodo sorgente dell'arco seguente
	**Non può esistere un deadlock se RRAG o WFG non contengono cicli, ma se ne contengono non è detto che vi sia un deadlock** 

**Modello basato su Matrice**
	Nel modello basato su matrice, lo stato di allocazione di un sistema è rappresentato da *due matrici*
	*Matrice Risorse Allocate* (**R_A**)
		Indica quante *unità di risorsa di ciascuna classe* sono allocate *a ciascun processo*
	*Matrice Risorse Richieste*
		Tiene conto delle richieste in attesa, e indica *quante unità di risorsa di ciascuna classe* sono state richieste da *ogni processo* del sistema
	In questo caso, vengono utilizzate anche tabelle ausiliarie per rappresentare informazioni aggiuntive (*Risorse massime allocabili*, *Risorse Totali*)
	![[Pasted image 20230403113237.png]]

**GESTIONE DEADLOCK**
---
*Approcci*
	Per trattare adeguatamente le situazioni di *stallo*, si possono impiegare tre approcci diversi
	*Rilevamento e Risoluzione*
		Il kernel analizza lo stato della risorsa per definire *se esiste* un deadlock. Se è così, *interrompe alcuni processi*, e assegna le risorse allocate ad altri processi affinchè il deadlock cessi di esistere. I processi interrotti vengono poi eseguiti in seguito. 
		Il costo di questo approccio comprende sia il costo dell'individuazione, sia il costo della riesecuzione
	*Prevenzione*
		Il kernel usa una politica di *allocazione* delle risorse che assicura che le quattro condizioni per il verificarsi dei deadlock non si verifichino mai *simultaneamente*. Ciò rende **impossibili** i deadlock
	*Evitare i deadlock*
		Il kernel analizza lo stato di allocazione per determinare se l'accettazione di una richiesta di risorsa *può generare un deadlock*. Vengono accettate **solo le richieste che non conducono a deadlock**, mentre le altre *vengono tenute in attesa finchè possono essere accettate*. Questo metodo rende impossibili i deadlock.

*Individuazione e Risoluzione*
	Questo approccio permette i deadlock, per poi provare a scoprire quando ciò accade e provare a risolvere la situazione dopo che si è verificata. Il sistema deve quindi fornire:
	*Un algoritmo*
		Che esamini lo stato del sistema per stabilire se si è verificato un deadlock
	*Una tecnica*
		Per permettere al sistema di ricominciare a funzionare
	L'algoritmo di individuazione dei deadlock prova a cercare una sequenza di eventi ammissibili dove tutti i processi bloccati possono sbloccarsi ed ottenere le risorse, e se una sequenza di tale tipo non esiste, c'è un deadlock
	*Risoluzione*
		Supponiamo che siano stati individuati dei deadlock nel sistema. A questo punto, è necessaria una tecnica che permetta al sistema di ritornare a funzionare. Una delle tecniche più utilizzate è quella *della risoluzione dei deadlock mediante prelazione*. 
		Ciò può essere realizzato interrompendo uno o più processi, allocando le loro risorse ad altri processi in modo che possano completare le loro esecuzioni.
		Ogni processo interrotto è detto *vittima della risoluzione*, e la scelta delle vittime viene fatta tramite vari criteri, fra cui la *priorità*, le risorse già usate...
		![[Pasted image 20230403114326.png]]

*Caratterizzazione deadlock mediante i Grafi*
	La caratterizzazione dei deadlock è una dichiarazione delle caratteristiche essenziali di un deadlock.
	Tra le condizioni necessarie per un deadlock c'è anche l'*attesa circolare*, che si manifesta in un **ciclo** dei modelli a grafo.
	*Sistemi Singola Istanza*
		In un sistema a singola istanza, ogni classe di risorsa ne contiene una singola istanza. Un ciclo è una condizione **necessaria e sufficiente** affinchè esista un deadlock.
	*Sistemi Istanza Multipla*
		In questi sistemi, un ciclo *non è una condizione **sufficiente*** per il verificarsi di un deadlock, perchè le classi di risorsa possono contenere più istanze. Affinchè un processo sia in deadlock, è necessario che *tutti i processi che contengono un'unità di una risorsa da esso richiesto siano anch'essi in deadlock*, ovvero che **tutte le istanze siano già assegnate a dei processi**

*Prevenzione Deadlock*
	In questo metodo, si tenta di evitare i deadlock annullando una o più delle condizioni necessarie:
	![[Pasted image 20230403115137.png]]
	Il kernel può usare una politica di *allocazione delle risorse* che assicuri che una di queste quattro condizioni non possa verificarsi
	**MUTUA ESCLUSIONE**
		In un sistema non esisterebbero deadlock se *nessuna risorsa è condivisibile*. Infatti, in questo modo in un RRAG esisterebbero solo archi di allocazione, quindi non ci sarebbero *attese circolari*
		Un problema è che *alcune* risorse sono *non condivisibili*, ma si può superare tale problema creando *dispositivi virtuali*, come ad esempio una stampante virtuale *da allocare a vari processi*
		Un altro problema è che questo approccio non può funzionare per risorse SW come file condivisi, che dovrebbero essere modificati in mutua esclusione, per evitare race condition.
	**HOLD AND WAIT**
		Per evitare la condizione relativa al possesso e attesa, è necessario che un processo che abbia acquisito delle risorse *non possa effettuare richieste*, oppure che un processo bloccato su una richiesta non possa poter impegnarne altre.
		In un RRAG, i percorsi che coinvolgono più di un processo non possono comparire, quindi *non possono esserci percorsi circolari*
		Una semplice politica per l'implementazione di questo approccio è consentire ad un processo di effettuare *solo una richiesta di risorse* durante la sua esecuzione, in cui chiede **tutte** le risorse di cui necessita
	**NO PRERILASCIO**
		Se le risorse sono rese prelazionabili, il kernel può assicurare che i processi abbiano tutte le risorse di cui necessitano, evitando così i percorsi circolari nel RRAG. L'unico problema è che i dispositivi sequenziali di I/O non possono essere prelazionati.
	**ATTESA CIRCOLARE**
		Un'attesa circolare può dipendere dalla condizione hold-and-wait, che a sua volta è conseguenza delle condizioni di mutua esclusione e assenza di prelazione. Quindi, non si verifica se non si verifica nessuna di tali condizioni. Le attese circolari possono essere evitate separatamente non consentendo ad alcuni processi di attendere determinate risorse.
		**ALLOCAZIONE SIMULTANEA**
			La strategia più semplice che si può implementare è quella di far sì che ciascun processo, quando necessita di un numero di risorse, vada a *richiedere simultaneamente tutte le risorse*, in modo da non poter mai bloccarsi sulla richiesta di una risorsa. Un processo bloccato non possiede alcuna risorsa. 
			Questa strategia ha un solo difetto : *pregiudica l'efficienza delle risorse*
		**RANKING DELLE RISORSE**
			Si può adottare un'altra strategia per la prevenzione delle attese circolari. Ad ogni classe di risorsa, si assegna un *rank* di risorsa. Alla richiesta di una risorsa, il kernel applica un *vincolo di validità* affinchè la risorsa venga definita *feasible* (fattibile). 
			Il vincolo è : *Il rank della risorsa che richiedo dev'essere maggiore della risorsa con rank maggiore attualmente allocata al processo*.
			Anche questa strategia può degenerare a lungo andare, come l'allocazione simultanea.

*Evitare i Deadlock*
	La politica di evitare i deadlock ammette una richiesta di risorsa solo se si riesce a stabilire che l'accettazione della richiesta non può condurre a deadlock, in qualunque momento. In caso contrario, la richiesta viene messa in attesa, finchè non sarà possibile ammetterla.
	Ogni processo *dichiara un massimo numero di istanze di risorsa* di ogni classe che può richiedere. Il kernel permette che un processo *chieda queste risorse a stadi successivi*, e si utilizza una tecnica di analisi nel caso peggiore per controllare la possibilità di deadlock successivi.
	Questo approccio è *conservativo*, in quanto un processo può terminare il suo funzionamento *senza richiedere il massimo numero di risorse dichiarato*.
	Uno degli algoritmi che implementa questa tecnica è l'algoritmo del *banchiere*; Tuttavia, per molti SO è spesso impossibile conoscere in anticipo le risorse che verranno usate da un processo, per cui è quasi *impossibile* evitare *del tutto* i deadlock

**BANCHIERE**
---
*Algoritmo*
	L'algoritmo del banchiere è un algoritmo di scheduling utilizzato per evitare i deadlock nell'allocazione delle risorse. Questo algoritmo può indicare se un sistema si trovi in uno stato sicuro o meno, nel caso in cui assegni una risorsa ad un processo.
	Se il sistema è in uno *stato sicuro*, allora può garantire che **tutti** i processi avranno termine, mentre se è in uno stato *non sicuro*, non può garantire la terminazione di tutti i processi.
	Si utilizzano quattro matrici:
	*Risorse Allocate*
		Indica il numero di istanze della classe $R_k$ *attualmente allocate* al processo $P_i$
	*Risorse Massime*
		Indica *il massimo numero di istanze* della classe $R_k$ che il processo $P_i$ può richiedere durante l'esecuzione
	*Risorse Richieste*
		Indica il numero di istanze della classe $R_k$ *attualmente richieste* dal processo $P_i$
	*Risorse Totali*
		Indica il numero *totale* di istanze della classe $R_k$ *appartenenti al sistema*.
	Il kernel ammette il processo $P_j \iff R_{Max} < R_{Tot}$  
	Le tecniche per evitare i deadlock sono implementate trasferendo il sistema da uno stato *sicuro* all'altro, seguendo questi step:
	1) *Quando un processo effettua una richiesta*, si calcola il nuovo stato in cui il sistema si troverebbe se essa fosse ammessa. Questo stato viene detto **Stato Proiettato**
	2) Se lo stato *Proiettato* è uno stato sicuro, si ammette la richiesta, aggiornando le matrici $R_{Alloc}$ e $R_{Tot}$. Altrimenti, la richiesta rimane *in attesa*
	3) *Quando un processo rilascia risorse*, o *termina l'esecuzione*, si esaminano le richieste in attesa per verificare se ammettendo una di esse il sistema si troverebbe in uno stato sicuro.
	Per ammettere una risorsa, e quindi allocare le risorse al processo, il sistema controlla che la richiesta sia *feasible* mediante la formula:
		$R_{Tot} - R_{TotAlloc} \ge R_{Max}(P) - R_{Alloc}(P)$ 
	Quando un processo effettua una nuova richiesta, viene inserita nella matrice $R_{Rich}$, che memorizza le richieste in attesa di *tutti* i processi, e viene invocato l'algoritmo, con l'identificativo del processo richiedente.
	Quando un processo rilascia alcune risorse allocate per sé, oppure termina le proprie operazioni, viene invocato l'algoritmo per ogni processo la cui richiesta è in attesa.
	L'algoritmo può essere descritto come segue:
	*Passo 1*
		L'algoritmo simula l'accettazione della richiesta, andando allo stato *Proiettato*
	*Passo 2*
		Controlla se lo stato *Proiettato* è uno stato *sicuro*, ovvero se esistono risorse a sufficienza per permettere l'accettazione delle richiesta 
	*Passo 3*
		Se ciò è possibile, l'algoritmo alloca le risorse, calcola il nuovo stato, e ripete i passi finchè tutti i processi non vanno a termine
	Per controllare se lo stato proiettato è uno stato sicuro, si controlla se *il massimo numero di risorse di cui necessita ogni processo attivo può essere soddisfatto allocando alcune delle risorse libere*.
		In caso affermativo, l'algoritmo simula il suo comportamento, cancellandolo dall'insieme dei processi active e rilasciando le risorse ad esso allocate.
		Questa azione viene ripetuta finchè non è possibile cancellare più processi dall'insieme.
		Se al termine di questi passi, l'insieme è vuoto, *il sistema si trova in uno stato sicuro*, quindi l'algoritmo cancella la richiesta dalla lista e alloca le risorse richieste
	La complessità di questo algoritmo è $O(n^2m)$, dove n è il *numero di processi* ed m è *il numero di classi di risorsa*

**STARVATION**
---
*Starvation*
	La starvation è quella situazione in cui vi è *impossibilità* per un processo di ottenere le risorse di cui necessita
	Si possono utilizzare, oltre a vari algoritmi di scheduling come il RR, le tecniche di *aging*, ovvero quelle tecniche che aumentano la priorità di una richiesta finchè essa non viene espletata
	Si dice che un programma è *bandwidth-starved* quando la sua esecuzione è rallentata da un'**insufficiente velocità di accesso alla memoria**, oppure che è *CPU-starved* quando il processo **è troppo lento per eseguire efficacemente il codice**