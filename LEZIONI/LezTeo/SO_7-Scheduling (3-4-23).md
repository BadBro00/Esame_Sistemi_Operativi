
**GESTIONE CPU**
---
*Politiche di Scheduling*
	La politica di Scheduling decide a quale processo debba essere assegnato l'uso della CPU.
	Per questo motivo, le decisioni dello scheduler influenzano sia il servizio utente che le prestazioni del sistema
	Lo scheduling è quella parte di codice che si occupa di selezionare il prossimo processo che passerà dallo stato *ready* allo stato *running*.
	Una volta che una richiesta viene elaborata dalla CPU, essa può essere completata oppure può essere prelazionata.
	Con *richiesta* si intende solitamente l'esecuzione di un job o di un processo. 
	Gli eventi sono il suo arrivo, ammissione, scheduling, prelazione e completamento. Un processo di un job è detto *in arrivo* quando viene sottomesso dall'utente, ed è ammesso quando *lo scheduler comincia a considerarlo nello scheduling*.
	Le politiche di scheduling hanno diversi parametri di valutazione:
		![[Pasted image 20230324154657.png]]
		![[Pasted image 20230324154713.png]]
		![[Pasted image 20230324154734.png]]
		![[Pasted image 20230324154748.png]]
	*Tecniche di Scheduling*
		Gli scheduler si basano su tre tecniche *fondamentali* per fornire un buon compromesso fra prestazioni del sistema e servizio utente:
		**Scheduling basato su PRIORITA'**
			Il processo in esecuzione è quello con priorità più alta. Ciò è assicurato selezionando il processo in stato *ready* avente priorità maggiore, e prelazionando il processo in esecuzione quando un altro con priorità più alta diventa *ready*. 
			**Solitamente, si assegna una priorità alta ai processi I/O-bound**, per avere un elevato *throughput* del sistema.
		**Scheduling basato sul RIORDINO DELLE RICHIESTE**
			Implica il fatto che le richieste verranno eseguite in un ordine diverso rispetto a quello di arrivo. Può migliorare sia il servizio utente che il throughput del sistema.
		**Scheduling basato sulla VARIAZIONE DELLA TIME-SLICE**
			Facendo uso della time-slice si ottengono tempi di risposta migliori utilizzando valori minori di time-slice, ma si riduce anche l'efficienza della CPU in quanto avvengono maggiori context switch
		La *priorità* viene usata dallo scheduler quando più processi sono in attesa dell'uso della CPU
		La priorità può essere *statica*, o *dinamica*, se alcuni suoi parametri cambiano durante l'elaborazione
		Lo scheduling basato su priorità ha lo svantaggio che una richiesta a bassa priorità può non venir mai espletata se arrivano sempre richieste a priorità maggiore. Una tecnica per prevenire questa *Starvation* è l'**Aging**, ovvero aumentare la priorità della richiesta fin quando non viene eseguita.
	*Scheduler nel SO*
		I moderni sistemi usano tre tipi diversi di scheduler:
		*Scheduler a lungo termine*
			Decide quale processo entra nella coda dei processi *ready* tra quelli che lo richiedono, e di fatto quindi gestisce il grado di *multiprogrammazione*, ovvero quanti processi sono in memoria. Lo scheduler può ritardare l'ammissione di una richiesta se non riesce ad allocarle risorse sufficienti o se *l'ammissione porterebbe ad un calo di prestazioni*.
		*Scheduler a medio termine*
			Gestisce la *permanenza in memoria* dei processi non in esecuzione. Decide quindi quali processi *swappare*
		*Scheduler a breve termine*
			E' detto anche *dispatcher*. Decide quale processo *ready* può ricevere l'uso della CPU. 
			I momenti in cui può entrare in esecuzione sono quattro:
			**Running->Blocked**
				Dovrà selezionare quale processo ready potrà andare in esecuzione.
			**Blocked->Ready**
				Deve determinare con quali altri processi ready compete per l'esecuzione
			**Running->Ready**
				Determina se il processo la cui esecuzione è stata interrotta può continuare ad essere eseguito o meno
			**Terminated**
				Lo scheduler dovrà decidere quale processo dovrà essere eseguito
			I casi 1 e 4 sono detti *preemptive*, dovendo scegliere un processo ready da mandare in esecuzione, mentre i casi 2 e 3 sono detti *non preemptive*, in quanto si può anche lasciare in esecuzione lo stesso processo che ha cambiato stato
	Ogni processo può essere visto nel SO come un alternanza di cicli della CPU e dell'I/O. Un processo è riassumibile come:
		Esecuzione d'istruzioni (*CPU-burst*)
		Attesa di eventi o operazioni di I/O (*I/O-burst*)
	I processi *CPU-bound* hanno cicli di CPU molto lunghi, mentre i processi *I/O-bound* hanno per maggior parte cicli di I/O

