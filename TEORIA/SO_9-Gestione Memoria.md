**MEMORIA COMPUTER**
---
*Gerarchia*
	Un calcolatore possiede una gerarchia di memoria:
	Registri, cache, RAM, disco,...
	Lo scopo della gerarchia è quello di fornire un'illusione di una memoria grande e veloce
	La gerarchia basilare è composta da:
	*Cache*
		Composta di tre livelli:
		*L1*
			La più vicina alla CPU, è la più veloce, mantiene le informazioni utili all'esecuzione di tutti i processi
		*L2*
			Più lontana, mantiene dati per l'esecuzione del processo, *vi si accede solo se i dati non sono trovati in L1*
		*L3*
			La più distante, contiene i dati cui viene effettuato l'accesso più frequentemente
		La cache è una memoria piccola, ciò fa sì che vengano garantiti *hit* elevati, ovvero che i dati vengano trovati molto spesso al suo interno. Essendo piccola, inoltre, l'accesso ed il trasferimento dei dati costa poco.
	*RAM*
		E' la seconda sulla "scala", è più capiente della cache ma più lenta. Consente di mantenere i processi *swapped* e quelli *running*, così da averli "vicino" durante l'esecuzione.
	*Disco*
		E' la memoria più capiente, ma la più lenta. Essa conserva tutti i dati, di qualunque genere. Questi dati all'occorrenza verranno trasportati nella RAM o nella Cache, quando serviranno all'esecuzione.
	Per mantenere in memoria un numero elevato di processi, il kernel può adottare quella che viene detta *Memoria Virtuale*, ovvero una parte della gerarchia che consente al sistema di mantenere in memoria **una parte dello spazio d'indirizzamento di ogni processo**. Sostanzialmente è come se il kernel mantenesse in memoria solo le istruzioni che devono essere eseguite al momento, e poi utilizza l'indirizzo di un processo per andare a prendere le istruzioni successive.

*Binding*
	Il binding è l'operazione con cui **si associano gli indirizzi di memoria alle entità di un programma**. Il binding consiste nello specificare il valore di un attributo
	Questa operazione si effettua in tre momenti diversi:
	1) Durante la *compilazione*
	2) Durante il *caricamento*
	3) Durante l'*esecuzione*
	Il momento esatto in cui avviene il binding può determinare l'efficienza e la flessibilità con cui l'entità del programma può essere utilizzata
	In generale distinguiamo fra binding *statico* (**early binding**) e *dinamico* (**late binding**):
		Il primo viene eseguito prima dell'esecuzione del programma, mentre il secondo avviene al momento dell'esecuzione

*Esecuzione*
	Un programma P scritto in un linguaggio L prima di essere eseguito deve subire varie trasformazioni.
	In particolare, dev'essere *compilato*, *linkato* e solo alla fine *eseguito*
	![[Pasted image 20230409083127.png]]
	I passaggi sono i seguenti: 
	**Compilazione**
		Le istruzioni del codice sono tradotte in *istruzioni macchina*. Viene creato il **modulo oggetto**.
	**Linking**
		Il codice delle librerie viene incluso nel modulo oggetto, e viene creato il **codice binario**.
	**Caricamento**
		Il codice binario viene caricato in memoria per poter essere eseguito dalla CPU
	Solitamente, le operazioni di linking e di caricamento sono effettuate da un unico programma chiamato *linker*.
	In alcune circostanze, la fase di caricamento viene seguita dal *loader*, mentre il linking si occupa solo del linking.
	Il binding può essere eseguito in tre momenti separati:
	*Al momento della compilazione*
		Viene eseguito in questo momento, quando si sa dove il programma risiede in memoria. Gli indirizzi che vengono assegnati sono gli stessi ad *ogni esecuzione*. Il codice generato prende il nome di **codice assoluto**.
		Se la posizione in memoria del processo dovesse cambiare, sarà necessario ricompilarlo
	*Al momento del caricamento*
		La posizione in memoria è fissa, *ma nota solo all'esecuzione*. Il codice generato è detto **rilocabile**, ed è il loader ad effettuare la rilocazione
	*Durante l'esecuzione*
		La posizione in memoria del processo può variare, quindi il programma può essere spostato da una parte all'altra della memoria

**INDIRIZZI LOGICI E FISICI**
---
*Indirizzo Logico/Fisico*
	Gli indirizzi *logici* sono quelli utilizzati dalla CPU. Il processore fa riferimento alle aree di memoria attraverso indirizzi logici, non conoscendo esattamente le posizioni dei dati in memoria
	Gli indirizzi *fisici* sono gli indirizzi dove risiedono i dati. L'accesso alla memoria avviene utilizzando tali indirizzi.
	La traduzione da indirizzo logico ad indirizzo fisico, *attuata durante l'esecuzione*, viene realizzata tramite un componente HW chiamato **Memory Management Unit**.
	I metodi di associazione degli indirizzi nelle fasi di compilazione e caricamento producono indirizzi logici e fisici identitici. Se invece gli indirizzi sono generati in fase di esecuzione, gli indirizzi logici *non coincidono con quelli fisici*.
	In tal caso, ci si riferisce agli indirizzi logici col termine di **indirizzi virtuali**.
	Il meccanismo che consente di mettere in corrispondenza i due indirizzi è la *rilocazione*
		La rilocazione *statica* viene eseguita prima dell'esecuzione, e permette di risparmiare overhead dovuto alla traduzione degli indirizzi, ma ha lo svantaggio di **non consentire di cambiare l'area di memoria del programma**
		La rilocazione *dinamica* viene eseguita all'esecuzione, ma *consentendo di poter cambiare l'area di memoria*, soffre di overhead. Può essere effettuata anche mettendo in pausa l'esecuzione e poi facendola riprendere.
	*Linker e Loader*
		La differenza fra linker e loader è che il *Linker* **collega insieme i moduli per formare un programma eseguibile**; il *Loader* **carica in memoria un programma o una sua parte per l'esecuzione**
		Vi sono due tipologie di linking:
		*Linking Statico*
			Il linker collega tutti i moduli del programma *prima dell'esecuzione*. Se più programmi usano lo stesso modulo, *ciascuno ne riceverà una copia*.
		*Linking Dinamico*
			Viene eseguito durante l'esecuzione del programma binario. Il linker viene invocato quando si incontra un *riferimento esterno* non assegnato. Il linker collega il riferimento e procede con l'esecuzione.
			In questo caso, se un modulo è usato da più programmi, verrà portato una sola volta in memoria, e se si aggiorna una libreria di moduli, il programma userà automaticamente la nuova versione del modulo

*Assegnazione della memoria*
	La memoria centrale deve contenere sia il SO che i programmi utente. E' perciò necessario assegnare le diverse parti della memoria nel modo più efficiente possibile. 
	Solitamente la memoria si divide in due *partizioni*, una per il SO ed una per i processi utente
	In un sistema multiprogrammato, la memoria centrale è condivisa fra un certo numero di processi. Date le operazioni di *swap* fra memoria e disco, esiste una difficoltà nel tenere separati i processi in memoria.
	**Occorre assicurarsi che ogni processo abbia spazi separati per non interferire con gli altri**.
	A tal fine, occorre determinare l'intervallo degli indirizzi cui un processo può accedere legalmente, e garantire che possa accedere solo a tali indirizzi.
	La **protezione della memoria** è implementata mediante due registri della CPU (*Memory Protection Information*, campo base e campo limite), che contengono l'indirizzo di partenza del processo, e la dimensione della memoria assegnata al processo.
	L'hardware per la protezione della memoria genera un *interrupt di violazione di protezione della memoria* se un indirizzo di memoria utilizzato da un programma risiede oltre l'area di memoria ad esso assegnatagli
	La multiprogrammazione consente di avere diversi processi in memoria, e permette ad un programma di fare uso di due o più processi diversi, in modo da poter terminare le sue operazioni.

*Multiprogrammazione con Partizionamento fisso*
	Il metodo più semplice per realizzare la multiprogrammazione è quello di dividere la memoria in n partizioni fisse, di diversa dimensione. **Ogni partizione deve contere esattamente un processo**, quindi il grado di multiprogrammazione è limitato al numero di partizioni. Le partizioni sono fisse, per cui la memoria non usata dal processo viene "persa".
	In questo tipo di multiprogrammazione, vengono usati due metodi:
	*Code Separate*
		![[Pasted image 20230409091707.png]]
		In questo approccio, *ciascuna partizione ha la sua coda di ingresso*
		All'avvio del sistema, viene effettuata la suddivisione in partizioni. Ogni processo che arriva *viene posto nella coda della partizione più piccola che riesce a contenerlo*.
		Lo svantaggio è evidente quando la coda per una partizione grande sia vuota, mentre quella di una partizione piccola sia piena.
		**I processi piccoli devono attendere per essere inseriti in memoria, sebbene la maggior parte della stessa sia libera**.
	*Coda Unica*
		![[Pasted image 20230409091732.png]]
		In questo approccio, *tutte le partizioni hanno una coda unica*, e la suddivisione viene effettuata all'avvio.
		Ogni qual volta una partizione diventa libera, vi viene caricato il processo *più vicino alla testa della coda che può entrare nella partizione*, e viene quindi mandato in esecuzione.
		Dal momento che non è desiderabile sprecare una partizione molto grande per far entrare un processo piccolo, un'altra strategia è quella di *cercare in tutta la coda ogni volta che si libera una partizione*, e scegliere il job più grande che può entrarvi. Questa tecnica **dà poca priorità ai processi piccoli**.
		Una possibile soluzione è quella di **avere sempre a disposizione una partizione piccola**, che permette ai processi più piccoli di girare senza dover allocare per loro una partizione grande.
		
		
