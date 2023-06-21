
**INPUT/OUTPUT CONTROL SYSTEM**
---
*Livelli IOCS*
	Una delle funzioni principali del SO è il controllo dei dispositivi di I/O. Esso deve formare un'interfaccia fra dispositivi fisici ed il resto del sistema, che sia semplice da usare e *la stessa per tutti* i dispositivi.
	Quando un processo effettua una richiesta di lettura o scrittura su un file, il FS passa la richiesta al sistema IOCS. Questo sistema mantiene alcuni dati in aree di memoria dette *buffer* (o **cache del disco**), per velocizzare l'elaborazione dei file.
	La *prima* operazione che l'IOCS effettua è quella di *controllare se i dati richiesti dal processo sono presenti in memoria*.
		In caso affermativo, il processo può accedere direttamente ai dati
		In caso contrario, *l'IOCS esegue tante operazioni di I/O quante necessarie* per caricare i dati nella cache del disco, e durante tali operazioni *il processo attende*
	Visto che molti processi effettuano operazioni di I/O concorrentemente, queste operazioni vengono schedulate da algoritmi di *Schedulazione del disco*, che fornisce un elevato throughput dei dispositivi.
	L'IOCS è organizzato in due livelli:
	*Metodo d'Accesso*
		Gestisce la lettura e scrittura dei dati per rendere efficiente l'elaborazione di un file.
	*IOCS Fisico*
		Esegue l'I/O a livello di dispositivo, e utilizza le politiche di scheduling per migliorare il throughput dei dispositivi I/O.
	**ORGANIZZAZIONE I/O**
		Ci sono tre modi per effettuare le operazioni di I/O:
		![[Pasted image 20230417110246.png]]
		![[Pasted image 20230417110303.png]]
		I dispositivi I/O sono connessi al *Controller di Dispositivo*, che a sua volta è connesso al controller *DMA*
		Ogni dispositivo connesso ha associato un ID *univoco*, che è della forma $(controller\_ID,device\_ID)$
		Un'operazione di I/O è caratterizzata:
			Dal *tipo di operazione* da eseguire
			Dall'*indirizzo del dispositivo di I/O*
			Dal *numero di byte* da trasferire
			Dagli *indirizzi delle aree di memoria* dei dispositivi I/O *coinvolti* nel trasferimento.
		Quando un'operazione di I/O viene eseguita *in modalità DMA*, la CPU avvia l'operazione di I/O, **ma non è coinvolta nell'operazione**. Quest'operazione è detta *Istruzione di I/O*, e richiede la partecipazione del controller DMA, del controller dispositivo e del dispositivo di I/O
		*Third Party DMA*
			Nel DMA di terze parti, all'occorrenza di un'operazione di I/O succede che:
			1) Il controller DMA invia i dettagli allo controller del dispositivo coinvolto
			2) Il dispositivo, una volta svolta l'operazione, consegna i dati al controller
			3) Il trasferimento di dati avviene nel seguente modo:
				1) Il controller invia un segnale *DMA Request* quando è pronto per il trasferimento
				2) Il DMA, dopo aver ricevuto il segnale, ottiene l'accesso al *controller del bus*, e ci inserisce l'indirizzo di memoria che partecipa al trasferimento, e invia un segnale di *acknowledgement*.
				3) Il controller, dopo aver ricevuto il segnale, trasferisce i dati verso la memoria
				4) Quando il trasferimento è terminato, il DMA genera un interrupt *di completamento dell'I/O*, a cui associa l'indirizzo della periferica. Di conseguenza, l'ISR analizza ed individua il dispositivo che ha completato l'operazione.
			Può accadere che la CPU intervenga durante l'operazione di I/O. In questo caso, il bus sarà conteso fra DMA, CPU e memoria. Per evitare contese e ritardi, è possibile applicare il *cycle stealing*:
			**La CPU e il DMA si attendono l'un l'altro, quando uno dei due deve trasferire dati**
	*Dispositivi di I/O*
		I dispositivi di I/O funzionano con diversi supporti, servono a scopi diversi ed organizzano ed accedono ai dati in modi diversi, per cui possono essere *classificati* secondo i seguenti criteri:
		*Scopo*
			Dispositivo di input/output/memorizzazione
		*Tipo di accesso*
			L'informazione scritta/letta con un comando di I/O si dice che forma un record. Le tipologie di accesso possono essere *sequenziali* o *casuali*.
			I dispositivi a **Carattere** sono dispositivi lenti, trasferendo un carattere alla volta fra memoria e dispositivo. Non sono indirizzabili, e non possono eseguire nessuna operazione di *posizionamento* (**mouse,tastiera,stampante**)
			I dispositivi a **Blocchi** sono più rapidi, in quanto trasferiscono *blocchi di dati di lunghezza fissa*, ognuno dei quali ha un proprio *indirizzo*, e per questo motivo sono indirizzabili, ovvero **è possibile leggere ciascun blocco in maniera *indipendente* rispetto agli altri** (**Dischi**)
		*Tempo di Accesso e Trasferimento*
			Le operazioni di I/O richiedono la somma di due tipi di tempi: 
				$t_a$ (*Tempo d'accesso*) : è il tempo che intercorre fra l'operazione read/write e l'inizio del trasferimento
				$t_x$ (*Tempo di trasferimento*) : è il tempo necessario a trasferire i dati da/verso la periferica
			Dunque, il tempo d'accesso è dato da:
			$t_{I/O} = t_a + t_x$
	*Individuazione e Correzione degli errori*
		I dispositivi di I/O sono in genere dotati di una componente *meccanica* e una *elettronica*, ed è spesso possibile separarle. La componente elettronica prende il nome di *Controllore del Dispositivo*. Ciò che realmente esce dal dispositivo è una sequenza di bit, che comincia con un *preambolo iniziale*, seguito da un checksum. Il preambolo è scritto quando il disco viene *formattato* e contiene svariate informazioni. 
		Il compito del *controllore di dispositivo* è quello di *convertire la sequenza di bit in un blocco di byte* ed eventualmente eseguire la *correzione degli errori*.
		Prima, il blocco di byte è ricostruito un bit alla volta in un *buffer* che si trova all'interno del controllore stesso, e *dopo che il suo checksum è stato controllato*, e che quindi non vi siano errori, può essere copiato all'interno della memoria.
		Per individuare e correggere gli errori, si sfruttano le informazioni ridondanti memorizzate confrontandole con le informazioni dell'individuazione dell'errore. Se avviene un *mismatch*, si è verificato un errore ed è necessario correggerlo.
		Per molti vecchi sistemi, si usava il *bit di parità*
			Quando si memorizza un byte di informazione, gli si associa un'informazione aggiuntiva che registra se il numero di bit *settati* (=1) è **pari o dispari**.
		In sistemi moderni, si usa il controllo *Controllo di Ridondanza Ciclico*
			Si utilizza *una funzione di hash* per rivelare errori su più.
		In entrambi gli approcci si usa l'aritmetica modulo 2, si eseguono addizioni senza resto implementandole come XOR.
	*DMA-based I/O*
		In questo trasferimento, la CPU delega il DMA. Inoltre, i dispositivi che effettuano sono collegati al DMA, per cui possono esserci problemi di contesa del buffer del DMA.
		Durante un'operazione di lettura (*input*), i dati vengono trasferiti ad un buffer del DMA, e poi questi saranno trasferiti in memoria, al termine dell'operazione.
		Durante un'operazione di scrittura (*output*), i dati vengono trasferiti dalla memoria al buffer del DMA per poi essere trasferiti alla periferica.
	*Memory Mapped I/O*
		Il trasferimento di dati fra CPU e un dispositivo di I/O può essere effettuato tramite la tecnica dell'I/O *mappato in memoria*, dove *ogni controllore possiede dei registri*, usati per la comunicazione con la CPU, che può comunicare coi registri in due modi:
		*Primo approccio*
			Ogni registro del controllore è caratterizzato da *un numero di porta I/O*. In questo schema, gli spazi d'indirizzamento per l'I/O e la memoria *sono diversi*.
		*Secondo approccio*
			Un insieme d'indirizzi di memoria sono riservati ad un dispositivo di I/O, cioè *ad ogni registro del controllore viene assegnato un indirizzo di memoria unico*. Questo sistema è chiamato I/O *mappato in memoria*.
		In questo modo il trasferimento avviene senza il DMA

**DISCHI**
---
*Dischi Magnetici*
	![[Pasted image 20230417172607.png]]
	I dischi magnetici sono costituiti da vari *piatti*, ognuno dei quali contiene tante *tracce*. Tutte le tracce uguali, posizionate su piatti differenti, formano un *cilindro*.
	L'elemento di memorizzazione del disco magnetico è un oggetto circolare, chiamato *piatto*, che ruota sul suo asse ed è ricoperto da un materiale magnetico.
	Ogni piatto memorizza i byte lungo le *tracce* circolari sulla sua superficie, di cui ognuna è divisa in *settori*. Alcuni dischi possono avere zone con più settori e zone con meno settori, ma grazie alla *virtualizzazione*, i moderni SO vedono i dischi aventi tutti lo stesso numero di settori.
	La *testina* è capace di leggere e scrivere sulla superficie del piatto, essendo capace di muoversi grazie al *braccio*. La posizione della testina è *solidale con tutte le altre* sugli altri piatti, ovvero **se una testina è posizionata sopra una traccia, tutte le altre saranno nella stessa posizione** cui il cilindro appartiene. Un *blocco* è l'insieme di tutti i settori posti nella stessa posizione in tutti i piatti.
	Quando un disco è in funzione, tutti i piatti ruotano grazie a un motore, che li fa girare a velocità elevata, espressa in *rotation per minute*
	*Parametri di prestazioni*
		Uno dei parametri più importanti è il **tempo d'accesso**, cioè *l'intervallo* di tempo fra l'esecuzione di un comando di lettura/scrittura e l'inizio del trasferimento dei dati. Il tempo d'accesso è esprimibile tramite la formula
		$t_a = t_s + t_r + t_t$
		Dove
			$t_r$ è il *tempo di ricerca*, ovvero il tempo per muovere la testina sulla traccia cercata $[5,15] ms$
			$t_r$ è la *latenza rotazionale*, cioè **il tempo impiegato dal disco per ruotare, portando il settore interessato sotto la testina**. La *latenza rotazionale media* è il tempo impiegato per mezza rivoluzione del disco $[3,4]ms$. In sostanza, la latenza rotazionale è data da $\frac{1}{r}$, dove $r$ è la velocità di rotazione, mentre la *media* è data da $\frac{1}{2r}$.
			$t_t$ è il *tempo di trasferimento*, cioè **il tempo necessario per trasferire un certo numero di blocchi** da leggere/scrivere, ed è dato da $T = \frac{b}{rN}$, dove $b$ è il numero di blocchi, $r$ è la velocità di rotazione e $N$ è il numero di blocchi per traccia.
	L'indirizzo di un record è caratterizzato dal numero del cilindro, numero di superficie e numero di record. Per ottimizzare l'uso della superficie del disco, le tracce sono organizzate in *settori*, in slot di dimensione fissa che contengono un record di informazione. La suddivisione può avvenire tramite HW (*hard sectoring*), o tramite SW (*soft sectoring*).
	*Organizzazione dei dati sul disco*
		E' fondamentale che i dati siano organizzati per garantirne un accesso efficiente. I dati letti da un dispositivo di I/O sono memorizzati nel *buffer DMA*, e poi vengono trasferiti in memoria *come unico blocco*. Per poter accedere ad un altro settore il disco deve compiere una rivoluzione, e ciò implica *perdita di tempo* nell'attesa. Per questo bisogna organizzare bene i dati, per ridurre i giri e velocizzarne l'esecuzione.
		*Alternanza dei settori*
			Una delle tecniche per fare ciò è l'alternanza dei settori, in cui i settor consecutivi non sono posti contiguamente, ma si alternano, in modo che se il disco ruota, si avrà la possibilità di avere quel settore sotto la testina.
			![[Pasted image 20230418084903.png]]
			Il numero di settori che si saltano prende il nome di *fattore di alternanza*.
		*Testina asimmetrica*
			Il disco richiede tempo per commutare la lettura dei dati da una traccia all'altra (*tempo di commutazione*), e durante questo tempo il disco *potrebbe perdere dei settori*, per cui bisognerà attendere il prossimo giro.
			Con l'**asimmetria della testina**, si organizzano le posizioni d'inizio traccia *su piatti diversi del cilindro*, in modo che lo sfasamento possa contrastare il movimento, e quindi non si perde il settore considerato
			Con l'**asimmetria del cilindro**, si organizzano le posizioni d'inizio traccia su *cilindri consecutivi*, per cui i dati sono resi asimmetrici come per la testina. Ciò minimizza il numero di giri necessario a posizionarsi su un'operazione di lettura/scrittura.

**RAID**
---
*Dischi RAID*
	Questa tecnologia usa un insieme di dischi rigidi per condividere o replicare i dati, e ha come obiettivi principali
	*L'aumento delle prestazioni* e *Migliore affidabilità*. Per fare ciò, distribuisce i dati coinvolti in un'operazione di I/O su diversi dischi, ed esegue le operazioni *su questi dischi **in parallelo***.
	Questa caratteristica può fornire accessi veloci o alti tassi di trasferimento, in base alla configurazione adottata. L'alta affidabilità è ottenuta *memorizzando informazioni ridondanti*, il cui accesso non necessita di tempo di I/O aggiuntivo, in quanto *si può accedere in parallelo* sia ai dati che alle informazioni ridondanti.
	Esistono diverse *configurazioni* RAID, che utilizzano diverse tecniche di ridondanza ed organizzazione, e vengono dette *livelli RAID*, e ad oggi vanno da 0 a 6. Esistono inoltre due tecniche *ibride*, basate sui livelli 0 e 1, che insieme al livello 5 risultano le configurazioni più usate.
	Tutti i livelli hanno caratteristiche in comune:
		*I vari HD* configurati in RAID *sono visti dal SO come **un disco unico***.
		I dati sono divisi in *stripes*, memorizzate su più dischi *nella stessa posizione*, in modo che sincronizzati i dischi è possibile leggere una striscia simultaneamente
		La capacità di ridondanza dei dischi è usata per *memorizzare le informazioni di parità* che permettono il recupero dei dati
	Il RAID può essere implementato sia con HW dedicato (*Controllore RAID*), sia con SW specifico. 
	Nel primo caso, dev'essere disponibile almeno un controllore RAID, che può essere una scheda PCI, o il controller integrato nella scheda madre.
	Nel secondo caso, è il SO che gestisce l'insieme di dischi attraverso un normale controller.
	**RAID 0**
		![[Pasted image 20230418090127.png]]
		Nel RAID 0, i dati vengono distribuiti su più dischi tramite la tecnica dello *striping*, dividendo equamente i dati fra due o più dischi *senza alcuna informazione di parità o ridondanza*. Questa non è del tutto una configurazione RAID, perchè *non usa ridondanza*. Le operazioni sono svolte in parallelo sui vari dischi.
		*Vantaggi*
			Garantisce tassi di trasferimento elevati
		*Svantaggi*
			*Scarsa affidabilità*. I dati sono inaccessibili anche con un singolo disco spento. La mancanza di ridondanza causa *perdita dei dati in caso di malfunzionamento*
	**RAID 1**
		![[Pasted image 20230418090355.png]]
		Nel RAID 1, viene memorizzata *una copia esatta* di tutti i dati su due o più dischi, e questa tecnica prende il nome di *Disk Mirroring*. Se un dato viene aggiornato da un processo, una copia di questo dato viene copiata su ogni disco. Il RAID 1 porta significanti miglioramenti nella lettura. Infatti, le operazioni vengono svolte in parallelo, aumentandone le prestazioni in lettura, leggendo l'informazione disponibile nel minor tempo. E' inoltre possibile *leggere da un disco mentre l'altro è occupato*.
		*Vantaggi*
			Maggiore affidabilità, creando tante copie quanti sono i dischi
			Migliori prestazioni in lettura
		*Svantaggi*
			Elevato Overhead, dovendo aggiornare più copie dello stesso dato ad ogni modifica.
			Il sistema vede un unico disco, con capienza pari a quella del disco più piccolo.
	**RAID 2**
		![[Pasted image 20230418090731.png]]
		Nel RAID 2 si utilizza la tecnica del *bit striping*, memorizzando *ogni bit* di dati ridondanti *su dischi differenti*, e i codici per la correzione degli errori sono salvati *su altri dischi*. Solitamente il codice usato è il *codice di Hamming*, essendo in grado correggere errori su singoli bit e rilevare errori doppi.
		In pratica, *una parte dei dischi viene usata per salvare i dati*, mentre l'altra **è usata solo per salvare le informazioni per la correzione degli errori**.
		Il RAID 2 è un *RAID 0 maggiormente affidabile*, e questo sistema risulta molto efficiente negli ambienti in cui si verificano numerosi errori di lettura/scrittura
		*Vantaggi*
			Elevata affidabilità
			Velocità di lettura molto alta
		*Svantaggi*
			Il numero di dischi usati può essere molto grande.
	**RAID 3**
		Il RAID 3 non è altro che una semplificazione del 2, e la differenza sostanziale è che nel RAID 3 viene usato *un solo disco* per il salvataggio dei codici di correzione. Ciò è possibile sostituendo il codice di Hamming con il *bit di parità*.
		Il RAID 3 usa una divisione *a livello di byte*. 
		Ogni operazione di I/O *richiede di usare tutti i dischi*, e ciò fornisce elevati tassi di trasferimento, ma tuttavia non possono essere eseguite operazioni multiple contemporaneamente, ma solo una ad istante.
		*Vantaggi*
			Prestazioni e caratteristiche simili al RAID 2
			Elevati tassi di trasferimento
			Affidabilità molto alta
			Un solo disco per la correzione errori
		*Svantaggi*
			Unica operazione I/O ad ogni istante
	**RAID 4**
		![[Pasted image 20230418100543.png]]
		Il RAID 4 è analogo al 3, fatta eccezione per il fatto che usa una divisione *a livello di blocchi*, con un disco dedicato alla memorizzazione dei codici di parità. La differenza sostanziale sta nel modo in cui i dati vengono divisi: nel RAID 3 sono divisi per byte, nel RAID 4 per blocchi.
		Per le operazioni di lettura molto grandi (*se richiesti più blocchi*), il RAID 4 si comporta come il 3: l'operazione di I/O richiede di usare un singolo disco, e ciò porta a bassi tassi di trasferimento, ma anche *la possibilità di eseguire più operazioni di I/O contemporaneamente*. Quando si vuole scrivere, sono coinvolti *tutti i dischi*, anche se la scrittura riguarda un singolo blocco, e ciò impedisce al sistema *di effettuare operazioni in parallelo*.
		*Vantaggi*
			Possono essere effettuate più operazioni di I/O contemporaneamente, *se le operazioni di lettura sono piccole*
			Il tasso di trasferimento è elevato, *se le operazioni di lettura sono grandi*
			Affidabilità molto alta
			Un solo disco viene usato per memorizzare i codici per la correzione degli errori.
		*Svantaggi*
			Una sola operazione di scrittura per volta, *sia se grande sia se piccola*
			Il disco di parità è un *bottleneck*, in quanto l'operazione di scrittura impedisce al sistema di effettuare operazioni in parallelo
	**RAID 5**
		![[Pasted image 20230418101123.png]]
		Il RAID 5 è uguale al 4, tranne per il fatto che *i codici di parità sono distribuiti su tutti i dischi*. In questo modo, se l'operazione di scrittura interessa un singolo blocco, *il sistema ha comunque la possibilità di effettuare altre operazioni di scrittura **in parallelo***.
		Per quanto riguarda la lettura, è svolta esattamente come nei RAID 3 e 4:
			*Operazioni di lettura grandi portano a tassi di trasferimento elevati, **ma all'impossibilità di effettuare operazioni in parallelo***
			*Operazioni di lettura piccole portano a bassi tassi, **ma alla possibilità di effettuare operazioni in parallelo***
		*Vantaggi*
			Possibilità di scritture in parallelo se ciò richiede un singolo blocco, *quindi niente bottleneck dal disco di parità*
			Possibilità di effettuare letture in parallelo se richiedono *un solo blocco*
			Alti tassi di trasferimento se le operazioni di I/O richiedono *più blocchi*
			Un solo disco è usato per memorizzare i codici di parità
		*Svantaggi*
			Possibilità di eseguire una sola operazione di I/O in ogni istante *se richiesti più blocchi*
			*Difficile da implementare*
	**RAID 6**
		![[Pasted image 20230418101543.png]]
		Un RAID 6 usa una divisione a blocchi *con i dati di parità distribuiti due volte fra tutti i dischi*. Risulta più ridondante del 5 e il throughput è *leggermente più alto* del 5, a causa del disco in più.
	*RAID IBRIDI*
		Le configurazioni ibride che usano le caratteristiche del RAID 0 e 1 sono spesso usate in pratica per ottenere sia elevati tassi di trasferimento sia elevata affidabilità. La differenza fra il **RAID 0+1** e il **RAID 1+0** è la *diversa disposizione di ogni sistema RAID*.
		**RAID 0+1**
			![[Pasted image 20230418102153.png]]
			In questa situazione, si effettua prima lo striping, *cioè si alternano i dati sui diversi dischi*, e poi *si copiano gli stessi dati su un altro disco*, come nel RAID 1. La sequenza di passi è sostanzialmente *RAID 0* $\implies$ *RAID 1*
		**RAID 1+0**
			![[Pasted image 20230418102313.png]]
			In questa situazione, si copiano prima gli stessi dati su un altro disco, come nel RAID 1, e poi si alternano su dischi diversi. La sequenza di passi è sostanzialmente *RADI 1* $\implies$ *RAID 0*

**PRINCIPI DEL SOFTWARE DI I/O**
---
*Sviluppo Software I/O*
	*Indipendenza dal dispositivo fisico*
		Un concetto chiave nel progetto di SW I/O è quello di *rendere indipendente il codice dal tipo di dispositivo*, cioè non si dovrebbe specificare in anticipo il dispositivo stesso.
	*Denominazione Uniforme*
		Strettamente correlato al precedente è il problema della *denominazione uniforme*. Il nome di un file o di un dispositivo dovrebbe essere semplicemente *una stringa di caratteri o un numero intero*, e non dovrebbe in alcun modo dipendere dal dispositivo.
	*Trattamento degli errori*
		Un altro concetto fondamentale è quello del *trattamento degli errori*, che dovrebbero essere trattati *quanto più vicino all'HW possibile*.
	*Trasferimento Sincrono*
		La maggior parte dell'I/O è *asincrono*: la CPU fa partire il trasferimento e svolge altri compiti, finchè non arriva l'interruzione di *terminazione I/O*, ma i programmi utente sono più facili da scrivere se *le operazioni I/O sono **sincrone***: dopo una read, il programma viene automaticamente sospeso finchè i dati da leggere non sono disponibili.
	*Dispositivi dedicati/condivisibili*
		Alcuni dispositivi, *come i dischi*, possono essere condivisi, cioè *usati da più dispositivi contemporaneamente*, mentre altri, *come i dispositivi a nastro*, devono essere usate *da un processo per volta*.

**I/O PROGRAMMATO**
	Nell'I/O programmato, *il lavoro è assegnato alla CPU*. In questo tipo di I/O, quando un programma utente vuole effettuare un'operazione di I/O, *deve usare una system call* per richiamare l'attenzione del kernel, che *eseguirà operazioni al suo posto*. Durante tutta l'operazione, *il processore sarà occupato*, e non avrà la possibilità di eseguire altri processi.
	Questo tipo di comportamento è detto **attesa attiva**, o *polling*, e comporta un utilizzo *a tempo pieno* della CPU, che durante l'elaborazione di un'operazione di I/O resta impegnata per tutto il tempo. Ciò è inefficiente, perchè si spreca CPU, soprattutto in sistemi complessi, che richiedono molte operazioni di I/O.
**INTERRUPT-DRIVEN I/O**
	Nell'I/O *guidato da interruzioni*, viene effettuata una system call per richiamare l'attenzione del kernel. *Il processore è parzialmente condiviso*, infatti ogni volta che il dispositivo di I/O coinvolto entra nell'operazione, *viene generato un interrupt*, per permettere alla CPU di eseguire altre operazioni.
**DMA-I/O**
	Un ovvio svantaggio dell'I/O ad interruzioni è che si ha uno spreco di tempo di CPU ogni volta che viene generata un'interruzione. Usando una stampante, *viene generato un interrupt ad ogni carattere*.
	Una soluzione è quella di usare il DMA:
	Quando avviene una richiesta di I/O, la CPU avvia il modulo DMA indicandogli le seguenti informazioni:
		*Tipo Operazione* **usando linea di controllo CPU-DMA**
			Se si tratta di una lettura o di una scrittura
		*Indirizzo Dispositivo* **usando le linee dati**
			Ovvero l'indirizzo del dispositivo di I/O coinvolto nell'operazione.
		*Posizione iniziale memoria* **usando le linee dati**, *memorizzata nel DMA nel modulo indirizzi*
			L'indirizzo di partenza dei dati da scrivere/leggere
		*Numero di parole* **usando le linee dati**, *memorizzata nel DMA nel data count register*
			Il numero di parole (sostanzialmente di byte) da leggere o scrivere
	A questo punto, il processore può eseguire altre operazioni. In sostanza, il DMA è I/O programmato, ed è lui a svolgere le operazioni, invece che la CPU.
	Il controllore del DMA è più lento della CPU, e se il controllore non è in grado di far andare il dispositivo a velocità massima, o se la CPU non ha nulla da fare nel frattempo, allora *gli altri tipi di I/O possono essere scelte migliori*

*DMA Breakpoint e interrupt*
	La CPU ed il DMA *competono* per l'utilizzo del bus di sistema. Il DMA deve *forzare* la CPU a sospendere temporaneamente le operazioni, cioè *gli ruba un ciclo di bus* (**cycle stealing**). Quando dev'essere svolta un'operazione di I/O, la CPU passa al DMA le quattro informazioni necessarie, ed è il DMA che la porta a termine. Conclusa l'operazione, il DMA genera un interrupt, per avvertire la CPU che è finita.
	I *DMA Breakpoints* sono dei punti in cui la CPU *può essere fermata per rubare un ciclo di bus*. Sono tre i momenti:
	1) Prima del *fetch*
	2) Dopo il *decode*
	3) Dopo l'*execute*
	La differenza sostanziale fra DMA Breakpoints ed interrupt sta nel fatto che *se viene generato un DMA breakpoint* **non viene salvato alcun contesto**.

