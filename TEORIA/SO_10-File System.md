**File System e Memoria di Massa**
---
*File System*
	Durante l'esecuzione, un processo può memorizzare nella RAM solo una parte di informazioni, e la restante è memorizzata su dischi e/o supporti esterni. Quella parte del SO che si occupa complessivamente dei file è detta **File Sstem**. Un amministratore di sistema si aspetta che un file system assicuri un uso efficiente dei dispositivi di I/O e contribuisca alle alte prestazioni del sistema. Gli utenti, invece, richiedono efficienza nella creazione e manipolazione dei file e nella condivisione degli stessi con altri utenti del sistema. Inoltre, richiedono che il file system implementi caratteristiche di protezione, sicurezza ed affidabilità in modo che i propri file non siano soggetti ad accessi illegali.
	Gli obiettivi principali di un file system sono:
		*Accesso conveniente e veloce ai file*
		*Memorizzazione affidabile dei file*
		*Condivisione file con altri utenti*
	Per raggiungere tali obiettivi in maniera efficace, il file system è strutturato in due strati:
		I *moduli del file system* che si occupano della condivisione, protezione e affidabilità dei file
		L'*IOCS* che si occupa dell'implementazione delle operazioni sui file
	*Elaborazione dei file*
		I moduli del file system vedono un file come *un insieme di dati*:
			Di cui è proprietario un utente
			Che può essere condiviso da un insieme di utenti autorizzati
			Che dev'essere memorizzato per un tempo esteso in modo affidabile
		Inoltre, un file system deve permettere ad un utente di poter rinominare un file senza che ciò vada in conflitto con i nomi dei file degli altri utenti.
		L'*IOCS* vede un file come contenitore di dati:
			Cui è necessario accedere velocemente
			Che sono memorizzati su un dispositivo di I/O che dev'essere utilizzato in maniera *efficiente*
	Un File System consiste di due tipi di dati : i dati *contenuti nei file* ed i dati *usati per accedere ai file*.
	I dati contenuti nei file vengono chiamati *dati*, mentre quelli per accedervi sono chiamati *metadati*
	A livello di linguaggio di programmazione, un file è un oggetto che possiede *attributi*, che descrivono l'organizzazione dei suoi dati, ed il meto d'accesso agli stessi. Un programma contiene le istruzioni per l'elaborazione dei file.
	Col termine *elaborazione dei file*, si indica la sequenza di operazioni di:
		Apertura del file
		Lettura/Scrittura dati da/su file
		Chiusura del file
	![[Pasted image 20230413113833.png]]
	Ogni directory contiene elementi che descrivono alcuni file:
	Nome proprietario, posizione nel disco, il modo in cui i dati sono organizzati, permessi d'accesso,...
	Un File System fornisce diversi tipi di file: un file può essere
	*Strutturato*
		Contiene **record** di dati
	*Non strutturato*
		Detto anche *stream* di dati
	Ogni tipo di file fornisce la sua visione *astratta* dei dati in un file, che chiameremo *vista logica*
	L'*IOCS* organizza i dati in un file di I/O *relativamente al tipo di file*. Questa è denominata *vista fisica* del file. L'IOCS organizza la *mappatura* fra vista logica e vista fisica dei file. Inoltre, fornisce un'organizzazione che velocizza l'attività di elaborazione di un file.
	*Operazioni sui file*
		Come detto, abbiamo due tipi di file:
		*File Strutturato*
			Contiene *record* di dati, ovvero collezioni di campi, ed un campo contiene un *singolo elemento* dei dati. Si assume che ogni record contenga un campo *chiave*, il cui valore è unico nel file, cioè *non esistono due record aventi stessa chiave*.
		*File Orientato allo Stream di byte*
			E' un file che non contiene nè record nè campi, ma viene visto semplicemente come una sequenza di byte dai processi che lo usano
	*Attributi di un file*
		Un attributo di un file è un'importante caratteristica di un file, sia per gli utenti che per il file system.
		Ogni file ha un nome, usato come riferimento. Un file ha anche altri attributi, che tipicamente comprendono:
			*Nome*
				Nome *simbolico* del file, l'unica informazione in forma umanamente leggibile
			*Identificatore*
				Un numero che identifica il file nel file system
			*Tipo*
				Descrive il tipo di file (Regolare, Link, ...)
			*Dimensione*
				Definisce la dimensione del file, dall'inizio alla fine
			*Posizione sul disco*
				Contiene il percorso del file
			*Protezione*
				Contiene le informazioni per l'accesso in lettura/scrittura/esecuzione
		Le informazioni sui file sono conservati nella struttura di directory. Durante l'elaborazione di un file, il file system usa i suoi attributi per localizzarlo e verificare che ogni operazione fatta su di esso sia coerente coi suoi attributi.
		![[Pasted image 20230413131559.png]]