**POLITICHE DI SCHEDULING**
---
*Politiche di Scheduling*
	Una classificazione delle politiche può essere fatta sul modo in cui effettuano il context switch:
		La politica di scheduling *preemptive* dà la possibilità di interrompere il processo in esecuzione a favore di un altro processo. Ciò è utile nel caso arrivi un processo *ready* a priorità maggiore, o con istruzioni che devono essere eseguite prima di un altro processo.
		La politica di scheduling *non-preemptive* invece costringe ogni processo a terminare oppure a bloccarsi, prima di poter effettuare un context switch
	Un'altra classificazione delle politiche è quella circa la *priorità*.
		Le politiche che la usano selezionano i processi cui attribuire la CPU in base alla priorità acquisita da ciascuno di essi. Queste politiche sono utili soprattutto nei sistemi *Real-Time* e nei sistemi *Interattivi*
		Le politiche che non la usano, considerano i vari processi "equivalenti", ovvero senza privilegiarne alcuno. Queste politiche sono basate su strategie di ordinamento come il **First Come First Served**
	Un'altra classificazione è quella relativa alle politiche *Statiche* o *Dinamiche*
		Nelle politiche *statiche*, ogni processo conserva nel tempo i suoi diritti (*costanti*) all'uso della CPU. Le decisioni di schedulazione sono prese *prima che il sistema ne inizi l'esecuzione*.
		Nelle politiche *dinamiche*, ogni processo modifica i propri diritti in base al comportamento passato o estrapolando quello futuro. Le decisioni di schedulazione vengono prese *durante l'esecuzione dei processi*

*Algoritmi di Schedulazione*
	Esistono tre ambienti differenti, per cui esistono determinati algoritmi di schedulazione:
	*Batch*
		Nei sistemi Batch, non ci sono processi in attesa di una risposta veloce. Sono accettabili sia algoritmi *preemptive* che *non-preemptive*. Sono importanti il *throughput*, il *tempo di turnaround* e l'uso della CPU.
		Le politiche usate sono : **FCFS** e **SJF**
	*Interattivo*
		Nei sistemi Interattivi, il prerilascio è essenziale per evitare che un processo si impossessi della CPU. La differenza con i sistemi Real-Time è che quelli interattivi sono d'uso generale, e possono eseguire programmi arbitrari che non collaborano, o sono persino *dolosi*. 
		Le politiche usate sono : **RR**,**Priorità**,**Code Multiple** e **HRRN**
	*Real-Time*
		Nei sistemi Real-Time, il prerilascio non è sempre necessario, perchè i processi sanno che non possono essere eseguiti per lungo tempo, e normalmente fanno il loro lavoro e si bloccano in fretta. I sistemi Real-Time eseguono solo programmi che agevolano le altre applicazioni