**DRIVER DI DISPOSITIVO**
	Ogni dispositivo collegato al computer ha bisogno di codice specifico che controlli il dispositivo stesso. Tale codice è il *driver di dispositivo*.
	E' detto driver **l'insieme di procedure che permettono al SO di utilizzare un dispositivo HW senza sapere come funzioni**.
	I driver sono caricati nella procedura di *boot*, oppure quando i dispositivi vengono collegati al PC (*plug and play*)
	Solitamente, i driver sono posizionati al di sotto del SO, ma possono anche essere *di livello utente*, che porterebbe anche il vantaggio di *isolare il kernel dai dispositivi* (**al di sotto del SO è il kernel ad occuparsene**), evitando crash causati dai driver che in genere interferiscono col kernel.
	*Le moderne architetture utilizzano driver installati **all'interno del SO***.
	Perchè l'IOCS fisico possa basarsi su driver di dispositivo, è necessario definire una *struttura dati* che unisce i due.
	Nella *Tabella dei DIspositivi Fisici* (PDT), ogni entrata contiene il nome del driver $DD\_NAME$ e un puntatore ad un'altra struttura, chiamata *Coda di I/O* (IOQ), dove *per ciascuna classe di dispositivi* l'IOCS fisico inserisce la sua *specifica operazione* da effettuare.
	All'inizio della tabella sono contenuti gli indirizzi per ciascuna funzione relativa a ciascun driver di dispositivo che svolge le operazioni di avvio. Quando l'IOCS è richiamato dalla CPU, l'IOCS fisico localizza la specifica periferica nella PDT ed esegue un'operazione generica di *inserimento dettagli* nella IOQ, e *caricamento in memoria*
	![[Pasted image 20230418105339.png]]