**ORGANIZZAZIONE FILE**
---
*Fondamenti ed operazioni d'accesso*
	Un'organizzazione dei file è una combinazione di due caratteristiche: un modo per organizzare i record in un file, ed un modo per accedervi.
	I due metodi fondamentali di accesso sono l'accesso *sequenziale*, secondo cui l'accesso avviene *nell'ordine in cui si trovano nel file*, e l'accesso *casuale*, secondo cui si può accedere ai record *in qualunque ordine*.
	Chiamiamo *pattern di accesso al record* l'ordine in cui un processo accede ai record di un file. Le azioni di elaborazione saranno eseguite efficientemente solo se le caratteristiche del dispositivo di I/O si prestano ad un metodo piuttosto che un altro.
	L'organizzazione dei file *viene scelta in base alle caratteristiche del dispositivo di I/O* che si usa, in modo da fornire un accesso efficiente. Un hard disk può accedere direttamente, tramite indirizzo, a qualsiasi record, mentre un drive a nastro solo sequenzialmente. Gli accesso sono implementati da un modulo dell'*IOCS* detto *metodo di accesso*.
	*Organizzazione Sequenziale*
		Le informazioni sono memorizzate in ordine, crescente o decrescente, in base al campo *chiave*. Di conseguenza, l'elaborazione di queste informazioni supporta solo due operazioni:
			1) Legge l'informazione (*record*) successiva/precedente
			2) Salta l'informazione (*record*) successiva/precedente
		Un file ad accesso sequenziale viene usato nelle applicazioni se i suoi dati possono essere *pre-ordinati* convenientemente in un ordine.
	*Organizzazione Diretta*
		L'organizzazione diretta fornisce efficienza e convenienza, perchè permette di accedere alle informazioni (*record*) in ordine casuale. Il metodo d'accesso si rifà a quello dei dischi.
		In questa organizzazione, occorre generare l'indirizzo del record usato dalla periferica. Se il file è memorizzato su un HD, la trasformazione genera un indirizzo $(num_{traccia},num_{record})$ in modo che *le testine dell'HD vengano posizionate su $num_{traccia}$ prima che venga eseguita l'operazione su* $num_{record}$.
		Quest'organizzazione presenta due svantaggi rispetto alla sequenziale:
			1) Il calcolo dell'indirizzo genera overhead, e consuma tempo di CPU
			2) Una parte della memoria viene sprecata, in quanto vengono memorizzati meno dati sulla traccia esterna del disco
	*Organizzazione Indicizzata*
		In quest'organizzazione, un *indice* aiuta a determinare la posizione di un record a partire dal valore della sua chiave.
		*Pura*
			Esiste un indice per ogni record.
		L'indice è costituito dalla coppia $(valore\_chiave,indirizzo\_disco)$. Per poter accedere ad un record con chiave k, viene trovato l'elemento indice contenente k tramite la *ricerca per indice*, e si utilizza l'indirizzo del disco annotato nell'elemento trovato per accedere al record.
	*Organizzazione Sequenziale Indicizzata*
		E' un'organizzazione ibrida che combina gli elementi delle organizzazioni indicizzata e sequenziale, cioè *esiste un indice per ogni sequenza del disco*. Per accedere ad un record, si cerca un indice che punta alla sezione del disco che può contenere il record, e poi si effettua la ricerca sequenziale per trovarlo.
		Quest'organizzazione richiede un indice molto più piccolo rispetto all'indicizzazione pura, poichè l'indice contiene  elementi *solo per alcuni valori della chiave*
		Per un file di grandi dimensioni, l'indice può contenere un gran numero di elementi, per cui i tempi richiesti per la ricerca possono diventare molto lunghi. Si può così usare una **gerarchia di indici**:
		Un indice di livello alto può essere usato per ridurre il tempo di ricerca, e un elemento nell'indice di livello più alto punta ad una *sezione* dell'indice

