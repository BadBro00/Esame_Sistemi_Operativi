--------------------------------------------------------------------------

*Semafori POSIX*
---
*Semafori*
	Un semaforo e' una primitiva usata per fornire un meccanismo di sincronizzazione tra vari processi o thread di un processo.
	Un semaforo, a seconda dei valori assunti, puo' essere:
		*Binario* : Assume valori 0 o 1
		*Contatore* : Assume valori da 0 a K, specificato nell'inizializzazione
	I semafori possono essere:
		*Basati su nome* : Identificati da nomi POSIX per IPC
		*Basati su memoria* : Memorizzati in memoria condivisa
	*Operazioni*
		Un processo puo' eseguire tre operazioni sui semafori:
			*Creazione* : Richiede l'inizializzazione anche del *valore di partenza*
			*wait* : Testa il valore del semaforo, si blocca se e' <=0 o lo decrementa altrimenti
			*post* : Aumenta di uno il valore, ma se un processo e' in attesa su un semaforo <=0, allora risveglia il processo
		Le ultime due operazioni sono *atomiche*, cioe' vengono svolte in un tick di CPU.
	*Semaforo Binario e Mutua Esclusione*
		Un semaforo binario puo' essere usato per imporre la mutua esclusione, utilizzando il fatto che una `wait` su un semaforo con valore <=0 blocca il processo.
		In questo modo, possiamo inizializzare il semaforo a uno, e far fare una wait al processo che vogliamo far partire dopo, mentre il processo che deve partire subito fara' le sue istruzioni ed alla fine fara' una `post` per far partire l'altro processo.
	*Semaforo Contatore e Mutua Esclusione*
		Un semaforo contatore puo' essere usato per la Mutua Esclusione, *sempre insieme ad altri meccanismi*. Esso infatti non puo' garantire mutua esclusione, assumendo anche valori >1, per cui necessita di altri meccanismi come mutex o variabili di condizione.
		Puo' essere usato per *segnare quanti processi possono partire*, tramite il suo valore, che dev'essere sempre >0. Ad esempio, si puo' usare come valore di Sedie nel Barbiere addormentato, o numeri di buffer pieni o vuoti nel Produttore-Consumatore.
	*Semafori basati **su nome***
		*Creazione*
			Per creare un semaforo con nome, bisogna usare `sem_open`, passandogli come argomento una stringa *nome*, le flags e la modalita', e il valore. Un semaforo con nome puo' essere usato per sincronizzare *sia thread che processi*.
		*Chiusura*
			Un semaforo con nome, bisogna usare `sem_close` , che si verifica anche quando viene terminato il processo. I nomi dei semafori POSIX sono *persistenti a livello Kernel* : mantengono il proprio valore anche se nessun processo ha il semaforo aperto.
		*Rimozione*
			Un semaforo con nome e' rimosso dal sistema con `sem_unlink`, che provvede a rimuovere del tutto dal FS il semaforo in oggetto.
			I semafori hanno un contatore di riferimento che tiene traccia *di quante volte sono aperti concorrentemente*.
			Il nome del semaforo puo' essere rimosso dal FS mentre il suo contatore e' maggiore di zero, ma verra' effettivamente rimosso solo quando si verifica l'ultima `sem_close`.
		*Ottenimento Valore*
			Per ottenere il valore di un semaforo, si usa la funzione `sem_getvalue`. Essa copia il valore *attuale* del semaforo, e lo salva in una variabile di ritorno. Seil semaforo e' bloccato, puo' ritornare 0 oppure il valore negativo assunto dal semaforo, il cui valore assoluto e' *il numero di processi attualmente bloccati sul semaforo*.
	*Semafori basati **su memoria***
		*Creazione*
			Per creare un semaforo basato su memoria, si usa la function `sem_init`, cui vanno passati un puntatore ad un oggetto di tipo `sem_t`, un int che indica se il semaforo e' condiviso (*0 se e' condiviso fra i threa del processo, >0 se e' condivisibile fra tutti i processi che lo useranno*), e un intero che e' il *valore iniziale* del semaforo.
		*Distruzione*
			Il semaforo basato su memoria va deallocato con `sem_destroy`
		Tutte le altre operazioni sono analoghe a quelle dei semafori basati su nome.
	*Condivisione di semafori fra processi*
		Il semaforo, per essere condiviso, deve risiedere in un'area di memoria *accessibile da tutti i processi che vogliono condividerlo*, e deve avere il secondo argomento di `sem_init` pari a 1.


--------------------------------------------------------------------------