**SCHEDULING DEL DISCO**
----
*Scheduling disco*
	Una delle funzioni dell'IOCS e dei driver dei dispostivi è quella di usare lo *scheduling del disco* per eseguire le operazioni di I/O in un ordine tale da *ridurre il movimento delle testine ed il tempo medio d'attesa* delle operazioni. Quindi, al variare del tipo di processo, si influenzano diversamente le prestazioni del sistema. Resta comunque che l'obiettivo comune di tutte le politiche di scheduling è quello di servire il massimo numero di richieste per unità di tempo.
	**FCFS**
		Seleziona l'operazione di I/O con tempo di richiesta inferiore, cioè le richieste vengono servite *in modo sequenziale*. Questa solitamente è la politica peggiore: si ottengono buone prestazioni solo se *molte richieste riguardano settori ravvicinati*.
	**SHORTEST SEEK TIME FIRST**
		La politica SSTF seleziona sempre l'operazione di I/O *con il minor movimento dalla posizione corrente delle testine*. Può essere soggetta a *Starvation*: se il disco verrà usato molto frequentemente, il braccio tenderà a rimanere sempre nella parte vicina alla traccia richiesta correntemente, quindi le altre richieste, relative a tracce più esterne dovranno aspettare molto tempo prima di essere servite.
	**SCAN** *(e LOOK)*
		Questa politica è nota come *algoritmo dell'ascensore*. Muove le testine del disco da un estremo all'altro del piatto, servendo *tutte le richieste che ci sono per la sua strada*, indipendentemente dal loro tempo d'arrivo. Una volta raggiunta l'ultima traccia, cioè l'altra estremità del piatto, la direzione viene invertita, e le nuove richieste vengono servite nella scansione inversa.
		Una variante, la **LOOK**, inverte la direzione delle testine quando non ci sono più richieste di I/O nella direzione corrente. Le prestazioni saranno buone *se vi sono carichi elevati*.
	**C-SCAN** (*e C-LOOK*)
		La *Circular Scan* esegue la scansione come nel normale **SCAN**, ma non esegue mai la scansione inversa, quindi la scansione è ridotta *ad un'unica direzione*. Invece di procedere in direzione inversa, questa politica *sposta le testine sulla posizione di partenza, e ripete la scansione*. La variante **C-LOOK** muove le testine finchè vi sono richieste da eseguire, e quando terminano riparte dalla posizione iniziale.
		Il vantaggio rispetto alle SCAN è che *i tempi d'attesa delle richieste sono più uniformi*
	**N-STEP-SCAN & F-SCAN**
		Sia con SSTF che con SCAN/C-SCAN può succedere che il braccio *non si muova da un certo settore per un lungo periodo di tempo*, e ciò accade se uno o più processi hanno alte frequenze d'accesso ad una particolare traccia. Per evitare tale fenomeno, si possono usare due approcci:
		*N-STEP-SCAN*
			La coda viene divisa in *sottocode*, sulle quali viene applicato lo SCAN, fin quando non sono svuotate. $n$ è il numero di sottocode, quindi se $n=1$ l'algoritmo è identico allo SCAN normale
		*F-SCAN*
			La coda viene suddivisa in due sottocode, di cui la prima viene servita con lo SCAN finchè non si svuota, e le successive richieste vengono poste nella seconda coda, che sarà servita solo dopo che la prima è stata svuotata.
	L'algoritmo SSTF è quello più *naturale*, ed è il più usato. SCAN e C-SCAN hanno le migliori prestazioni nei sistemi con un alto carico di richieste.
	L'algoritmo di scheduling del disco dovrebbe essere implementato come *un modulo separato* del sistema operativo, in modo da poterlo rimpiazzare con un altro se necessario. Sia SSTF che LOOK sono una scelta *ragionevole* come algoritmo di default.
	Per effettuare lo scheduling del disco, è necessaria la formula 
	$t_{hm} = t_{const} + |track_1 - track_2|*t_{pt}$ 
	*Buffering e Blocking record*
		Per migliorare le prestazioni dell'elaborazione di un file all'interno di un processo, un metodo d'accesso ricorre alle tecniche di *buffering* e *blocking* dei record.
		*Buffering*
			Tenta di sovrapporre le attività di I/O e di CPU di un processo. Tale obiettivo è raggiunto in due modi:
			*Prefetching* di un record di *input* in un buffer di I/O
			*Postwriting* di un record di *output* da un buffer di I/O
			Un *buffer* è un'area di memoria utilizzata per mantere temporaneamente i dati coinvolti in un'operazione di I/O.
			Per un file di *input*, la tecnica usa il **prefetching**:
				Mentre il processo è impegnato nell'elaborazione di un dato, viene avviata *un'operazione che legge il dato successivo*, e lo memorizza in un buffer *prima che questo sia richiesto dal processo*. Questa tecnica è quindi capace di *diminuire, o addirittura **eliminare** il tempo d'attesa*.
			Per un file di *output*, usa il **postwriting**:
				Il record *che dev'essere scritto* viene semplicemente *copiato in un buffer* quando il processo esegue un'operazione di scrittura, in modo che l'esecuzione del processo possa proseguire. L'effettiva scrittura è poi eseguita *dal buffer in un momento successivo*.
		*Blocking*
			La tecnica del blocking riduce il numero di operazioni di I/O da eseguire, leggendo o scrivendo molti record in una singola operazione.
			Quando più record vengono letti o scritti insieme, è necessario differenziare l'accesso e l'elaborazione dei dati e come vengono scritti sul dispositivo di I/O:
			*Record Logico*
				E' l'unità di dati utilizzata in un processo per l'accesso e l'elaborazione
			*Record Fisico*
				Chiamato anche *blocco*, è l'unità dei dati utilizzata per il trasferimento da e verso un dispositivo di I/O.
				Il *fattore di blocking* è il numero di record *logici* in uno *fisico*. Si dice che il file **adotta il blocking dei record** se tale fattore è $>1$. Le azioni necessarie per l'estrazione di un record logico da un blocco, in modo che possa essere usato in un processo, sono collettivamente chiamate *azioni di unblocking*.