*Metodi di Accesso*
	Un metodo d'accesso è un modulo dell'*IOCS* che implementa gli accessi ad una classe di file che utilizza *una specifica organizzazione*. Il tipo di accesso da usare dipende dall'organizzazione del file.
	E' possibile usare due tecniche di programmazione dell'I/O per rendere più efficiente l'accesso, ovvero:
	*Buffering dei record*
		In questa tecnica, il metodo di accesso legge i record di un file *prima che siano effettivamente richiesti* dal processo, e li memorizza temporaneamente in aree di memoria dette *buffer*, finchè non sono richiesti. Lo scopo di questa tecnica è quello di eliminare l'attesa per il completamento delle operazioni di I/O
	*Blocking dei record*
		Il metodo d'accesso legge o scrive sempre *grandi blocchi di dati*, che contengono diversi record di file, da o verso un dispositivo di I/O. Questa caratteristica *riduce il numero totale di operazioni di I/O* richieste per elaborare un file, migliorando di conseguenza *l'efficienza nell'elaborazione di un file da parte di un processo*.
		Il blocking, inoltre, migliora *l'utilizzo* del dispositivo di I/O e il suo *throughput*.

**DIRECTORY**
---
*Importanza nel FS*
	Le directory ricoprono un ruolo fondamentale nel FS, contenendo le *informazioni relative a gruppi di file*. Ogni elemento in una directory contiene gli attributi di un file.
	![[Pasted image 20230414115817.png]]
	I campi *open count* e *lock* sono usati quando si apre un file in maniera *concorrente*. Il campo lock viene usato quando un processo richiede l'uso *esclusivo* del file.
	Il campo *flag* è usato per differenziare i diversi tipi di file in una directory (*D directory*; *L link*; *M file system*)
	Il campo *misc_info* invece contiene informazioni aggiuntive, come il proprietario, la data di creazione e di ultima modifica
	*Struttura a due livelli*
		Una directory contiene i file appartenenti a più utenti, quindi deve garantire due importanti prerogative
		*Libertà nella scelta del nome*
			Possibilità per gli utenti di dare gli stessi nomi ai propri file
		*Condivisione dei file*
			Concedere ad altri utenti la possibilità di accedere ai propri file
		![[Pasted image 20230414120222.png]]
		La Directory **master** contiene informazioni relative alle directory utente di *tutti gli utenti* del sistema. Ogni elemento della master è una coppia che consiste di un ID utente e di un puntatore ad una directory utente.
		La Directory **utente** contiene elementi che descrivono i file appartenenti ad un utente
		Questa soluzione richiede che i nomi siano unici *solo all'interno dell'area del singolo utente*. Una tale organizzazione garantsce l'accesso al file corretto anche se nel sistema esistono molti file con lo stesso nome.
		Tuttavia, l'uso delle *User Directory* ha lo svantaggio che impedisce agli altri utenti di condividere i loro file con altri. Per raggiungere tale obiettivo, sono necessare *istruzioni speciali* (come chmod), che permettono agli utenti di impostare i permessi d'accesso al file per gli altri utenti del sistema. Per fare ciò, bisogna controllare i permessi del file, contenuti nel campo *prot_info*
	*Struttura ad albero*
		Un approccio più flessibile è quello dell'**albero delle directory**
		![[Pasted image 20230414122307.png]]
		In questa struttura, il file system fornisce all'utente una directory chiamata *root* che contiene la *directory home* di ciascun utente, ovvero una directory che ha lo stesso nome dell'utente. Un utente ha la possibilità di creare file o directory nella sua home, con la possibilità di organizzare le proprie informazioni in una struttura basata su diversi livelli di *sottodirectory*. Ad ogni istante, un utente *si trova* in una specifica directory, chiamata *directory corrente*. Quando l'utente vuole aprire un file, tale file viene cercato nella corrente. Al login, il SO permette all'utente di operare solo nella sua home. In questa organizzazione, i nomi dei file devono essere univoci, per cui si utilizza un *path* per identificarlo in maniera univoca. I path per localizzare un file a partire dalla directory corrente sono detti *relativi*. Il path **assoluto** di un file parte dalla *root*, e i file aventi stesso nome, ma in diverse directory, differiscono per il loro *path assoluto*.
	*Struttura a grafi*
		In un albero delle directory, ogni file eccetto la root ha esattamente una directory genitore. Una struttura del genere separa totalmente i file di utenti differenti, non ammettendo la condivisione di file e directory tra più utenti.
		Per risolvere tale problematica, si possono organizzare le directory come un *grafo aciclico*. Questa organizzazione permette di avere sottodirectory e file *condivisi*, senza necessariamente avere copie. In questa struttura, un file può avere più genitori, per cui un file condiviso può essere puntato dalle directory di tutti gli utenti che vi hanno accesso.
		Un metodo molto diffuso per implementare la struttura a grafo è quella di utilizzare i **link**, un nuovo elemento di directory che consiste in un puntatore ad un file o directory.
	La *ricerca di informazioni* o file è l'operazione più frequente sulle directory. Altre operazioni sono la *creazione*/*cancellazione* di file o directory, l'*aggiornamento* degli elementi relativi ai file quando chiusi dai programmi, l'*elencazione del contenuto*, o la *cancellazione* della directory stessa.
	*Cancellazione*
		L'operazione di cancellazione della directory risulta complessa avendo la struttura a grafo, poichè un file può avere più genitori. Un file è effettivamente cancellato *se ha un solo genitore*, altrimenti **viene reso inaccessibile dalla directory cancellata**. Per semplificare tale operazione, il FS associa ad ogni file un contatore di link, che è impostato a uno alla creazione del file, e incrementato ogni volta che una directory lo punta e decrementato di uno quando viene rimosso un link. Il file viene definitivamente rimosso dal FS se il contatore arriva a zero.
	Per avere maggiore efficienza nella ricerca all'interno delle directory, sono usate organizzazioni che utilizzano le hash table o gli alberi B+.