**SWAPPING/MEM VIRT**
---
*Swapping*
	Nei sistemi multiutente e multiprogrammati, normalmente non vi è abbastanza memoria principale per contenere tutti i processi attivi. Dev'essere quindi utilizzato o lo *swapping* o la *memoria virtuale*
	Lo swapping è la strategia più semplice e consiste proprio nel caricare interamente in memoria ogni processo, eseguirlo per un certo tempo e poi spostarlo nuovamente sul disco. Lo spazio sul disco dedicato ad ospitare i processi è detto **Area di Swap**
	Le operazioni svolte sono *swap-in*, quando si porta un processo dal disco alla memoria; *swap-out*, quando si porta un processo dalla memoria al disco
	Nei sistemi multiprogrammati, a lungo andare, lo swapping può **causare molti *buchi*** all'interno della memoria. Una soluzione a questo problema è la 
	**Compattazione della Memoria**
		Per superare le difficoltà del partizionamento fisso, si può utilizzare il *partizionamento dinamico*.
		Quando un processo è caricato in memoria centrale, **gli viene allocata tanta memoria quanta ne necessita**. La flessibilità delle partizioni migliora l'utilizzo della memoria, evitando partizioni troppo grandi o troppo piccole e quindi lo *spreco*
		Il problema delle partizioni variabili è che *complicano la procedura per tenere traccia dell'allocazione e deallocazione della memoria*.

**ALLOCAZIONE DELLA MEMORIA**
	Quando si alloca la memoria ad un processo, il supporto a runtime alloca due tipi di memoria: lo *stack* e l'*heap*.
	*Stack*
		Lo **stack** serve a memorizzare tutte le variabili automatiche del codice, ad esempio quelle generate dal ritorno delle funzioni, ed è strutturato come una *LIFO*. E' strutturato in questo modo:
		![[Pasted image 20230409094237.png]]
		La funzione *main* invoca la funzione *sample*, le cui informazioni relative alla chiamata prendono il nome di *stack frame*. Ciascun frame base punta al precedente, mentre quello iin cima corrisponde all'entrata. L'allocazione e deallocazione è molto veloce perchè ad esso viene allocata memoria *contigua*, e si gestisce come una pila, usando i puntatori che vengono allocati e deallocati
	*Heap*
		Quando si invocano funzioni per l'allocazione dinamica della memoria, si opera sull'*heap*, per cui è possibile farlo su qualunque porzione disponibile tramite system call (*calloc*,*malloc*,*realloc* e *free*).
		Per poter allocare e deallocare opportunamente all'interno dell'heap, ciascuna area di memoria allocata contiene informazioni relative alla lunghezza dell'area di memoria allocata
		![[Pasted image 20230409094713.png]]
		Quando si crea un processo o quando lo si carica in memoria, bisogna determinarne la quantità da allocargli.
		Nei moderni SO si usa l'allocazione *dinamica*. Viene allocata tanta memoria quanta realmente ne occorre al processo. Però, durante l'esecuzione di un processo, le strutture dati dello stesso possono crescere. Le componenti da tener presente per la quantità di memoria ad allocare sono:
		1) Codice e dati del programma
		2) Segmento di dati PCD (*dati dinamici controllati da programma*)
		3) Segmento Stack
		![[Pasted image 20230409095355.png]]
		Alle componenti codice e dati statici del programma vengono allocate aree di memoria che corrispondono esattamente alla loro dimensione. I dati PCD e lo stack condividono un'*unica grande area di memoria*, ma eventualmente crescono *in direzioni opposte* durante la sua esecuzione.

**GESTIONE DELLA MEMORIA**
---
*Bitmap/Liste Libere*
	Quando la memoria viene assegnata dinamicamente, il SO deve gestirla. Ci sono due modi per farlo:
	*Bitmap*
		Con una mappa di bit, la memoria viene divisa in *unità d'allocazione* che possono essere lunghe solo poche parole, o arrivare a quale Kb. A ciascun'unità, viene associato un bit della mappa, che *vale 0 se è libera oppure 1 se è occupata*.
		Le dimensioni dell'unità rappresentano una scelta progettuale importante. **Più piccola è l'unità, maggiore è la mappa**. Una mappa di 32n bit userà n bit nella mappa di bit, così la mappa occuperà solo $\frac{1}{33}$ dell'area di memoria
		Se si sceglie un'unità grande, allora la mappa sarà piccola, ma **viene sprecata una quantità significativa della memoria nell'ultima unità, quando la dimensione dei processi non è multiplo esatto dell'unità di allocazione**.
		Il problema principale, utilizzando l'allocazione contigua, sta nel fatto che *quando si decide di caricare un processo di k unità, il gestore della memoria deve esaminare la mappa di bit, per trovare una sequenza consecutiva di k zeri*. Questa è un'operazione lenta, per cui le bitmap sono poco usate.
	*Liste Libere*
		Quando un processo completa la propria esecuzione o rilascia la memoria allocata, il kernel **riutilizza la memoria** per soddisfare le richieste di altri processi.
		Quando si fa uso del partizionamento della memoria, il SO conserva una tabella, nella quale sono memorizzate *le partizioni di memoria disponibili e quelle occupate*. Questa gestione della memoria è chiamata **Gestione della memoria con Liste Concatenate**.
		Inizialmente, tutta la memoria è a disposizione dei processi utente; si tratta di un grande blocco di memoria disponibile. Ma col passare del tempo, vengono eseguiti molti processi. Dunque, solitamente, in memoria vi saranno **buchi** di diverse dimensioni
		Il kernel utilizza tre funzioni per garantire il **riuso efficace della memoria**:
		*Free List*
			Mantiene una lista contenente le informazioni relative ad ogni area di memoria libera. Quando un processo libera parti di memoria, le informazioni relative alla memoria liberata vengono inserite nella free list, così come quando esso termina.
		*Selezionamento Area*
			Il kernel seleziona un'area di memoria per l'allocazione. Quando viene effettuata una nuova richiesta di memoria, il kernel seleziona l'area più adatta per soddisfarla.
		*Unione Aree*
			Il kernel può unire due aree libere, per crearne una di dimensioni maggiori. Le aree rimosse vengono eliminate dalla list, e viene inserita la nuova area creata.

**TECNICHE DI ALLOCAZIONE**
---
*Mediante Free List*
	Al tempo $t$ esistono $n$ buchi, di differenti dimensioni. Quando un processo è in attesa di memoria, esistono quattro tecniche per scegliere un buco fra quelli disponibili:
	*First-Fit*
		E' l'algoritmo più semplice, nel quale *si assegna al processo il primo buco abbastanza grande da contenerlo*, a partire dall'inizio della lista. Dunque, *le dimensioni del buco saranno uguali o maggiori di quelle richieste dal processo*.
		Questo algoritmo quindi **divide l'area in due parti: una delle dimensioni richieste dal processo, e la restante parte viene reinserita nella free list**
	*Next-Fit*
		Questo è un caso particolare di first-fit. In questo algoritmo, si assegna al processo *il primo buco abbastanza grande per contenerlo, **a partire dal punto in cui era terminata la ricerca precedente***. In questo modo, *si spezzano in modo più uniforme i blocchi della list*, al contrario del First-Fit, che spezza solo i primi blocchi.
	*Best-Fit*
		Questo algoritmo assegna al processo *il più piccolo buco capace di contenerlo*. Si può facilmente intuire che bisognerà scorrere la list per trovare il buco adatto. *La restante parte non assegnata al processo viene reinserita nella list*.
	*Worst-Fit*
		Questo algoritmo *assegna il buco più grande al processo*. Anche qui bisogna esaminare l'intera lista. Lo scopo di questo algoritmo è produrre buchi più grandi, cercando di evitare la *frammentazione esterna*
	Per rendere più veloce l'allocazione della memoria è possibile mantenere aggiornata la free-list, ordinandola per dimensione. In questo modo, la ricerca nel best-fit è effettuata nel modo più veloce