*Cache del disco e dei file*
	Una tecnica generale per velocizzare l'accesso ai dati consiste nell'utilizzare una gerarchia di memoria composta da una parte della memoria e dai file memorizzati sul disco.
	Il *Caching* è la tecnica di mantenere alcuni file in memoria, in modo che vi si possa accedere senza dover effettuare un'operazione di I/O.
		L'IOCS fisico implementa una *cache del disco* per ridurre il tempo di operazioni di I/O per accedere ai file memorizzati sul disco.
		Un metodo d'accesso implementa una *cache dei file* per ridurre il numero di operazioni I/O durante le operazioni sui file.

--------------------------------------------------------------------------------
**PRATICA SCHEDULING**
---
Utilizzando questa tabella:
![[Pasted image 20230418115433.png]]
E sapendo che :

*Le testine si muovono verso tracce con numeri maggiori*
*Le richieste vengono fatte in tempi diversi*

**Il tempo di decisione equivale al tempo di decisione precedente più il tempo di seek**
$t_{des}[i] = t_{des}[i-1] + t_{seek}[i-1]$ 
La *Head Position* è la posizione della testina sulla traccia precedente.
$seek\_time = |Track_1 - Track_2|$ 

Abbiamo diversi algoritmi di scheduling:
	**First Come First Served**
		Serve le richieste in ordine d'arrivo
	**Shortest Seek Time First**
		Serve le richieste più vicine alla posizione *corrente* della testina
	**LOOK**
		Va da sinistra a destra, e appena non vi sono più richieste, torna indietro e ripete in direzione inversa
	**Circular-LOOK**
		Come la LOOK, ma appena terminata la scansione va alla richiesta con numero di track minore.

