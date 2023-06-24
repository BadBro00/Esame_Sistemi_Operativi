
--------------------------------------------------------------------------
*THREAD*
---

*Thread o Processi*
	I processi concorrenti *velocizzano l'esecuzione* delle applicazioni, ma *i Context Switch generano un overhead elevato*. Tramite i thread, si puo' risolvere questa problematica.
	Con i thread, si evita l'overhead *per la commutazione del processo*, ma rimane quello dovuto *all'utilizzo delle risorse*, in quanto i thread utilizzeranno le risorse del processo che li ha creati.
	I thread suddividono lo stato del processo in due parti:
		1) *Stato delle Risorse* : Associato al processo (che li ha generati)
		2) *Stato dell'Esecuzione* : Associato ai singoli thread.
	*Caratteristiche del Thread*
		Un thread consiste delle informazioni necessarie per rappresentare un contesto d'esecuzione in un processo:
			1) *TID* : Identificatore di ciascun thread nel processo
			2) *Valori dei registri*
			3) *Stack*
			4) *Politica di Scheduling e Priorita'*
			5) *Maschera dei Segnali*
			6) *Errno*
			7) *Dati specifici*
		Ogni cosa all'interno di un processo e' condivisibile fra i thread del processo stesso.
		POSIX definisce l'*API ```pthread```* per effettuare operazioni di :
			1) *Gestione* : Creazione, recupero stato, terminazione, attesa...
			2) *Supporto condivisione dati* : Mutex
			3) *Supporto sincronizzazione* : Variabili di Condizione
	*Libreria Pthread*
		*Identificazione dei thread*
			Ogni thread ha un proprio *TID* univoco. L'ID del thread *ha senso solo nel processo* cui appartiene, ed e' dato dal tipo *pthread_t*
			Un thread puo' ottenere il proprio ID tramite ```pthread_self```, che restituisce un *unsigned long int* che rappresenta il proprio TID. Questa funzione puo' essere usata con ```pthread_equal``` per controllare se il proprio TID corrisponde a quello richiesto.
		*Creazione di thread*
			La function per la creazione di thread e' ```pthread_create```, alla quali vanno passati tid, argomenti, routine di avvio e argomenti della routine.
			Quando vengono creati dei thread, *non c'e' garanzia su quale viene eseguito per primo*, il thread creato o quello invocante. Il nuovo thread ha accesso allo spazio di indirizzi del processo, ed eredita l'ambiente e la maschera dei segnali (**L'insieme dei segnali pendenti e' quindi *cancellato, non ereditato***)
		*Terminazione di thread*
			Se un qualsiasi thread in un processo chiama ```exit```, allora l'intero processo termina, compresi *tutti i thread al suo interno*.
			Analogamente, quando l'azione di default e' di terminare il processo, *il segnale inviato al thread terminera' l'intero processo*.
			Un singolo thread puo' uscire in tre modi, arrestando il suo flusso di controllo, senza terminare il processo:
				1) *Ritornare dalla routine d'avvio*, il valore di ritorno e' il codice d'uscita
				2) *Cancellazione da un altro thread*, tramite ```pthread_cancel```
				3) *Chiamata alla function* ```pthread_exit```
			Quando un thread termina, il suo valore di ritorno puo' essere visto ed usato dagli altri thread, tramite la function ```pthread_join```. Tramite questa funzione, il thread chiamante *si blocchera' finche' il thread specificato termina*. In quel momento, il puntatore al valore di ritorno *sara' disponibile agli altri thread*.
			Usando ```pthread_join```, poniamo il thread nello stato **detached**, in modo che le sue risorse possano essere recuperate. Se non si e' interessati al valore d'uscita, si puo' impostare retval a NULL.
		*Cancellazione di thread*
			Un thread puo' cancellarne un altro tramite la function ```pthread_cancel```, passando il TID del thread da cancellare come parametro.
			Per default, questa function fa si che il thread specificato dal tid si comporti come se avesse chiamato ```pthread_exit```, con l'argomento di *PTHREAD_CANCELED*. ```pthread_cancel``` non attende che il thread termini.
		*Distacco di un thread*
			Una chiamata a ```pthread_join``` fallisce per un thread distaccato, restituendo *EINVAL*. Un thread si puo' distaccare chiamando ```pthread_detach```.
		*Attributi dei thread*
			Un thread puo' essere creato senza specificargli i parametri, nel cui caso usera' quelli di default. Altrimenti, si puo' usare `pthread_attr_t` per modificarne gli attributi. 
			Tramite `pthread_attr_init` si inizializza la struttura degli attributi, che conterra' i valori di default per tutti gli attributi di thread supportati.
			Per liberare la memoria degli attributi, si usa `pthread_attr_destroy`. Se un'implementazione di `pthread_attr_init` ha allocato memoria *dinamica*, la chiamata a `pthread_attr_destroy` la libera.
			La struttura `pthread_attr_t` e' *opaca alle applicazioni*, cio' significa che le applicazioni *non conoscono nulla circa la struttura interna*, favorendone la portabilita'.
	*Thread e Segnali*
		Ogni thread ha una propria maschera di segnali. I thread individualmente *possono bloccare i segnali*, ma se un thread modifica l'azione associata ad un dato segnale, *tutti i thread condivideranno l'azione*.
		I segnali sono consegnati *ad un singolo thread nel processo*. Per inviare un segnale ad un thread, si usa `pthread_kill`. Con signo pari a 0, possiamo *verificare l'esistenza* del thread.
	**MUTEX E VARCOND**
		Quando molteplici thread di un processo condividono la stessa memoria, e' necessario che ciascun thread *mantenga la coerenza dei propri dati*.
		Se ciascun thread usa variabili che gli altri non leggono o modificano, non vi e' alcun problema di consistenza. Se invece i thread leggono o modificano variabili condivise, si devono *sincronizzare* affinche' non vi siano race condition o problemi di consistenza dei dati.
		*Quando un thread modifica una variabile, gli altri potenzialmente possono riscontrare inconsistenza nella lettura dei dati*.
		**SINCRONIZZAZIONE THREAD**
			*Mutex*
				Un mutex e' un oggetto che permette a processi o thread di *sincronizzare l'accesso ai dati condivisi*. Un mutex ha due stati:
					*Bloccato* : Gli altri thread che tentano di bloccarlo restano in attesa
					*Libero* : Quando un thread rilascia il mutex, uno dei thread in attesa lo acquisisce.
				Ogni volta che un thread ha bisogno di accedere a dati condivisi, acquisisce il mutex, e lo rilascia ad azione completata. In questo modo si previene l'inconsistenza dei dati.
				Il mutex e' una variabile di tipo `pthread_mutex_t`, e si puo' inizializzare:
					*Staticamente* : Impostandolo al valore costante *PTHREAD_MUTEX_INITIALIZER*
					*Dinamicamente* : Invocando `pthread_mutex_init`
				Se allochiamo dinamicamente il mutex, e' necessario richiamare `pthread_mutex_destroy` per liberare la memoria.
				Per bloccare il mutex, si usa `pthread_mutex_lock`, oppure `pthread_mutex_trylock` se si vuole far decidere se ci sono alternative rispetto alla normale attesa.
				Per sbloccare il mutex, si richiama `pthread_mutex_unlock` : 
					Se vi e' piu' di un thread in attesa, *una politica di scheduling decide quale acquisira' il mutex*.
				*Attributi del mutex*
					Per default, un mutex puo' essere usato *solo da thread dello stesso processo*.
					Utilizzando l'attributo *PTHREAD_PROCESS_SHARED*, si permette a thread di altri processi di usare il mutex. Gli oggetti attributo vanno inizializzati, ed infine distrutti per non sprecare memoria.
			*Variabili di Condizione*
				Le variabili di condizione costituiscono *un ulteriore meccanismo di sincronizzazione per i thread*. Mentre i mutex controllano l'accesso dei thread ai dati tramite *polling* (Interrogazione ciclica), le variabili di condizione permettono di *sincronizzare i thread sulla base dell'attuale valore dei dati*.
				Una variabile di condizione e' *sempre associata ad un mutex lock*.
				Le variabili di condizione hanno tre componenti : 
					1) *Variabile Condizione* : Il meccanismo con cui il thread attende la condizione
					2) *Mutex associato* : Il meccanismo che protegge il predicato
					3) *Predicato* : Condizione o valore che il thread controlla
				Prima di usare una variabile condizione, di tipo `pthread_cond_t`, e' necessario inizializzarla:
					*Staticamente* : Impostandola a *PTHREAD_COND_INITIALIZER*
					*Dinamicamente* : Invocando `pthread_cond_init`
				Successivamente, andra' usata `pthread_cond_destroy` se inizializzata dinamicamente.
				*Attesa sulla condizione*
					Un thread che vuole attendere sulla condizione invoca `pthread_cond_wait`, e potra' attendere per un tempo indefinito. Se invece vuole attendere per un tot di tempo, usera' `pthread_cond_trywait`.
					Quando la condizione si verifica, si puo' usare `pthread_cond_signal` per risvegliare *un thread* in attesa, oppure `pthread_cond_broadcast` per risvegliarli *tutti*.