*Frammentazione*
	Quando si alloca con **best**, **next** e **first** fit, si crea **frammentazione**.
	*Esterna*
		La frammentazione esterna si ha quando c'è difficoltà ad allocare buchi nella free-list a richieste successive (*perchè i buchi sono via via sempre più piccoli*)
	*Interna*
		La frammentazione interna si ha quando si vuole destinare alla richiesta di un processo una quantità di memoria maggiore rispetto a quella richiesta (*ci saranno blocchi mai utilizzati*)
	La sostanziale differenza fra le due frammentazioni riguarda **quale parte della memoria viene sprecata**: 
		Nella frammentazione interna, si spreca la memoria *assegnata al processo*, che si trova in un'area più grande di quanto necessario, e così si perde un tot di memoria allocabile ad un altro processo.
		Nella frammentazione esterna, si perde memoria *da allocare*, perchè si cerca sempre di diminuire la dimensione dei buchi
	Per minimizzare la frammentazione, è possibile *fondere* le aree di memoria libere, e ciò viene fatto in due modi:
	*Boundary Tag*
		E' un descrittore di stato di un'area di memoria, che consiste di due campi: in uno viene indicato se l'area è occupata o meno, nell'altro è indicata la *grandezza* del blocco.
		I boundary tag sono posti all'inizio ed alla fine di un blocco libero
		![[Pasted image 20230410133605.png]]
		Grazie al boundary tag, è possibile aggiornare facilmente i puntatori ed i tag ad un area che si è liberata accanto.
		Il numero delle aree allocate (*occupate*) è dato dal numero di aree del tipo A,B,C; il numero di quelle vuote è dato da $(2*\#A+2*\#B)/2$ 
	*Compattazione*
		Tramite questo sistema, vengono prese le aree di memoria libere, e vengono *compattate **alla fine della free-list*** attraverso la *rilocazione*
		![[Pasted image 20230410133917.png]]
	
*Buddy e Potenza2*
	Il *buddy system* e gli *allocatori potenza 2* eseguono l'allocazione di memoria in blocchi di piccole dimensioni predefinite. Questa caratteristica porta alla frammentazione **interna**, poichè parte della memoria in ogni blocco può essere sprecata. Tuttavia, *consente all'allocatore di mantenere free-list separate per blocchi di dimensioni differenti*.
	Questa organizzazione evita ricerche costose nella free-list e porta ad allocazioni e deallocazioni veloci
	*Buddy System*
		Un allocatore buddy divide e ricombina i blocchi in modo predeterminato, durante l'allocazione e la deallocazione. I blocchi creati dividendo un blocco sono detti *blocchi buddy*. I blocchi liberi vengono uniti per ricreare il blocco da cui erano stati creati. Questa operazione prende il nome di *fusione*. Secondo questo sistema, i blocchi liberi contigui *che non sono buddy* **non vengono fusi**.
		In un buddy system *binario*, i blocchi di memoria disponibile hanno dimensione $2^K, K \in [L,U]$ dove:
		1) $2^L$ è un blocco allocato di dimensione più piccola
		2) $2^U$ è un blocco allocato di dimensione più grande. Solitamente, $2^U$ è la dimensione dell'*intera memoria disponibile per l'allocazione*
		Inizialmente, l'intero spazio di memoria è trattato come un singolo blocco buddy, di dimensione $2^U$. Quando dev'essere allocata un'area, di dimensione S:
			Se $2^S \in [2^{U-1},2^U]$, allora viene allocato l'intero blocco $2^U$; altrimenti, il blocco viene diviso in due parti, ciascuna di dimensione $2^{U-1}$
			Se $2^S \in [2^{U-2},2^{U-1}]$, allora uno dei due blocchi è allocato per intero; altrimenti, uno dei due è diviso in due metà di dimensione $2^{U-2}$
			Questo processo viene ripetuto finchè non si trova la corretta dimensione del blocco di memoria da allocare
		Per evitare che i blocchi buddy diventino di dimensione troppo piccola, viene inserito un *limite minimo*, che una volta raggiunto non consente di dividere a metà il blocco buddy
		L'allocatore buddy associa un *tag* di un bit ad ogni blocco, per indicare se è allocato o libero. Il tag può trovarsi nel blocco oppure al di fuori
		L'allocatore mantiene molte liste di blocchi liberi. Ogni free-list contiene blocchi di uguale dimensione. Quando un processo richiede un blocco di dimensione M, il sistema cerca *la più piccola potenza del due che sia maggiore o uguale ad M* ($2^I \le M$). Se la free list che contiene i blocchi di dimensione $2^I$ *è non vuota*, allora alloca al processo il primo blocco della lista, e gli cambia il tag; se la free-list *è vuota*, vuol dire che non sono stati allocati blocchi di dimensione I, e dunque l'allocatore *controlla la free-list dei blocchi di dimensione I+1, **estrae un blocco da tale lista e lo divide a metà***, per creare due blocchi buddy di dimensione I. Uno di questi verrà allocato al processo I, mentre l'altro risulterà libero. Se la free-list dei blocchi di dimensione I+1 è vuota, il sistema controllerà volta per volta le list dei blocchi di dimensione $I+k$, cercando il primo blocco libero ed eseguendo il procedimento per ottenere un blocco di dimensione I.
		Quando un processo *libera* un blocco di dimensioni $2^I$, il processo è analogo. Si verifica che il blocco accanto sia libero (il *fratello*), e nel caso li fonde per ottenere un blocco di dimensioni $2^{I+1}$. Questo procedimento continua finchè non si trova che il *fratello* del blocco esaminato è occupato.
	*Potenza del due*
		Come nel buddy system *binario*, le dimensioni dei blocchi di memoria sono **potenze del due** e vengono mantenute free-list separate per blocchi *di diverse dimensioni*.
		Ogni blocco contiene un *header* che, a sua volta, contiene l'indirizzo della free list alla quale dovrebbe essere aggiunto se deallocato.
		Quando viene seguita una richiesta per M byte, l'allocatore controlla la free list contenente i blocchi la cui dimensione è $2^I$ tale che $2^I \ge M$. Se tale list è vuota, controlla la list dei blocchi di dimensione potenza del 2 successiva e così via.
		Inoltre, *non viene eseguita la fusione dei blocchi adiacenti*, sia quando l'allocatore non ha a disposizione più blocchi di una data dimensione, sia quando una richiesta non può essere soddisfatta.
	*Confronto Allocatori*
		Gli allocatori possono essere confrontati in base a velocità di allocazione ed uso efficiente della memoria.
		Gli allocatori buddy e potenza del due sono più veloci degli allocatori -fit, poichè *evitano le ricerche nelle free-list*.
		L'allocatore potenza2 è più veloce del buddy, poichè *non fonde nè divide i blocchi*.
		Gli allocatori che usano le tecniche -fit generano *frammentazione **esterna***, che limita le loro prestazioni nel caso peggiore poichè i blocchi liberi possono essere di dimensioni troppo piccole per soddisfare una richiesta.
		Gli allocatori buddy e potenza del due generano *frammentazione **interna***, a meno che le richieste non coincidano con una potenza del 2, ovvero la dimensione dei blocchi. Inoltre, questi allocatori usano memoria aggiuntiva per memorizzare i tag (*buddy*) o gli header (*pot2*).

*Frammentazione Memoria*
	Il fenomeno della frammentazione si ha quando si inseriscono e rimuovono processi dalla memoria RAM, oppure un file dal disco.
	Se si considera la RAM, ripetute aggiunte o rimozioni di sequenze di dati di dimensioni diverse comportano una *frammentazione* dello spazio libero disponibile, che quindi non risulta più essere *contiguo*
	Esistono due tipi di frammentazione:
	*Interna*
		Quando viene allocata ad un processo più memoria del necessario
	*Esterna*
		Quando un'area di memoria rimane inutilizzata perchè troppo piccola
	La frammentazione *esterna* può essere evitata unendo le aree di memoria libere per formare aree di memoria di dimensioni maggiori.
	Quest'operazione può essere ripetuta finchè non si incontra un'area di memoria allocata ad un processo, ma *è un metodo costoso*, poichè coinvolge la ricerca nella free list *ogni volta che si libera un'area di memoria*
	In questo approccio (*compattazione*), tutte le aree di memoria libere vengono unite per formare un'unica area libera. Questo risultato può essere ottenuto "compattando" tutte le aree di memoria allocata ad un'estremità della memoria.
	La compattazione non è semplice come potrebbe sembrare, coinvolgendo spostamenti di molti byte di memoria per volta

**ALLOCAZIONE NON CONTIGUA**
---
*Allocazione Contigua/Non Contigua*
	In passato, le vecchie architetture di computer utilizzavano l'allocazione *contigua* della memoria.
	Nell'allocazione contigua, ciascun processo è mantenuto in una singola sezione contigua della memoria.
	Le moderne architetture utilizzano il metodo dell' *allocazione non contigua*, in cui le varie parti di un processo sono contenute in più aree di memoria, anche sparpagliate.
	Questo modello di allocazione consente al kernel di **riutilizzare le aree più piccole rispetto alla dimensione di un processo**, *diminuendo la frammentazione esterna*.
	Questo tipo di allocazione richiede l'uso della **Memory Management Unit**