![[Pasted image 20230418115933.png]]
![[Pasted image 20230418115947.png]]

----------------------------------------------------------------------------------------
**TEMPO D'ACCESSO NELLO SCHEDULING**
---
Supponiamo che la coda delle richieste di un'entità disco composta da 200 tracce sia la seguente:
$39700 - 304 - 115 - 2600 - 2120 - 270 - 0 -20000$
*Il blocco i-simo è memorizzato nella traccia* $i \mod 200$ 
La testina ha eseguito l'ultimo movimento, portandosi dalla traccia 85 alla traccia 97
Si ipotizzi che:
	Lo spostamento da una traccia ad un'altra richieda tempo medio pari a $40\mu s$ per traccia
	L'inversione della direzione di movimento richieda in media $80\mu s$ 
	La velocità di rotazione sia $7200rpm$
Si vuole determinare il tempo medio richiesto, *complessivamente*, per accedere alle tracce nella coda, usando le politiche *SSTF* , *C-SCAN* e *LOOK*

**SOLUZIONE**
---
Latenza Rotazionale : $L_r = 60/(2*7200) = 4.17ms$ 

Determiniamo la traccia nella quale si trova il blocco ($i \mod 200$)
Blocchi:
$39700 - 304 - 115 - 2600 - 2120 - 270 - 0 -20000 \implies 100-104-115-0-120-70-121-200-160-0$

Possiamo quindi applicare gli algoritmi

*SSTF*
	$97-100-104-115-120-121-160-200-70-0$
	Le distanze fra le tracce ($|Track_1-Track_2|$) valgono:
		$3-4-11-5-1-39-40-130-70$
	Il tempo d'accesso è quindi:
		$t_a = (303*40\mu s)+80\mu s+(9*4.17ms) = 12.12ms + 0.08ms + 37.53 ms = 49.73ms$

*C-SCAN*
	$97-100-104-115-120-121-160-200-0-70$
	Le distanze fra le tracce valgono:
		$3-4-11-5-1-39-40-200-70$
	$t_a = (373*40\mu s)+80\mu s+(9*4.17ms) = 14.92ms+0.08ms+37.53ms = 52.53ms$

*LOOK*
	$97-100-104-115-120-121-160-200-70-0$
	Le distanze fra le tracce valgono:
		$3-4-11-5-1-39-40-130-70$
	$t_a = (303*40\mu s)+80\mu s+(9*4.17ms) = 12.12ms+0.08ms+37.53ms = 49.73ms$

-----------------------------------------------------------------------------------------

FINE TEORIA

----------------------------------------------------------------------------------------