*Montaggio File System*
	In un sistema operativo possono coesistere diversi File System, ognuno creato su un disco *logico*, ovvero **su una partizione del disco**. I file contenuti in un file system sono utilizzabili *solo quando il FS è **montato***.
	L'operazione di *mounting* connette il File System alle directory del sistema. Tale unione dura finchè il file system non è smontato o il sistema viene riavviato.
	L'operazione di *unmounting* disconnette il File System.

*Protezione dei file*
	Il SO deve anche implementare la protezione dei file, in particolare dare la possibilità ad un utente di voler condividere i suoi file *solo con una parte degli utenti*, che viene detta **condivisione controllata**, ed è implementata specificando *quali utenti* possono accedere al file, e *in che modo*. Queste informazioni sono tenute nel campo *prot_info*.
	L'informazione relativa alla protezione è solitamente memorizzata nella forma di una *access control list*, dove ogni elemento è una coppia $(nome\_utente,lista\_privilegi)$. La dimensione dell'ACL dipende dal numero di utenti e dal numero di privilegi definiti nel sistema. Per ridurne le dimensioni, è possibile *specificare un'ACL per ogni classe di utenti*

**MEMORIA DISCO**
---
*Allocazione spazio su disco*
	Un disco può contenere diversi FS, ognuno nella sua partizione dedicata. Il File System ha informazioni sulla partizione in cui è presente un file, ma il sistema *IOCS* no, per cui l'allocazione dello spazio sul disco è gestita dal file system.
	*Allocazione Contigua*
		I primi file system usavano il metodo di allocazione contigua della memoria, allocando una singola area di memoria ad ogni file, al momento della creazione.
		In questa allocazione, ogni file occupa un insieme di blocchi *contigui* sul disco, quindi risulta particolarmente semplice, dovendo conoscere solo il blocco iniziale e la lunghezza del file.
		Lo svantaggio è quello di creare *frammentazione esterna*, potendo generare aree di memoria troppo piccole per essere riutilizzate, ma anche *frammentazione interna*, poichè il FS era progettato per allocare *memoria extra* sul disco, per consentire al file di crescere.
	*Allocazione Non Contigua*
		I moderni FS adottano l'allocazione non contigua, che consiste nell'allocazione di una parte di memoria sul disco *su richiesta*, ovvero alla creazione di un file, o quando la sua memoria aumenta.
		Un file system deve risolvere tre problematiche per implementare questo approccio:
			*Gestione dello spazio libero*
				Deve tenere traccia dello spazio libero sul disco ed allocarlo quando un file richiede un nuovo blocco
			*Evitare movimenti eccessivi della testina*
				Deve garantire che un file non sia "sparpagliato" in diverse parti del disco, poichè ciò causerebbe un movimento eccessivo delle testine magnetiche del disco durante l'elaborazione del file.
			*Accesso ai dati del file*
				Deve mantenere le informazioni sui file presenti nel disco trovare i blocchi di memoria che lo contengono
		L'allocazione non contigua può essere *concatenata* o *indicizzata*
		*Allocazione NC Concatenata*
			Quest'organizzazione risolve il problema della frammentazione esterna, e quello della dimensione dei file. Tuttavia, in mancanza di una *File Allocation Table*, l'assegnazione concatenata non è in grado di sostenere un efficiente accesso diretto, *poichè i puntatori ai blocchi sono sparpagliati*, con i blocchi stessi, per tutto il disco, *e si devono recuperare **in ordine***. Ogni file è rappresentato come *una lista concatenata di blocchi*, ognuno avente due campi al suo interno : *Dati* e *Metadati*, che è un campo di tipo link e punta al prossimo blocco.
			![[Pasted image 20230414144948.png]]
			Il campo *Info di posizione* punta al primo blocco del file sul disco. Agli altri blocchi vi si accede *seguendo i puntatori dei vari blocchi*. L'ultimo blocco del disco contiene un puntatore *null*.
			Lo spazio libero sul disco è rappresentato da una *free list*, in cui ogni blocco libero contiene un puntatore al successivo. Alla richiesta di un blocco, esso viene estratto dalla free list per essere aggiunto alla lista dei blocchi del file. Per cancellare un file, *la lista di blocchi del file viene semplicemente aggiunta alla free list*.
			Il vantaggio principale di questa allocazione è che *è sufficiente memorizzare in ogni elemento della directory solamente l'indirizzo del primo blocco* sul disco. Questo porta anche ad una lettura sequenziale semplice da effettuare, tuttavia vi sono anche degli svantaggi. L'accesso diretto è estremamente lento, perchè per arrivare al blocco $n$ bisogna per forza attraversare gli $n-1$ blocchi che lo precedono. Un ulteriore svantaggio riguarda lo *spazio richiesto per i puntatori*.
			La soluzione più comune a questo problema è il riunire diversi blocchi contigui in un *cluster* e assegnare i gruppi di blocchi anzichè i singoli.
			Un altro problema riguarda l'*affidabilità*. Se si danneggiasse il campo metadati, ovvero il puntatore, i dati successivi potrebbero essere persi. Ci sono delle soluzioni, come l'uso delle liste *doubly linked*, che però sono onerose.
		*File Allocation Table*
			Una FAT viene mantenuta in memoria, e ha un elemento per ogni blocco del disco. Per un blocco allocato ad un file, questo elemento consiste nell'indirizzo del blocco successivo. In questo modo, il blocco e il suo elemento nella FAT costituiscono una coppia che contiene la stessa informazione contenuta nel blocco nell'allocazione concatenata.
			![[Pasted image 20230414145903.png]]
			La FAT può anche essere usata per memorizzare l'informazione relativa allo *spazio libero*. La lista dei blocchi liberi è costruita nello stesso modo in cui viene costruita la lista dei blocchi di un file. In alternativa, per ogni blocco libero può essere usato un valore speciale *free*, che indica che il blocco è libero.
			Il vantaggio della FAT è che garantisce maggiore *affidabilità*, rendendo meno pericoloso il danneggiamento di un blocco contenente i dati del file.
			Gli svantaggi sono:
				Il danneggiamento del blocco che conserva la FAT ha conseguenze disastrose
				Le prestazioni sono peggiori, poichè è necessario accedere alla FAT per conoscere l'indirizzo del blocco successivo.
		*Allocazione Indicizzata*
			Questa tecnica risolve il problema dell'accesso diretto dell'allocazione *concatenata*, raggruppando tutti i puntatori in una sola locazione, il blocco *indice*.
			Nell'allocazione indicizzata, si mantengono tutti i puntatori ai blocchi di un file in una tabella indice chiamata *File Map Table*. Ogni file ha il proprio blocco indice. Nella sua forma più semplice, la FMT è un *array di indirizzi di blocchi del disco*. Ogni blocco ha un solo campo, quello *dati*. L'i-simo elemento del blocco indice punta all'i-simo blocco del file.
			![[Pasted image 20230414150519.png]]
			Il campo *info di posizione* dell'elemento della directory relativo al file contiene l'indirizzo dell'FMT. Una volta creato il file, tutti i puntatori sono impostati a *null*. Quando le dimensioni del file crescono, viene localizzato un file sul disco e l'indirizzo di questo blocco viene aggiunto all'FMT.
			*Vantaggi*
				Quest'allocazione permette di accere *diretamente* ad un blocco dalla FMT, *senza avere frammentazione esterna*. Inoltre, l'affidabilità è migliorata, in quanto il danneggiamento di un elemento della FMT non compromette l'intero file, ma solo una sua parte.
			*Svantaggi*
				Il principale problema è la *dimensione del blocco indice*, cioè la dimensione dell'FMT. Se essa è troppo piccola, non può gestire abbastanza puntatori per un file di grandi dimensioni, per cui è necessario un meccanismo per gestire tale situazione.
			*Indice a più livelli*
			![[Pasted image 20230417093753.png]]
			Una soluzione è quella di usare un blocco a più livelli, che non contiene dati. Per accedere ai blocchi che li contengono, prima si accede ad un elemento della FMT e otteniamo l'indirizzo del blocco indice, che punta ai blocchi dati. Successivamente, accediamo ad un elemento del blocco indice per ottenere l'indirizzo del blocco dati.
		*Organizzazione Ibrida*
			![[Pasted image 20230417094153.png]]
			Quest'organizzazione ibrida della FMT include sia le caratteristiche dell'allocazione classica sia dell'allocazione indicizzata multilivello. Ad esempio, i primi n elementi dell'FMT puntano a blocchi dati, come nell'allocazione indicizzata, mentre gli altri elementi puntano a blocchi indice.
			*Vantaggi*
				Il vantaggio di questa organizzazione è che i file piccoli sono accessibili in maniera efficiente
			*Svantaggi*
				Lo svantaggio è che i file medio-grandi soffrono di un parziale degrado delle prestazioni d'accesso, causato dai blocchi d'indicizzamento.