**MMU**
	Un *indirizzo logico* è l'indirizzo di un'istruzione o di un dato utilizzato dalla CPU; Un *indirizzo fisico* è l'indirizzo di memoria in cui è presente l'istruzione o il dato.
	L'insieme di indirizzi logici in un processo rappresenta lo **spazio di indirizzamento logico** del processo P, mentre l'insieme degli indirizzi fisici nel sistema rappresenta **lo spazio di indirizzamento fisico** del sistema.
	![[Pasted image 20230411095431.png]]
	Il kernel memorizza le informazioni relative alle aree di memoria allocate a P ini una tabella e le rende disponibili alla MMU. La CPU invia gli indirizzi logici di ogni dato/istruzione alla MMU, che li converte in indirizzi fisici, tramite le istruzioni relative all'allocazione memorizzate nella tabella, e ritorna l'indirizzo fisico dell'istruzione/dato.
	Esistono due approcci fondamentali per implementare l'allocazione non contigua:
	*Segmentazione*
	*Paginazione*

*Paginazione/Segmentazione*
	Nella **paginazione**, ogni processo viene diviso in parti di dimensione fissata, dette *pagine*. Nella **segmentazione**, un programmatore identifica le parti di un processo, dette *segmenti*.
	![[Pasted image 20230411121935.png]]
	Ogni area di protezione allocata ad un programma dev'essere *protetta* contro le interferenze da parte di altri programmi. E' la MMU che si occupa di implementare tale funzione mediante il *controllo dei limiti*.
	*Controllo*
		Nel tradurre un indirizzo logico $(comp_i,byte_i)$, la MMU controlla se $comp_i$ è un indirizzo del programma, ossia *se risiede nella quantità di memoria allocata al processo*, e se $byte_i$ è presente in $comp_i$.
		L'indirizzo fisico è dato dall'indirizzo *fisico* di memoria di partenza che contiene il componente del processo ed il numero *di byte di scarto*. Viene generato un *Interrupt di violazione di protezione della memoria* se uno di questi controlli fallisce.
		$E_{AM}(comp_i,byte_i) = Start_{Addr} + \#Byte (\in comp_i)$ 
	**Paginazione**
		Nella paginazione, ogni processo viene diviso in *pagine*, la cui dimensione è predeterminata dall'architettura.
		La memoria può memorizzare un numero *intero* di pagine, e viene partizionata in blocchi di memoria, dette *frame*, che hanno la stessa dimensione della pagina. Quindi, **ogni area di memoria è esattamente della dimensione della pagina**, per cui *non si crea frammentazione esterna*.
		Lo spazio in memoria consiste in un'organizzazione di pagine. Ogni pagina è composta da *s* byte, dove s è potenza del 2.
		La MMU prende questo indirizzo logico e lo scompone nella coppia $(p_i,b_i)$, dove $p_i$ è il numero di pagina, e $b_i$ è l'offset in bit.
		Le pagine e i byte al loro interno sono numerati a partire dallo 0, per cui $p_i \ge 0 \ ; 0\le b_i \le s$ 
		L'hardware partiziona la memoria in *frame*, numerati in memoria a partire dallo 0. Ad ogni istante, alcuni frame risultano essere allocati alle pagine dei processi, mentre altri sono liberi. Il kernel mantiene una lista di tale frame, detta *lista frame liberi*, che viene consultata al caricamento di un processo in memoria.
		Per facilitare la traduzione dell'indirizzo, il kernel mantiene una *Tabella delle Pagine*, che ha un elemento per ogni pagina del processo, indicante il *frame allocato alla pagina*.
		Durante la traduzione di un indirizzo $(p_i,b_i)$, la MMU utilizza il numero di pagina $p_i$ per indicizzare la tabella delle pagine, e così ottiene il numero del frame della pagina allocata a $p_i$ e calcola l'indirizzo fisico mediante l'equazione $Addr(p_i,b_i) = Addr_{frame(p_i)}+\#byte(p_i)$ 
		*Dimensione Ottimale Pagine*
			La dimensione delle pagine è un parametro molto importante. Usando pagine piccole, si può *sprecare meno memoria*, mentre usando pagine grandi *si avrà una tabella più piccola*. **Il tempo per trasferire una pagina grande è simile a quello necessario a quello per trasferire una pagina piccola**.
			Siano:
				$S$ la dimensione *media* dei processi
				$P$ la dimensione delle pagine
				$E$ la dimensione di un elemento nella tabella
			Allora:
				$\frac{S}{P}$ è il numero di pagine in memoria
				$\frac{SE}{P}$ la dimensione della tabella
				$\frac{P}{2}$ la **stima** della memoria *sprecata*
			Il costo sarà di $C=\frac{SE}{P}+\frac{P}{2}$
			Derivando rispetto a P, si ottiene che la *dimensione ottimale delle paigne è*:
				$P = \sqrt{2SE}$ , che *solitamente va da 1 a 64KB*
		Se la dimensione dello spazio degli indirizzi logici è $2^m$ e la dimensione della pagina è di $2^n$ unità di indirizzamento, allora $m-n$ bit più significativi di un indirizzo logico indicheranno *il numero di pagina*, e gli n bit meno significativi indicheranno *lo scostamento*.
		La paginazione non è altro che *Rilocazione Dinamica*: ad ogni indirizzo logico l'architettura fa corrispondere un indirizzo fisico. Con la paginazione si evita *frammentazione esterna*, ma si può avere frammentazione *interna*, visto che lo spazio di memoria richiesto da un processo **non è multiplo della dimensione delle pagine**.
		Attualmente la dimensione delle pagine è compresa fra 4KB e 8KB; ciascun elemento della tabella è lungo circa 4byte, ma tali dimensioni possono variare.
	**Segmentazione**
		Nella segmentazione, un programma è diviso in vari *segmenti* di diversa dimensione. Ogni segmento rappresenta un'entità logica del programma, ad esempio una funzione od una struttura dati.
		Visto che la dimensione del segmento è variabile, può generarsi *frammentazione esterna*. Per questo motivo, il sistema deve usare tecniche di riutilizzo della memoria, come la *best-fit* o la *first-fit*.
		La segmentazione permette una facile *condivisione del codice, dei dati e delle funzioni* di un programma, proprio perchè organizzati in segmenti. Un processo viene visto come un insieme di segmenti, che però sono *sparsi in memoria*. Per questo motivo, indirizzi fisici e logici **non corrispondono**.
		Ogni indirizzo *logico* è rappresentato nella forma $(s_i,b_i)$, dove $s_i$ è l'**ID** di un segmento, mentre $b_i$ è lo *scostamento in byte* all'interno di tale segmento.
		Quest'organizzazione permette al programmatore di vedere la memoria come un insieme di segmenti, che possono essere di dimensioni diverse, e soprattutto *dinamica*.
		Offre dei vantaggi rispetto alla paginazione, cioè:
		1) *Semplifica la gestione delle strutture dati che crescono*
		2) *Permette la modifica e la ricompilazione indipendente dei programmi*
		3) *Si presta alla condivisione dei processi*
		4) *Si presta alla protezione*
		![[Pasted image 20230411124437.png]]
		La parte sinistra della figura mostra la *visione logica* di Q. Per facilitare la traduzione, il kernel costruisce una *tabella dei segmenti* per Q. Ogni elemento mostra la dimensione e l'area di memoria allocata ad ogni segmento. Il campo *dimensione* viene usato per garantire la protezione della memoria.
		Questa tabella viene usata dall'MMU per effettuare la traduzione degli indirizzi: visto che i segmenti hanno dimensione diversa e variabile, la traduzione non può essere effettuata come nella paginazione, ma bisognerà sommare $b_i$ all'indirizzo di avvio di $s_i$ 
		L'allocazione di memoria per ogni segmento viene eseguita come nell'allocazione *contigua* della memoria.
		Nel caricare un processo, il kernel cercherà nella sua *lista di aree libere* un'area non allocata, ed eseguirà l'allocazione *first-fit* o *best-fit* per ogni segmento del processo. Quando un processo termina, le aree ad esso allocate vengono aggiunte alla free-list.
		La frammentazione *esterna* può verificarsi dato che i segmenti hanno dimensioni diverse.
	**Segmentazione con Paginazione**
		Un approccio *ibrido*, chiamato segmentazione con paginazione, combina le caratteristiche delle due tecniche. L'unico svantaggio è che, usando la paginazione, si incorre in *frammentazione interna*.
		![[Pasted image 20230411191006.png]]
		Secondo questo approccio, ogni *segmento* di Q viene *paginato* separatamente, e di conseguenza viene allocato ad ogni segmento *un numero intero di pagine*
		Per ogni segmento, viene creata una tabella delle pagine, e l'indirizzo di questa tabella viene memorizzato nell'elemento relativo al segmento *nella tabella dei segmenti*. Ogni segmento viene paginato separatamente, per cui si verifica *frammentazione interna **nell'ultima pagina di ogni segmento***. Ogni elemento della tabella contiene l'indirizzo della tabella delle pagine e la dimensione del segmento, *utile per la protezione della memoria*.
		La traduzione di un indirizzo logico $(s_i,b_i)$ avviene in due fasi.
			Nella prima, si cerca l'elemento di $s_i$ nella tabella dei segmenti, e *viene estratto l'indirizzo della sua tabella delle pagine*.
			Il numero di byte $b_i$ viene quindi scomposto nella *coppia* $(ps_i,bp_i)$ dove $ps_i$ è il numero di pagina del segmento $s_i$, e $bp_i$ è il numero del byte della pagina $p_i$.
			Nella seconda fase, *si completa il calcolo dell'indirizzo effettivo, così come nella paginazione*, cioè si ottiene il numero di frame di $ps_i$ e $bp_i$ viene ad esso concatenato per ottenere l'indirizzo fisico.