**ALGORITMI DI SCHEDULING**
---
*Politiche di Scheduling **NON-PREEMPTIVE***
	Nello scheduling non-preemptive, un processo viene elaborato fino al completamento o fino al blocco. Per queste ragioni, queste politiche risultano molto semplici : dato che una richiesta non può mai essere prelazionata, lo scheduler si occupa semplicemente di riordinarle, per migliorare il servizio utente o le prestazioni del sistema.
	Le tre politiche sono:
	**FCFS**
		Questo scheduling è senza priorità ed è *statico*. I processi sono schedulati nell'ordine in cui arrivano. I processi *ready* sono organizzati come una coda *FIFO*.
		Questo tipo di algoritmo è semplice da implementare, ma poco efficiente, considerando il tempo medio d'attesa.
		Questo algoritmo privilegia i processi *CPU-bound*, e presenta l'effetto *convoglio*: i processi che richiedono meno tempo di CPU devono attendere che i processi CPU-bound termino l'esecuzione o si blocchino.
	**SJF**
		Gli algoritmi *SJF* possono essere sia non preemptive (*Shortest Next Process FIrst*), che preemptive (*SRTF*)
		Lo scheduling SNPF è senza prelazione, con priorità e *dinamico*.
		L'algoritmo seleziona il processo in attesa che userà la CPU *per minor tempo*. Se due processi hanno lo stesso tempo d'esecuzione, verrà applicato lo scheduling FCFS.
		L'algoritmo presenta però due problematiche:
		*Deve conoscere in anticipo i tempi d'esecuzione*
			Visto che il sistema operativo non conosce a priori i tempi di servizio, è necessario effettuare una *stima*
		*Possiede un potenziale problema di Starvation*
			E' possibile che un processo rimanga in attesa per troppo tempo prima di essere schedulato, se vengono aggiunti sempre processi di piccola durata alla coda di *ready*
	**HRRN**
		Lo scheduling HRRN è un algoritmo senza prelazione, con priorità e *dinamico*.
		Questo algoritmo viene usato per prevenire l'*aging*, ovvero l'eccessiva attesa dei processi lunghi, rispetto a quelli brevi.
		Questa politica calcola i rapporti di risposta di ogni processo, secondo la formula:
		$R_r = \frac{T_{att}+T_{serv}}{T_serv}$
		Dove:
			 $T_{att}$ è il tempo d'attesa del processo, ovvero per quanto tempo *dall'arrivo* il processo non è stato ancora eseguito.
			$T_{serv}$ è il tempo di servizio del processo, ovvero il CPU-burst del processo, cioè il tempo di CPU necessario al processo per eseguire tutte le sue istruzioni.
		Calcolati i rapporti di risposta di ogni processo, l'algoritmo schedula sempre quello con il rapporto più alto.
		Il rapporto di un processo lungo, col passare del tempo, diventa sufficientemente grande per rendergli possibile l'esecuzione. Ciò previene la starvation riscontrata negli altri algoritmi.

*Politiche di Scheduling **PREEMPTIVE***
	Nello scheduling con prelazione, i processi possono *sempre* essere prelazionati a favore di altri processi, *prima che possano portare a termine la loro esecuzione*. Una richiesta può essere prelazionata diverse volte prima che venga espletata, per cui vi è un maggior overhead rispetto agli scheduling non-preemptive.
	Le tre politiche di scheduling preemptive sono:
	**SRTF (/STG)**
		Nello scheduling *Shortest Remaining Time First*, o *Shortest Time to Go*, quando viene sottomesso un nuovo processo la cui durata è minore del tempo necessario al processo in esecuzione per completare le sue istruzioni, lo scheduler provvede ad *effettuare un context switch* per assegnare l'uso della CPU al nuovo processo. In caso di uguaglianza, *viene selezionato il processo non schedulato per più tempo*. Questa politica ha lo svantaggio di permettere ai processi lunghi di incorrere in starvation.
	**RR con time-slice**
		Lo scheduling Round Robin è un algoritmo con prelazione, con o senza priorità e statico o dinamico.
		Ad ogni processo viene assegnato un intervallo di tempo (detto *time-slice*), che definisce il massimo intervallo di tempo in cui il processo può essere in esecuzione. Per scandire i quanti di tempo, viene generato un *timer interrupt* che segnala al sistema lo scadere della time-slice
		Questo algoritmo privilegia i processi CPU-bound perchè *utilizza l'intero quanto assegnato*, mentre i processi I/O-bound possono non utilizzarlo del tutto in quanto devono completare anche operazioni di I/O, senza usare la CPU.
		L'unico problema di questo algoritmo è la *gestione del quanto*, ovvero il valore della time-slice da assegnare: un valore troppo basso causerebbe molti context switch e quindi un grande overhead, ma assegnarlo troppo alto causerebbe ritardi e tempi di risposta molto lunghi.
		![[Pasted image 20230329112503.png]]
	**LCN**
		Questa politica seleziona sempre *il processo che ha utilizzato meno tempo di CPU*. In caso di uguaglianza, lo scheduler seleziona il processo non elaborato per maggior tempo.
		Tutti i processi hanno relativamente gli stessi progressi in termini di CPU-burst, garantendo che i processi brevi finiranno prima di quelli lunghi. 
		Questo algoritmo ha lo svantaggio di causare la Starvation dei processi lunghi, e trascura i processi esistenti quando un nuovo processo entra nel sistema, dato che *ha usato meno CPU-burst*