**AFFIDABILITA' DEL FILE SYSTEM**
---
*Definizione di Affidabilità*
	L'affidabilità è *il grado di funzionamento corretto del file system*, anche al verificarsi di malfunzionamenti (Corruzione dati nei blocchi, fault di sistema..).
	I due aspetti principali dell'affidabilità sono:
	*Garantimento correttezza operazioni*
		Il file system deve garantire sempre la correttezza delle operazioni sui file al suo interno, come creazione, cancellazione e aggiornamento
	*Prevenzione perdita dati*
		Il file system deve garantire che i dati contenuti nei file non vengano mai persi
	Il primo riguarda la consistenza e la correttezza dei *metadati*, il secondo riguarda la consistenza e correttezza dei *dati*.
	Quando si parla di affidabilità bisogna tenere conto dei *fault* e dei *failure*.
	*Fault/Failure*
		Un fault (*Page Fault*, *fault di sistema*) è un malfunzionamento di una parte del sistema. Ad esempio, la corruzione dei dati all'interno di un blocco di memoria è un fault.
		Un failure è invece un *comportamento erroneo*, spesso anche dovuto ad un fault, ma può essere indipendente.
		Per gestire l'affidabilità del SO si usano due strategie:
		*Recupero*
			Nel momento in cui avviene un **fault**, si *ripristinano i dati* a prima che accadesse tale fault
		*Tolleranza ai guasti*
			Anche se si verifica un **fault**, il sistema è in grado di continuare ad operare, *utilizzando risorse ridondanti*