**MEMORIA VIRTUALE**
---
*Memoria Virtuale*
	La memoria virtuale è una parte della gerarchia della memoria composta da una memoria e da un disco. Questa soluzione fa sì che *la richiesta totale di memoria di un processo possa **superare la dimensione della memoria nel sistema***. Permette inoltre che un maggior numero di processi risiedano in memoria contemporaneamente, perchè *ognuno di essi occupa meno memoria della loro dimensione*. Le prestazioni di un processo dipendono dalla *percentuale delle sue porzioni che devono essere caricate in memoria*.
	Il kernel la implementa mediante una combinazione HW+SW, cioè attraverso la *Memory Management Unit* e il *Gestore della Memoria Virtuale* (**SW**). Sono due le operazioni fondamentali nel caricamento della memoria virtuale che utilizzano la paginazione: 
	La *traduzione degli indirizzi* e la *paginazione su richiesta*
	*Traduzione degli indirizzi*
		La memoria virtuale consente ad un processo di caricare in memoria, di volta in volta, solo le sue parti *necessarie*. Essa si basa sul modello di *allocazione di memoria non contigua*, per tali motivi:
			1) Le parti di un processo, dette *componenti*, possono essere caricate in aree di memoria non adiacenti
			2) L'indirizzo di ciascun operando o istruzione di un processo è un indirizzo logico del tipo $(p_i,b_i)$; è la MMU che traduce tale indirizzo in un indirizzo fisico, in cui si trova il dato o l'istruzione necessaria.
		Questo modello di allocazione *riduce la frammentazione* della memoria
	*Caricamento su Richiesta*
		Il gestore della memoria virtuale **carica in memoria solo quella porzione che contiene l'indirizzo di start** del processo, ovvero solo l'*indirizzo dell'istruzione con cui inizia la sua esecuzione*. Successivamente, carica altre parti del processo **solo quando necessarie** (*caricamento su richiesta*). Occasionalmente, il gestore *rimuove* dalla memoria le componenti inutilizzate del processo.
	*Paginazione e Segmentazione*
		E' possibile implementare la memoria virtuale attraverso la paginazione o la segmentazione.
		Nella paginazione, ciascuna porzione di spazio di indirizzamento è chiamata *pagina*; tutte le pagine hanno dimensioni uguali $2^K$, che è definita dall'architettura.
		Nella segmentazione, ogni porzione di uno spazio di indirizzamento è chiamato *segmento*. L'identificazione delle porzioni è a carico del programmatore, e i segmenti possono avere dimensioni diverse.
		Alcuni sistemi usano un approccio ibrido usando sia la paginazione che la segmentazione.
	*Paginazione su RIchiesta*
		Consideriamo un processo P composto da pagine, numerate da 0 in avanti. Ogni pagina è di $S$ byte, dove $S=2^K$.
		Si consideri che la memoria del computer è composta da frame di pagina, dove un frame è un'area di memoria avente la stessa dimensione della pagina. Questi frame sono numerati da 0 a $\#Frame-1$.
		Dunque, lo spazio di indirizzamento fisico è composto da indirizzi da 0 a $S*(\#Frame-1)$.
		Ogni indirizzo logico usato in un processo è rappresentato da una coppia $(p_i,b_i)$, dove $p_i$ è il numero di pagina, e $b_i$ è il numero di byte della pagina $p_i$. Si ha sempre che $p_i \ge 0 \ ; \ 0 \le b_i \le S$.
		La traduzione dell'indirizzo è data da: $Addr(p_i,b_i) = \&Frame(p_i)+\#Byte(b_i) \in p_i$. Essendo $S = 2^K$, il calcolo dell'indirizzo effettivo è eseguito mediante *concatenazione di bit*.
		![[Pasted image 20230411193119.png]]
		*Tabella delle pagine*
			Il gestore della memoria virtuale tiene una tabella delle pagine per ciascun processo, per *mappare* le pagine virtuali sui frame, cioè per indicare *in quale frame di memoria si trovano le varie pagine*. Ciascuna tabella contiene un elemento (*riga*), per ogni pagina allocata al processo. I campi (*colonne*) sono molteplici e contengono svariate informazioni.
			Le dimensioni di una tabella vanno dai 32 ai 64bit, nei moderni computer, ma possono avere dimensioni differenti.
			![[Pasted image 20230411193358.png]]
			I passi per effettuare la traduzione dell'indirizzo logico in indirizzo fisico sono 3:
			![[Pasted image 20230411193436.png]]
		*Page Fault*
			La MMU effettua la traduzione degli indirizzi mediante la tabella delle pagine. Si ha un **page fault** quando un processo tenta di caricare una pagina non mappata.
			Il controllo del *bit di validità* viene effettuato al passo due, dove la MMU controlla il bit di validità nella tabella delle pagine: se tale bit vale 0, la pagina *non è presente in memoria*, e la MMU genererà un interrupt chiamato *Page Fault*, altrimenti è presente.
			Per poter risolvere questo problema, si potrebbe allocare più memoria, ma questa operazione potrebbe causare danni agli altri processi. *La quantità di memoria da allocare deve rispettare il giusto compromesso fra avere memoria sufficiente per un processo e buone prestazioni*, che garantiscono un buon grado di multiprogrammazione.
			Per fare ciò, esistono meccanismi che valutano dinamicamente le condizioni di esecuzione di ciascun processo, valutandone la soluzione ottimale.
			Quando c'è un elevato tasso di page fault perchè ci sono pochi frame allocati, è probabile che in parecchi processi si verifichi il **THRASHING**, poichè *spenderanno maggior tempo per la paginazione che per l'esecuzione, facendo sì che la CPU rimanga in idle*. In questo modo, verranno avviati nuovi frame liberi, che andranno incontro a *Thrashing*. In pratica le prestazioni del sistema collassano, finchè l'operatore non dovrà per forza terminare alcuni processi.
		*Page-In,Page-Out e sostituzione*
			Quando un processo vuole *usare una pagina non presente in memoria, e ci sono frame liberi in memoria*, il gestore della memoria virtuale carica la pagina dallo spazio di swap. Questa operazione prende il nome di **page-in**.
			Quando il gestore della memoria virtuale decide di *rimuovere una pagina dalla memoria, copia la pagina nello spazio di swap*. Questa operazione prende il nome di **page-out**.
			Quando un processo vole usare una pagina *non presente in memoria*, ma *non ci sono frame liberi*, si deve attuare la **Sostituzione delle Pagine**. La sostituzione è necessaria al verificarsi di un page fault non avendo frame liberi in memoria.
			Questa operazione viene svolta dal gestore della memoria virtuale, che:
				1) Seleziona una delle pagine attualmente in memoria, *usando un algoritmo di sostituzione* delle pagine
				2) Modifica il campo *bit di validità* della pagina, settandolo a 0. Con questa operazione, la pagina diventa **DIRTY**.
				3) Effettua un'operazione di *Page-Out*, per copiare la pagina sul disco in quanto è dirty.
				4) Effettua un'operazione di *Page-In* per caricare in memoria, nel frame appena liberato, la nuova pagina dal disco
				5) Una volta conclusa l'operazione di Page-In, modifica il campo *bit di validità* della nuova pagina a 1.
				**Durante tali operazioni, lo stato del processo viene impostato a Blocked**.
		*Tempo di accesso effettivo*
			Il tempo medio di accesso, atteso dal processo, dipende dalla presenza o meno in memoria della pagina cui si fa riferimento. Per calcolare tale tempo si usa la formula:
				$pr_1 *2* t_{mem}+(1-pr_1)*(t_{mem}+t_{\frac{p}{h}}+2*t_{mem})$ , dove:
				$pr_1$ è la probabilità che la pagina *esista* in memoria (**HIT**)
				$t_{mem}$ è il tempo di accesso in memoria
				$t_{\frac{p}{h}}$ è l'*overhead* del tempo per la gestione degli errori di pagina
			Il tempo è suddiviso in due componenti:
				1) **Pagina in memoria**
					$pr_1*2*t_{mem}$ : Se la pagina è in memoria (*Hit*), occorre $2t_{mem}$ per prenderla dalla tabella delle pagine e poi bisogna trovare il frame effettivo (*due accessi in memoria*)
				2) **Pagina non in memoria**
					$(1-pr_1)*(t_{mem}+overhead+2*t_{mem})$ : Se la pagina non è in memoria, bisogna trovarla nel disco (*accedendo la prima volta in memoria*), gestire l'overhead dovuto all'interrupt *Page Fault*, e poi eseguire il controllo nella tabella delle pagine, ed andare al frame effettivo.

