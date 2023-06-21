**THREAD**
---

*Thread*
	La commutazione fra processi genera un elevato overhead. Anche se alcune macchine forniscono istruzioni che semplificano questo overhead, rimane comunque elevato, data la mole di informazioni che devono essere cambiate (PCB, stato CPU, contesto,...)
	Per ovviare a questo problema, si utilizzano i **thread**, ovvero un modello alternativo di esecuzione di un programma, che *usa le risorse di un processo*. In sostanza, il thread è visualizzabile come un mini-processo a sè, che esegue codice, ma non ha risorse proprie, e *condivide lo spazio d'indirizzamento del processo*.
	*Thread e processi*
		Come un programma può avere più processi che eseguono le sue istruzioni, così *un processo può avere più thread al suo interno*.
	L'overhead dovuto alla commutazione fra processi ha due componenti:
	*Overhead dovuto all'esecuzione:*
		Lo stato della CPU del processo in esecuzione dev'essere salvato e lo stato della CPU del nuovo processo dev'essere caricato nei registri
	*Overhead dovuto all'uso delle risorse:*
		Dovuto alla commutazione del contesto del processo in esecuzione
	Un thread differisce da un processo *perchè al primo non sono allocate risorse*. Un processo crea un thread mediante *una system call* ( **pthread_create()** ), che verrà eseguito usando il contesto del processo ed in tal modo accede alle risorse del processo.
	Ogni thread è *un'istanza del programma*, per cui ha **un proprio Thread Control Block**, analogo al PCB, che contiene le seguenti informazioni:
	*Informazioni per la schedulabilità:*
		**ThreadID, priorità e stato**
	*Puntatore al PCB*
		Punta al PCB del processo genitore
	*Puntatore al TCB*
		Punta al prossimo TCB nella lista
	**Attività dei thread**
		*Stato dei thread e transizioni*
			Gli stati dei thread e quelli dei processi sono uguali, essendo analoghi fra loro, con la differenza che riguarda gli stati:
			*Blocked*:
				Nel caso dei thread, essi non possono richiedere risorse, per cui non c'è alcuna transizione per la richiesta. Tuttavia il thread può entrare nello stato blocked.
			*Swapped*
				Lo stato swapped non esiste, *sia ready che blocked*, proprio perchè la memoria è una risorsa del processo
	**Vantaggi dei thread**
		Ci sono vari vantaggi nell'uso dei thread, primo fra cui quello di avere una
		*Comunicazione più efficiente*
			Visto che i thread condividono lo spazio d'indirizzamento del genitore, possono comunicare fra loro attraverso **dati condivisi** anzichè tramite *messaggi*, evitando l'overhead dovuto alle system call
		Un altro vantaggio è la 
		*Progettazione semplificata*
			La creazione e la terminazione di thread è più efficiente rispetto ai processi: si ricorre alla *thread pool*, un'organizzazione per la quale si riutilizzano i thread invece di distruggerli dopo averne soddisfatto le richieste, così da evitare l'overhead dovuto alla creazione e terminazione.
		I thread assicurano la
		*Correttezza dei dati condivisi e la loro sincronizzazione*
			Ciò può avvenire solamente se l'applicazione che li utilizza è codificata in **thread safe**, ovvero applicazioni che implementano la **mutua esclusione**, tramite *mutex*.
	**Modelli di thread**
		Vi sono tre modelli di thread:
		*Thread Livello Kernel*:
			Un thread di questo livello è **implementato dal kernel**, per cui tutte le operazioni sono implementate tramite system call. L'overhead dovuto alla commutazione risulta comunque dieci volte minore rispetto a quello dei processi.
			*Vantaggi*: 
				Un thread Kernel è alla pari di un processo, ma ha una quantità minore di informazioni di stato
			*Svantaggi*:
				La commutazione è gestita dal kernel, quindi genera overhead anche se il thread interrotto e quello schedulato appartengono allo stesso processo, ma è comunque minore di quello dei processi.
		*Thread Livello Utente*:
			Sono implementati tramite una libreria (**pthread.h**), linkata al codice del processo. In questo modo, il kernel non è a conoscenza dei thread di livello utente nel processo, ma vede solo il processo
			*Vantaggi*:
				Evita l'overhead della system call per la sincronizzazione, per cui l'overhead *potrebbe* essere dieci volte più veloce rispetto ai thread kernel. Questa organizzazione inoltre consente ad ogni processo di usare una politica di scheduling che meglio si adatta alla sua natura
			*Svantaggi*:
				Il kernel non conosce la differenza fra thread e processo, per cui *se un thread si bloccasse su una system call, il kernel bloccherebbe il processo genitore*. Per facilitare questa situazione, un SO dovrebbe rendere disponibile una versione **non bloccante** di *ogni system call*	
		*Modello dei thread Ibridi*:
			Implementa *sia* i thread utente, *sia i thread kernel*, e **un metodo per associarli**. La libreria di thread (**pthread.h**) crea thread utente in un processo e a ciascuno associa un **TCB**. Il kernel crea thread kernel, e a ciascuno associa un **Kernel Thread Control Block**.
			Ci sono tre metodi per associare i thread utente a quelli kernel:
			**Molti a uno**:
				Il kernel crea un *singolo* kernel thread, e **tutti i thread utente** sono associati al thread kernel. I thread utente non possono essere paralleli, l'overhead è basso e il blocco di un thread *porta al blocco di tutti i thread nel processo*
			**Uno a Uno**:
				Ogni thread utente è mappato permanentemente su un thread kernel. I thread possono essere eseguiti in parallelo *su diverse CPU*, la commutazione genera un overhead più elevato perchè gestita dal kernel. I thread sono mappati su diversi thread kernel.
			**Uno a molti**:
				Ad ogni thread utente è concesso di essere mappato su differenti thread kernel in momenti diversi. L'implementazione risulta più complessa.