*Journaling File System*
	Durante l'esecuzione, un file system mantiene in memoria una parte di file e metadati, in particolare **file control block**, **file map table** e **free list**.
	Quando l'esecuzione di un file system viene terminata dall'utente, il FS *copia tutti i dati e metadati dalla RAM sul disco*, in modo che la copia sul disco sia *completa e consistente*. Tuttavia, quando il sistema viene spento all'improvviso (*ad esempio premendo l'interruttore dell'alimentatore*), il FS non ha la possibilità di ricopiare i dati, per cui tale spegnimento viene detto *sporco* (**DIRTY**), perchè avremmo dei dati scritti non memorizzati. Questo tipo di spegnimento causa una *perdita dei dati e metadati in memoria*
	Tradizionalmente, i FS usano *tecniche di ripristino* per proteggersi contro la perdita di dati e metadati, poichè molto semplici da implementare. La creazione di copie di backup comportava un piccolo overhead durante il normale funzionamento del sistema, ma al verificarsi di un errore l'overhead per la sua gestione era molto elevato, ed *il sistema non era utilizzabile durante il ripristino*.
	Un FS moderno utilizza tecniche di *fault tolerance*, in modo da poter riprendere l'esecuzione velocemente dopo uno spegnimento improvviso. Un **Journaling File System** implementa la fault tolerance mantenendo un *journal*, dove vengono salvate le azioni che il FS si *accinge a fare*, prima di attuarle effettivamente. Al verificarsi di uno spegnimento improvviso, le azioni non ancora eseguite sono salvate nel FS come "non fatte". Al riavvio, il SO nota che sono *non fatte*, e le esegue, garantendo così *la consistenza e correttezza dei dati e metadati*.
	L'uso di tecniche di fault tolerance genera un overhead elevato. Per questo motivo, il JFS offre diverse modalità journaling. Un amministratore di sistema può scegliere una modalità journaling da adattare al tipo di affidabilità necessaria nell'ambiente di elaborazione.
	![[Pasted image 20230417101512.png]]