*Ridurre Page Fault*
	Riducendo i Page Fault, è possibile riddurre l'$EAT$. Una soluzione è quella di *caricare le pagine **prima** che siano necessarie ad un processo*.
	Per poter identificare la tabella delle pagine relativa ad un indirizzo logico, l'MMU contiene un registro che si chiama *Page Table Access Register* (**PTAR**), il quale punta all'inizio della tabella. Attraverso la somma del numero di pagina, e del contenuto del PTAR, sarà possibile individuare la tabella delle pagine in memoria.
	*Supporto HW alla Paginazione*
		*Protezione della Memoria*
			Per poter implementare la protezione della memoria si usa un ulteriore registro, detto *Page Table Size Register* (**PTSR**). E' un'informazione che l'MMU usa per *verificare che un processo acceda ad una pagina esistente*.
			Un interrupt di violazione della protezione viene generato quando un processo tenta di accedere ad una pagina cui non può accedere, o per permessi o perchè non esistente. Per gestire i privilegi, si fa riferimento al campo *prot_info* della tabella delle pagine. 
		*Buffer di Traduzione*
			Le tabelle delle pagine vengono tenute in memoria per le loro grandi dimensioni, ma ciò può *penalizzare fortemente le prestazioni*. Una singola istruzione, infatti, può far riferimento a più indirizzi.
			Solo una piccola parte degli elementi della tabella viene letta con più frequenza.
			Una possibile soluzione è quella di usare il **Translation Look-Aside Buffer** (*TLB*), o *memoria associativa*, che una cache veloce contenuta nell'MMU che permette di velocizzare la traduzione degli indirizzi.
			Il TLB contiene porzioni della tabella delle pagine, in particolare gli elementi usati più di recente. Di ogni elemento memorizza alcune informazioni principale, come *il numero di pagina*, *il numero di frame*, *il bit di modifica* e il *campo per la protezione*.
			Quando alla MMU arriva un indirizzo virtuale da tradurre, l'hardware controlla prima *se il relativo numero di pagina è presente nel TLB*, confrontandolo simultaneamente (*in parallelo*) con tutti gli elementi.
			Se c'è corrispondenza (*page hit*), la MMU completa la traduzione prendendo il numero di frame *direttamente dal TLB*, senza bisogno di accedere alla tabella delle pagine.
			Se non c'è corrispondenza (*page miss*), la MMU esegue una normale ricerca nella tabella delle pagine: se la pagina è presente, completa la traduzione, altrimenti si genera un *Page Fault*, che attiva il gestore della memoria virtuale per caricare la pagina in memoria.
			Quando si verifica un Page Miss, la MMU cerca la pagina nella tabella, e quando ha concluso la traduzione degli indirizzi, *scarica uno degli elementi del TLB e lo sostituisce con l'elemento della tabella appena trovato*.
			Se l'MMU fa traduzione degli indirizzi accedendo alla tabella delle pagine con processi precedenti, può succedere che si vada a *minare la protezione della memoria*. Per evitare questo problema ci sono due approcci:
				1) Ogni entrata del TLB deve contenere *l'ID del processo in esecuzione al momento dell'entrata*.
					Avendo l'ID del processo, non si può accedere al TLB per fare la traduzione di un altro processo relativa a quello corrente
				2) Il kernel deve *scaricare* il TLB mentre esegue la commutazione fra processi
			E' quindi necessario prendere in considerazione il *tempo d'accesso medio* per ogni processo:
				$pr_1*2*t_{mem}+(1-pr_1)*(t_{mem}+t_{\frac{p}{h}}+2*t_{mem}) \rightarrow$
				$\rightarrow pr_2*(t_{TLB}+t_{mem})+(pr_1-pr_2)*(t_{TLB}+2*t_{mem})+(1-pr_1)*(t_{mem}+t_{\frac{p}{h}}+2*t_{mem})$ 
			Dove:
				$pr_1$ è la probabilità che la pagina *esista* in memoria
				$pr_2$ è la probabilità che l'entrata alla pagina *esista* **nel TLB**
				$t_{mem}$ è il tempo d'accesso in memoria
				$t_{TLB}$ è il tempo d'accesso al TLB
				$t_{\frac{p}{h}}$ è l'overhead per la gestione del Page Fault
	*Supporto per la gestione delle pagine*
		Il gestore della memoria virtuale ha bisogno di due tipi di informazione per *minimizzare il Page Fault ed il numero di operazioni di Page-In e Page-Out* durante la sostituzione della pagina:
			1) L'ultimo istante d'utilizzo di una pagina
			2) Se una pagina è *dirty*, cioè se un'operazione di scrittura è stata eseguita su qualche suo byte.	
		L'istante di ultimo utilizzo indica *quanto di recente una pagina è stata usata da un processo*. Per questo scopo, è usato un campo di un singolo bit: *ref_info*. Si usano alcuni algoritmi (*LRU*), che decidono quale pagina rimuovere. 
		Per indicare se una pagina è dirty,viene usato il campo *bit di modifica*. Se una pagina è *clean*, vuol dire che la sua copia in memoria è ancora attuale, e quindi non è necessaria alcuna operazione di Page-Out

**Organizzazione pratica delle tabelle delle pagine**	
	Per risolvere lo spreco derivante dalla presenza *costante* in memoria di tabelle di pagine molto grosse, vengono eseguiti fondamentalmente *due* approcci per ridurre la dimensione in memoria assegnata alle tabelle, e il TLB viene usato in *entrambi*:
		*Tabella delle pagine invertita*
			La tabella delle pagine invertita, *IPT*, contiene un elemento per ogni frame di memoria,
			Ciascun elemento contiene il numero di pagina che occupa il frame, e l'ID del processo. La tabella viene così chiamata perchè l'informazione in essa contenuta è *invertita* rispetto alla classica tabella delle pagine.
			La dimensione di un IPT dipende dalla dimensione della memoria. In questo approccio, è *più difficile* effettuare la traduzione degli indirizzi, non dovendo più cercare un indice, ma *una coppia di elementi $(R,p_i)$ nella tabella IPT*, che indica che **il frame $f_i$ è occupato dalla pagina $p_i$ del processo $R$**.
			Lo scheduler, selezionato un processo, ne preleva l'ID dal PCB e lo invia in un registro dell'MMU. Per velocizzare tale ricerca, vengono usati il TLB e un'*Hash Table*, nel caso in cui si verifichi un Page Miss.
			Quando c'è un indirizzo logico, si costruisce l'indirizzo $(p_i,b_i)$, successivamente si preleva l'ID del processo ed insieme al numero di pagina lo si va a cercare all'interno dell'IPT.
			La chiave per un funzionamento efficiente è quella di *ottimizzare la ricerca tramite la definizione di un'Hash Table*: prendendo l'ID del processo ed il numero di pagina, si concatenano e si applica una **funzione di Hashing** che restituisce un indice, che fa riferimento alla tabella delle pagine.
			Nella tabella di hash si potrebbe avere una *collisione*, per cui si aggiunge un campo puntatore, in modo che le collisioni vengano gestite mediante una *lista*.
		*Tabella delle pagine multilivello*
			Questa tecnica consiste nel *suddividere una tabella delle pagine*, di grosse dimensioni, in *più livelli*. In questo modo si effettua una paginazione della tabella : una tabella di alto livello viene usata per accedere alle varie pagine della tabella delle pagine. Se la tabella di alto livello fosse di grandi dimensioni, potrebbe essere *essa stessa paginata*, e così via.
			Si impiegano nel sistema due tipi di pagine: la *Pagina della Tabella* e le *Pagine del processo*
			In questo modo si limita la quantità di memoria necessaria per gestire la tabella delle pagine, perchè si mantiene un'organizzazione di dimensioni ridotte che contiene le informazioni necessarie e le altre che possono essere tenute su disco, riducendo la quantità di memoria