----------------------------------------------------------------------------------------

**SCHEDULING IN PRATICA**
---
*Sleep Mode*
	Quando non vi sono processi *ready*, la CPU dev'essere pronta a gestire qualsiasi interrupt che uno dei processi *blocked* può attivare. Per rispondere a questo requisito, i computer moderni sono dotati di una modalità speciale, detta *sleep mode*, in cui la CPU **non esegue istruzioni, ma può gestire gli interrupt**. 
	Alcuni computer, oltre a non eseguire istruzioni, **calano il clock della CPU** e la *disconnettono dal bus* di sistema.

**ALGORITMI**
	*Scheduling basato su priorità*
		Lo scheduling a priorità fa uso di *diverse code di processi*, in base alle varie priorità degli stessi. La coda a priorità maggiore è la prima coda dello scheduler, mentre quella a priorità minore è l'ultima coda.
		Ogni coda *è organizzata come una coda di PCB*, ognuno dei quali punta al prossimo PCB del processo in coda.
		La testa della coda contiene due puntatori : uno al primo processo nella coda, l'altro punta alla *testa della coda a priorità inferiore*. Lo scheduler scorre le code a partire da quella a priorità maggiore, fino all'ultima. Seleziona il primo processo nella prima coda non vuota che trova.
		Lo scheduling basato su priorità può causare la starvation dei processi a bassa priorità. Se si usa la tecnica dell'*aging*, le priorità devono essere considerate *dinamiche*, cioè *il PCB dei processi devono poter essere **spostati** fra le varie code*
	*Scheduling RR con time-slice*
		Può essere implementato mediante una lista singola di PCB dei processi ready, dove la lista è organizzata come una coda. Lo scheduler rimuove il primo PCB dalla coda e schedula il processo corrispondente.
		*Se la time-slice scade*, il processo viene posto in fondo alla coda.
		*Se il processo avvia operazioni di I/O*, il suo PCB viene posto in fondo alla coda al termine dell'operazione
		Un processo, nel passare del tempo, *migra dal fondo alla testa* della coda per essere schedulato
	*Scheduling multilivello*
		Questo scheduling è detto anche *a code multiple*. Combina lo scheduling basato su priorità e quello round-robin per garantire una buona combinazione fra prestazione del sistema e tempi di risposta.
		Uno scheduler multilivello utilizza diverse code di processi pronti, e a ciascuna è assegnata una priorità. Alla coda con priorità maggiore viene assegnato un quanto *più piccolo*, mentre alle coda con priorità minori viene assegnato un quanto via via *più grande*.
		Uno scheduler multilivello è un algoritmo con prelazione, con priorità e *Statico*. I processi della classe più alta vengono eseguiti per un quanto, quelli della seconda per due quanti, ecc..
		Ogni volta che un processo rimane in esecuzione per tutta la durata del suo quanto, viene "abbassato" di una classe.
		Un processo in testa alla coda viene schedulato *solo se le code con priorità maggiore sono vuote*. Per garantire un'efficienza ottimale, si dà priorità maggiore ai processi I/O-bound
	*Scheduling multilivello **Adattivo***
		E' anche detto *a code multiple con feedback*. Fa uso di priorità *dinamiche*, che consente ad un processo di spostarsi fra le varie code dello scheduler.
	*Scheduling fair-share*
		Uno scheduling fair-share si occupa di assicurare un uso *equo* della CPU da parte degli utenti o delle applicazioni. In pratica, gli utenti o le applicazioni che usano un numero maggiore di processi ricevono meno risorse.
	*Scheduling a lotteria*
		In questo scheduling, vengono distribuiti *biglietti* ai processi che condividono una risorsa (*es: tempo di CPU*). Quando lo scheduler deve selezionare un processo a cui attribuire l'uso della CPU, viene scelto a caso un *biglietto* e il processo che lo possedeva ottiene l'uso della risorsa.
		I processi, inoltre, possono *scambiarsi i biglietti*, per avvantaggiare i processi con cui cooperano per raggiungere un obiettivo comune.
	*Scheduling Real-Time*
		Nello scheduling real-time il tempo gioca un ruolo fondamentale, dovendo rispettare le *deadline*. I sistemi RT sono classificati in:
		*RT Hard*
			Dove le deadline non devono essere superate
		*RT Soft*
			Dove le deadline possono essere superate senza conseguenze gravi per il sistema.
		Gli eventi a cui un sistema RT può dover reagire sono *Periodici* o *Aperiodici*
		In questi sistemi, gli algoritmi utilizzani sono:
		*Statici*
			Che cioè prendono decisioni sulla schedulazione *prima che inizi l'esecuzione*. Ciò funziona solo se le informazioni sull'esecuzione sono disponibili *in anticipo*
		*Dinamici*
			Le decisioni sulla schedulazione vengono prese *durante l'esecuzione*
		I processi di un'applicazione Real-Time interagiscono fra loro per garantire che le loro azioni vengano eseguite nel *giusto ordine*. Per gestire le dipendenze fra i processi, viene utilizzato un *grafo di precedenza* fra i vari processi.
		La **schedulabilità** è una sequenza di decisioni di scheduling, che consentono ai processi di un'applicazione di agire seguendo le precedenze e *rispettare il requisito di risposta* dell'applicazione.
	*Scheduling della Deadline*
		Per ogni processo possono essere definiti due tipi di *Deadline*:
		**Scadenza d'inizio**
			Il minimo istante entro il quale le operazioni del processo devono *iniziare*
		**Scadenza di fine**
			Cioè il tempo entro cui le operazioni del processo devono *terminare*
		Esistono vari modi per determinare le scadenze che prendono in considerazione diversi fattori: *le precedenze del processo*, *la possibilità di eseguire I/O*, *disponibilità delle risorse*.
		Per calcolare la deadline di ciascun processo, si usa la formula:
		$D_i = D_{app} - \sum_{k \ \in \ discendenti(i)}(x_k)$ 
			Dove 
			$D_{app}$ è la deadline dell'applicazione
			$x_k$ è il tempo di servizio del processo $P_k$
		![[Pasted image 20230329115833.png]]
		*Earliest Deadline First*
			Seleziona sempre il processo con deadline più vicina.
			Si consideri la sequenza di scheduling dei vari processi:
			Sia *seq* la la sequenza in cui i processi sono schedulati;
			Se $pos(i)$ è la posizione di $P_i$ nella sequenza delle decisioni di scheduling, lo sforamento delle deadline di $P_i$, ovvero $D_i$ non avviene se:
			$\sum_{k:pos(P_k)<=pos(P_i)} x_k <= D_i$ 
			Ciò è vero solo se esiste *una schedulazione ammissibile*.