*File System Virtuale*
	Un sistema operativo fornisce un *Virtual File System*, che facilita l'esecuzione simultanea di diversi file system. In questo modo, ogni utente può utilizzare il FS che preferisce. Un processo invoca il VFS utilizzando comandi generali per l'accesso ai file, ed il livello VFS *ridireziona* il comando al File System appropriato
	![[Pasted image 20230417102837.png]]
	Ciò è implementato da un *layer VFS*, situato fra un processo ed un FS. Il layer ha due interfacce:
	*Interfaccia con il processo*
		Fornisce le funzionalità per eseguire le operazioni sui file e le operazioni mount/unmount
	*Interfaccia con il FS*
		Serve per determinare a quale FS appartiene il processo, invocando le systemcall dello specifico FS.
	Il VFS risulta molto utile nei dispositivi I/O *rimuovibili*, come penne USB, in quanto consente all'utente di montare il FS presente in questi dispositivi *nella sua directory corrente*, e accedere ai file *senza preoccuparsi che siano memorizzati in modo differente*.

**UNIX FS**
---
*Inode (**index node**)*
	Le informazioni che costituiscono l'elemento della directory relativo ad un file, sono in Unix divise fra l'elemento della directory e l'*i-node* del file.
	L'elemento della directory contiene solo *il nome ed il numero di i-node*, mentre la maggior parte delle informazioni è racchiusa nel suo i-node.
	La struttura dati i-node viene mantenuta *sul disco*, e contiene le seguenti informazioni:
		*Tipo* del file (Directory, link o file speciale)
		*Numero di link* al file
		*Dimensione* del file
		*ID dispositivo* su cui è memorizzato
		*Numero Seriale* dell'i-node
		*ID utente+gruppo proprietario* $(UID,Group\_ID)$
		*Permessi d'accesso* $(rwx,rwx,rwx)$
		*Info su allocazione*
	La divisione dell'elemento fra directory e i-node *facilita la cancellazione dei link*. Un file può essere cancellato se il numero dei suoi link arriva a 0.
	In UNIX, in memoria vengono contenuti gli i-node, i *descrittori di file* e le *strutture file*. Una struttura file contiene due campi, la *posizione di un file aperto* e *un puntatore al suo i-node*.
	In questo modo, un i-node ed una struttura file insieme contengono *tutte* le informazioni necessarie per accedere al file. I descrittori di file (*fd*) sono memorizzati in una tabella per ogni processo.
	*Allocazione dello spazio su disco*
		UNIX utilizza l'allocazione indicizzata per lo spazio sul disco, con una dimensione del blocco di 4KB. Ogni file ha una FAT memorizzata nel proprio i-node. Gli i-node contengono, oltre ai campi precedenti, altri *15 elementi*, di cui 12 sono *indirizzi indiretti* e 3 sono indirizzi *diretti*, che vengono allocati su richiesta.
		I primi 12 *puntano direttamente* ai blocchi dati, mentre gli altri 3 puntano ai blocchi indice, in particolare:
			Il 13° punta ad un *blocco indiretto di primo livello*, un blocco che ha puntatori ai blocchi dati
			Il 14° punta ad un blocco *indiretto di secondo livello*
			Il 15° punta ad un blocco indiretto di *terzo livello*, ma non viene quasi mai usato.
		In questo modo, la dimensione totale del file può arrivare fino ad un massimo di $2^{42}$ byte, ma visto che gli indirizzi sono a 32 bit, la dimensione è limitata a $2^{32}-1$ byte.
		Il numero di indirizzi contenuti in ogni blocco *indiretto* dipende dalla dimensione dei singoli blocchi e dalla dimensione degli indirizzi.
	*Superblocco*
		La radice di un FS è detta **superblock**. Una parte del disco, solitamente quella iniziale, viene usata per il codice d'avvio del SO. Dopo lo spazio lasciato dal codice, si colloca il superblocco, che è considerabile come una *tabella riassuntiva* delle caratteristiche e dello stato del FS. Le informazioni contenute ci consentono di sapere:
		*Dimensione dei blocchi*
		*Posizione degli i-node*
		*Numero di i-node*
		*Blocchi liberi*
		*blocchi allocati*

----------------------------------------------------------------------------------------