**GESTORE MEMORIA VIRTUALE**
---
*Gestore*
	Il gestore della memoria virtuale deve prendere due decisioni chiave, che influenzano le prestazioni di un processo:
	*Quale pagina rimuovere dalla memoria*, per liberare spazio per una nuova pagina richiesta, e *quanta memoria allocare al processo*.
	![[Pasted image 20230412110429.png]]
	![[Pasted image 20230412110444.png]]
	*Gestione dello spazio d'indirizzamento logico*
		Il gestore della memoria virtuale gestisce lo spazio d'indirizzamento *logico* di un processo, attraverso le seguenti funzioni:
		1) Crea una copia delle istruzioni e dei dati del processo nel suo spazio di swap
		2) Gestisce la tabella delle pagine
		3) Esegue Page-In e Page-Out
		4) Esegue l'inizializzazione del processo
		Una copia dell'intero spazio d'indirizzamento logico del processo è mantenuta nell'area di swap del processo.
		Al verificarsi di un Page Fault, la pagina viene caricata dall'area di swap, mediante Page-In. Quando una pagina dirty dev'essere rimossa dalla memoria, viene eseguita un'operazione di Page-Out. In questo modo la copia della pagina nello spazio di swap è *attuale* se quella pagina non è in memoria, o era in memoria ma non è stata modificata da quando era caricata.
	*Gestione della memoria*
		Il gestore della memoria si occupa anche di *mappare* i frame, tenendo traccia di quali siano quelli occupati e quali quelli liberi. Un frame viene eliminato dalla lista dei frame liberi quando viene effettuata un'operazione di Page-In, mentre viene aggiunto quando viene svolta un'operazione di Page-Out
		Quando un processo termina, tutti i frame ad esso allocati sono aggiunti alla lista dei frame liberi.
	*Protezione*
		Il gestore della memoria si occupa di conservare le informazioni *utili per la protezione della memoria*. Queste sono memorizzate nel campo *prot_info* della tabella delle pagine. Sono contenuti i *privilegi d'accesso*, quindi se si tenta di accedere ad una pagina con una modalità non consentita, viene *generato un interrupt*
	*Raccolta informazione per la sostituzione delle pagine*
		Il gestore della memoria virtuale si occupa anche di conservare le informazioni necessarie per sostituire una pagina. Queste sono contenute nei capi *Ref_info* e *Modificata*, nella tabella delle pagine.

**SOSTITUZIONE PAGINE**
---
*Politiche di Sostituzione*
	L'obiettivo di una politica è quello di sostituire *solo le pagine che non saranno usate nell'immediato*. Ci sono tre politiche per la sostituzione:
		1) Sostituzione delle pagine **ottimale**
		2) Sostituzione **FIFO**
		3) Sostituzione **Least Recently Used**
	Per attuare questa analisi ci basiamo sul concetto di *stringa dei riferimenti alle pagine*.
	Una tale stringa è una sequenza di pagine cui il processo ha fatto accesso durante la sua esecuzione. Può essere costruita monitorando l'esecuzione di un processo, e *formando una sequenza di numeri di pagina*.
	**Al k-simo riferimento della stringa è associato un istante di tempo b.**
	*Sostituzione Ottimale*
		Consiste nel sostituire le paigne in modo che il numero *totale* di Page Fault sia il minimo possibile. Un algoritmo del genere sostituisce *le pagine che non verranno usate per il tempo maggiore*
		Una politica del genere è **irrealizzabile**, in quanto al momento del Page Fault, il sistema *non può conoscere il comportamento futuro di un processo*.
	*Sostituzione FIFO*
		Ad ogni Page Fault, sostituisce la pagina caricata in memoria **prima di ogni altra**, cioè *quella in memoria da più tempo*. Per tenere traccia dell'ordine, si usa il campo *Ref_info* della tabella delle pagine.
		Il SO mantiene una lista delle pagine correntemente in memoria, dove la pagina in testa è la più vecchia e quella in coda è la più recente, e andrà a sostituire sempre quella in testa.
		Questa strategia *non è desiderabile*, in quanto l'ultimo caricamento potrebbe essere stato fatto da più tempo ma *non significa che nel breve periodo non possa essere referenziata*, soprattutto se si trova nella *località corrente* dell'indirizzo
	*Sostituzione LRU*
		La politica *Least Recently Used* sostituisce la pagina usata meno di recente con la pagina richiesta. In pratica viene *scaricata la pagina usata da più tempo*. Tale politica è realizzabile, ma **non conveniente**, in quanto per implementarla andrebbero mantenute *liste concatenate di tutte le pagine in memoria*, con la pagina usata meno di recente in testa, e la difficoltà sta nel fatto *che la lista andrebbe aggiornata **ad ogni riferimento alla memoria***.
	![[Pasted image 20230412112236.png]]
	![[Pasted image 20230412112302.png]]
	C'è un'anomalia nel grafico della politica *FIFO*: Il numero di Page Fault aumenta quando auenta il numero di frame. Questo comportamento è detto **anomalia di Belady**.
	Per questo motivo, il gestore della memoria non può usare la tecnica FIFO perchè incrementando i frame allocati potrebbe aumentare la frequenza dei Page Fault.
	*Proprietà dello stack*
		Esiste il giusto compromesso fra numero di frame allocati e Page Fault:
		Purchè una strategia di sostituzione possa risiedere nella zona desiderabile, deve godere della **proprietà dello stack**: 
			Una politica di sostituzione delle pagine gode di tale proprietà se $(p_k)_n^k \subseteq (p_i)_m^k \ \forall n,m \ | \ n<m$ 
			![[Pasted image 20230412112830.png]]
			Dove $(p_k)_n^k$ indica l'insieme delle pagine in memoria al tempo $t_k^+$ se $alloc_i = n$ durante *l'intera attività di* $P_i$. $t_k^+$ indica l'istante dopo $t_k$ ma prima di $t_{k+1}$.
		Una politica di sostituzione delle pagine soddisfa la proprietà dello stack se *il numero di pagine del processo $P_i$ 
		all'istante k  e n frame allocati sono inclusi nelle pagine allocategli allo stesso istante temporale, se allo stesso processo gli si allocano m frame, con $m>n$*.
		In pratica, se si considera l'esecuzione del processo $P_i$ nei vari istanti, e ad ogni istante $t_k^+$ **le pagine presenti in memoria in n frame sono contenute nell'insieme delle pagine con m frame allocati**, allora la politica gode della proprietà dello stack.
		Quando si eseguono m frame significa che ci saranno $m-n$ pagine che possono essere riferite o meno durante l'esecuzione. Se sono riferite quando c'è l'esecuzione con m, allora la pagina sarà in memoria, altrimenti verrà generato un Page Fault.
		All'aumentare dei frame allocati **non possono aumentare i Page Fault**, ma al massimo *possono essere costanti*.
		**LA STRATEGIA FIFO NON GODE DELLA PROPRIETA' DELLO STACK**.

**ESEMPI REALISTICI DI SOSTITUZIONE**
---
*Esempi*
	![[Pasted image 20230412120135.png]]
	Il gestore della memoria virtuale mantiene una lista dei frame liberi, e prova a tenere pochi frame in tale lista ad ogni istante di tempo. Esso consiste di due *daemon threads*: 
	*Gestore Frame Liberi*
		Viene attivato ogniqualvolta la lista dei frame liberi contiene un numero di frame che va sotto una soglia definita dal gestore, in fase di boot del sistema: esso va a scandire le pagine dei processi presenti in memoria *alla ricerca di qualche pagina che possa essere rimossa*, per riempire la lista dei frame liberi. Tramite questo metodo, si evita di effettuare il Page-In: il gestore sceglie una pagina da sostituire e segna all'interno della lista dei frame liberi se il frame contiene una pagina modificata di recente *aggiornando il dirty bit*. 
	*Gestore I/O pagina*
		Quando è necessario effettuare una sostituzione, il *Gestore dell'I/O di pagina* va ad eseguire le operazioni di Page-Out: esamina la lista dei frame liberi, controlla i frame con dirty bit settato, e per questi effettua Page-Out, memorizzando la pagina contenuta in quel frame sul disco.
	*Gestore Page Fault*
		Funziona come un qualunque componente del kernel *interrupt driven*: si attiva con l'interrupt generato dall'MMU al verificarsi di un Page Fault, e verifica se la pagina che dev'essere caricata in memoria si trova ancora all'interno dei frame liberati dalle operazioni precedenti. Il gestore setta il bit di validità e rimuove il frame dalla lista dei frame liberi.

**ALTRE POLITICHE**
	La politica *LRU* sarebbe la scelta più conveniente, ma non è fattibile perchè i computer non hanno sufficienti dati nel capo *Ref_info* per memorizzare il tempo di ultimo riferimento.
	Le politiche di sostituzione delle pagine devono essere implementate usando *solo il bit di riferimento*. Questo requisito ha portato a una classe di politiche dette **Not Recently Used**, in cui il bit di riferimento è utilizzato per determinare se una pagina è stata riferita di recente, e qualche pagina di queste viene sostituita.
	*Not Recently Used*
		Una semplice politica NRU è la seguente: il bit di riferimento è inizializzato a 0 quando viene caricata la pagina in memoria, ed è settato ad 1 quando viene riferita. Quando si rende necessaria una sostituzione, se il gestore nota che tutte le pagine hanno bit settato, lo re-imposta a 0 e arbitrariamente seleziona una pagina per la sostituzione; altrimenti, sostituisce una pagina randomica che abbia bit 0.
		L'attrattiva di tale approccio è che è facile da capire e da implementare, e fornisce prestazioni spesso soddisfacenti.
	*Algoritmi di Clock*
		Forniscono la migliore discriminazione tra le pagine resettando periodicamente i bit di riferimento. In questo modo, risulta possibile sapere se una pagina è stata riferita nell'immediato passato.
		Le pagine di tutti i processi sono memorizzati in una lista circolare, e i puntatori usati dagli algoritmi si muovono sulle pagine ripetutamente, in modo analogo al movimento delle lancette di un orologio. Il bit di riferimento è settato quando:
			1) La pagina è caricata per la prima volta in un frame di memoria
			2) La pagina nel frame è utilizzata
		Al verificarsi di un Page Fault, si effettua una scansione della lista e si sostituisce il frame che ha bit di riferimento pari a 0.
		*Una Lancetta*
			Nell'algoritmo di Clock **ad una lancetta**, un'esecuzione è composta da due step su ogni pagina:
				Nel primo passo, il gestore della memoria virtuale semplicemente *resetta* il bit
				Nel secondo, cerca tutte le pagine i cui bit sono ancora 0, e le aggiunge alla lista dei frame liberi (*sostituisce la pagina*)
		*Due Lancette*
			Nell'algoritmo **a due lancette**, sono usati due puntatori. Il primo, chiamato **Resetting Pointer**(*RP*), serve a resettare i bit di riferimento, mentre il secondo, detto **Examining Pointer**(*EP*), serve a controllare i bit di riferimento. Entrambi i puntatori vengono incrementati simultaneamente. Il frame al quale EP punta è aggiunto alla lista dei frame liberi se il suo bit di riferimento è 0.
			RP reimposta il bit a 0 se quando lo esamina vale 1.
			La distanza fra i due puntatori fornisce proprietà diverse agli algoritmi. 
				Se i puntatori sono molto vicini, sarà esaminata una pagina subito dopo il reset del bit, e di conseguenza *solo le pagine usate di recente* rimarranno in memoria. 
				Se i puntatori sono abbastanza lontani, solo le pagine non utilizzate da molto tempo verranno rimosse.
		![[Pasted image 20230412122016.png]]

**ALLOCAZIONE FRAME AD UN PROCESSO**
---
*Assegnazione memoria*
	Sia il sovradimensionamento che il sottodimensionamento di memoria concessa ad un processo porta a cali di prestazioni e scarsa efficienza della CPU.
	Vengono usati due approcci per controllare l'allocazione dei frame per un processo:
	*Allocazione di memoria fissa*
		La prestazione di un processo è indipendente dagli altri processi del sistema. Quando si verifica un Page Fault in un processo, viene sostituita una delle sue pagine. Questo approccio è detto *sostituzione di pagina locale*
	*Alloczione di memoria variabile*
		La memoria può essere *variata* in due modi:
		Quando si verifica un Page Fault, tutte le pagine di tutti i processi che sono in memoria possono essere prese in considerazione per la sostituzione. Ciò è identificato come *sostituzione globale di pagine*. Alternativamente, il gestore della memoria virtuale può rivedere l'allocazione della memoria per un processo *periodicamente*, sulla base della sua località e sul comportamento riguardo i Page Fault, ma quando se ne verifica uno esegue una *sostituzione locale*
	Nell'*allocazione fissa in ambito globale*, le decisioni riguardanti la memoria sono eseguite staticamente. La memoria da allocare ad un processo è determinata, in base ad alcuni criteri, quando il processo viene inizializzato. La sostituzione di pagina *è sempre eseguita localmente*.
	Nell'*allocazione variabile in ambito globale*, l'allocazione per il processo attualmente in esecuzione *può diventare troppo grande*. La migliore soluzione fra le tre è sicuramente l'*allocazione variabile in ambito locale* , che utilizza la sostituzione locale delle pagine, perchè *il gestore della memoria virtuale determina il giusto valore di **alloc** per un processo, di volta in volta*.
	**Modello a Working Set**
		Il concetto di Working Set fornisce una base per *decidere quante e quali pagine di un processo* dovrebbero essere in memoria per ottenere una buona prestazione di processo.
		L'insieme di tutte le pagine di ogni processo viene detto **working set**. Consiste nell'assicurarsi che *l'insieme di lavoro sia caricato totalmente in memoria*, prima di consentire ad un altro processo di andare in esecuzione.
		Il working set aumenta la probabilità di Page Fault come un processo, ma la diminuisce con la diminuzione delle pagine disponibili. Per evitare la consumazione completa della memoria, *le pagine devono essere rimosse dal working set*, e trasformate in disponibili per un loro eventuale utilizzo.
		Il SO diminuisce i working set nei seguenti modi:
			1) Scrivendo su pagine modificate in un'area dedicata, su un dispositivo di massa
			2) Contrassegnando aree non modificate come libere
		In molti casi, una sorta di algoritmo NRU determina le pagine che possono essere rimosse dal working set dei processi.
		Consideriamo le seguenti notazioni:
			$\Delta$ è il numero delle precedenti istruzioni che costituiscono la finestra dei Working Set
			$WS_i(t,\Delta)$ è il working set di $P_i$ al tempo t per la finestra $\Delta$
			$WSS_i(t,\Delta)$ è la dimensione del Working Set $WS_i(t,\Delta)$, cioè *il numero di pagine in $WS_i(t,\Delta)$*
			$WS_i(t,\Delta) \le \Delta$
		Attraverso l'uso dei Working Set, il gestore può aumentare o diminuire il grado di multiprogrammazione.
			Se c'è un insieme di processi in esecuzione $\{P_k\}$ , si potrebbe decidere di *abbassare il grado*, **sospendendo uno dei processi in esecuzione**. Una casistica è quando la somma delle dimensioni dei Working Set di tutti i k processi è maggiore del numero di frame in memoria. 
			Se ci sono più pagine riferite rispetto al numero di frame, bisogna ridurre il grado di multiprogrammazione.
				$\sum_k (WSS_k) > \#frame$
			E' possibile *incrementare il grado* quando la somma delle dimensioni dei Working Set di tutti i k processi è minore del numero dei frame in memoria.
				$\sum_k (WSS_k) < \#frame$
			Se ciò è vero, allora si cerca un processo $P_g$ tale che il suo working set è minore del numero di frame disponibili. Quindi la somma delle dimensioni dei working set sarà:
				$WSS_g \le [\#frame - \sum_k (WSS_k)]$ 
		Il gestore della memoria virtuale tiene traccia per ogni processo, sia il valore di $alloc_i$ che la dimensione del suo Working Set, per gestire l'aumento e la diminuzione del grado di multiprogrammazione.
			Per abbassarlo, sceglie un $P_i$ da sospendere: esegue un Page-Out per ogni pagina modificata da $P_i$ e cambia lo stato del frame a *libero*. Quindi $alloc_i$ è impostato a 0, mentre il WSS rimane alterato.
			Per incrementarlo, si ripristina $P_i$ e si pone $alloc_i = WSS_i$, per cui si carica la pagina di $P_i$ che contiene la prossima istruzione da eseguire, mentre le altre verranno caricate al verificarsi di un Page Fault. Alternativamente, si possono caricare *tutte* le pagine di $WS_i$, generando però ridondanza nei caricamenti.
		Per quanto riguarda l'implementazione, il principio resta uguale: *si valuta il processo periodicamente*, dove alla fine dell'intervallo *si valuta il WS di ogni processo*, e si usano tali informazioni per determinare i WS dell'intervallo successivo.
	*Working Set Clock*
		L'algoritmo WSClock è un algoritmo perfezionato, basato sull'algoritmo Clock ma che utilizza anche le informazioni sul WS. Per la sua semplicità di implementazione e per le buone prestazioni, è usato largamente.
		La struttura dati necessaria è una lista circolare di pagine fisiche, che inizialmente è vuota. Quando viene caricata la prima pagina, viene aggiunta alla lista, e ogni volta che viene caricata un'altra pagina, va a finire nella lista formando un anello. Ogni elemento contiene il campo relativo al tempo di ultimo utilizzo, inoltre contiene il bit R e il bit M.
		Come nell'algoritmo dell'orologio, ad ogni Page Fault, la pagina puntata dalla lancetta viene esaminata per prima:
			Se R assume valore 1, la pagina è stata usata durante il tick corrente, quindi viene lasciata in memoria. R viene quindi impostato a 0, e si passa ad esaminare la pagina successiva.