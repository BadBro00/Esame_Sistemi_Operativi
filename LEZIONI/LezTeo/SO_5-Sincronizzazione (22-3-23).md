**SINCRONIZZAZIONE FRA PROCESSI**
---

*Processi Concorrenti*
	All'interno di un'applicazione, vi possono essere più processi che eseguono il codice, lavorando insieme per uno scopo comune. Questi vengono detti **processi concorrenti** (o *intercomunicanti*)
	Due processi *cooperano* se ciascuno ha bisogno dell'altro per procedere con le proprie operazioni, mentre due processi *competono* se entrano in conflitto sulla ripartizione delle risorse
	Con il termine **concorrenti** ci si riferisce a processi il cui comportamento è influenzato dalla presenza contemporanea di altri processi.
	Con il termine **intercomunicanti** ci si riferisce a processi concorrenti che condividono dati o coordinano le loro attività, coloro che non lo fanno sono detti **indipendenti**.

*Sincronizzazione*
	La sincronizzazione dei processi riguarda i processi *intercomunicanti* e consiste nell'individuare le tecniche usate per *ritardare e ripristinare i processi* e per *implementare le loro interazioni*.
	Il modo in cui i processi interagiscono può essere classificato sulla base del grado di conoscenza che hanno dell'esistenza degli altri processi:
	*Non si vedono fra loro*
		Sono processi indipendenti che non sono fatti per collaborare. In questo caso è il SO che deve preoccuparsi della gestione per la *competizione* delle risorse
	*Vedono altri processi indirettamente*
		Non conoscono direttamente il nome degli altri processi, ma condividono con loro l'accesso a qualche oggetto. Tali processi effettuano *cooperazione*
	*Vedono gli altri direttamente*
		Progettati per lavorare insieme, effettuano *cooperazione*
	*Sincronizzazione per accesso ai dati*
		La sincronizzazione per l'accesso ai dati serve per garantire la consistenza dei dati condivisi. Si tratta di coordinare i processi per implementarne la **mutua esclusione**. 
			In informatica il termine *mutex* (*mut*ual *ex*clusion), indica il meccanismo di sincronizzazione con il quale si impedisce che più processi accedano contemporaneamente agli stessi dati in memoria o ad altre risorse *soggette a race condition*. 
			La mutua esclusione viene implementata usando le **sezioni critiche**:
				Sezioni del codice che possono essere eseguite *solo da un processo per volta*
		Affinchè la mutua esclusione sia possibile, occorrono tre condizioni:
		*Mutua Esclusione*
			Un solo processo per volta può accedere alla sezione critica
		*Progresso*
			Nessun processo fuori dalla sezione critica può impedire ad un altro di entrare
		*Attesa limitata*
			Nessun processo deve attendere *indefinitivamente* prima di entrare nella sezione critica
		Queste ultime due garantiscono che non si verifichi mai la **starvation**
	*Sincronizzazione per il controllo*
		Serve per coordinare le attività dei processi in modo da eseguirli nell'ordine desiderato. Viene implementata mediante l'uso delle **operazioni atomiche**, il mezzo che assicura l'esecuzione di una sequenza di istruzioni senza essere prelazionati. Quindi, un'operazione atomica *non può essere eseguita in maniera concorrente con un'altra operazione che **coinvolge gli stessi dati***.
	**Race Condition**
		Nell'ambito del SO, le *race condition* sono situazioni che si verificano quando due processi accedono alla stessa risorsa contemporaneamente. Per evitarle, bisogna assicurarsi che solo un processo per volta possa accedere e modificare i dati in comune. Questa condizione richiede una forma di sincronizzazione fra i processi
	**Condizioni di Bernstein**
		Dato un programma *sequenziale* è possibile stabilire un criterio per determinare se più istruzioni possano essere eseguite *in maniera concorrente*. Tale criterio è espresso dalle *condizioni di Bernstein*, che permettono di prevenire le race condition, verificando per ogni coppia di processi se vengono soddisfatte le seguenti condizioni:
			1) $range(i) \cap range(y) = \emptyset$
				**Agiscono su aree di memoria differenti**
			2) $range(i) \cap dominio(y) = \emptyset$
				**L'area su cui agisce un'istruzione non modifica l'area da cui dipende l'altra**
			3) $dominio(i) \cap range(y) = \emptyset$
				**Viceversa della condizione 2**
		Quando un dominio di istruzioni rispetta le condizioni di Bernstein, il loro esito complessivo risulterà sempre lo stesso, indipendentemente dall'ordine e dalla velocità d'esecuzione.
		Altrimenti, in caso di violazioni, gli errori dipenderanno *dall'ordine di esecuzione*, e dalle *velocità relative*, generando dati *inconsistenti* e race condition.

**Approcci alla sincronizzazione**
---
*Approcci*
	Ci sono vari modi per soddisfare i requisiti della mutua esclusione:
	*Approcci Software*
		Consistono in algoritmi che gestiscono la mutua esclusione *senza alcun supporto da parte del SO* o del *linguaggio di programmazione*
	*Approcci Hardware*
		Istruzioni macchina *speciali* e disabilitazione delle interruzioni, che hanno il vantaggio di *ridurre l'overhead*, ma non sono soddisfacenti.
	*Approcci SO/Linguaggio di programmazione*
		Consistono in costrutti, funzioni e strutture dati.
	**Ciclare** - *Approccio Software*
		Un processo P0 o P1, che vuole eseguire la sua sezione critica, controlla la variabile globale condivisa *turno*
		Se questa è uguale all'identificatore di uno dei processi (0 o 1), il processo corrente può entrare nella propria sezione critica, altrimenti resta a *ciclare*, in attesa che la variabile turno assuma il valore del proprio identificativo.
		Questa situazione prende il nome di **buisy waiting**, e non è raccomandata poichè va a sprecare lavoro da parte della CPU
```C
while( Processo in CS o sta eseguendo operazione indivisibile){
	//do nothing
}
```
-
	**Bloccare** - *Approccio Hardware*
		Per evitare le attese attive, un processo che è in attesa di entrare in una sezione critica deve andare *nello stato Blocked*, invece di ciclare inutilmente. Lo stato del processo dovrebbe essere impostato a ready *solo quando gli sarà permesso di entrare nella CS*:
```C
if( Processo in CS o sta eseguendo operazione indivisibile ){
	block();
}
```
-
	Entrambe le soluzioni possono evitare race condition ma sono realizzate in due modi diversi. Nell'approccio *software*, viene adottata una complessa organizzazione di controlli per evitare la race condition. Il secondo approccio invece utilizza *alcune caratteristiche dell'hardware* per semplificare questo controllo.

*Approccio Hardware*
	Nell'approccio HW, la sincronizzazione viene implementata utilizzando le **Variabili di lock**, ovvero variabili condivise, e istruzioni macchina speciali fornite dall'architettura.
	Su un sistema monoprocessore, la soluzione più semplice è quella di permettere a ciascun processo di disabilitare le interruzioni non appena entra nella sezione critica, in modo da evitare il *prelazionamento* del proceso, e di riabilitarle non appena ne esce. Questo approccio però ha dei difetti, e non è attuabile su un sistema multiprocessore, in quanto *le altre CPU continuerebbero l'esecuzione e potrebbero accedere alla memoria condivisa*.
	Per questi motivi, i SO implementano le sezioni critiche e le operazioni atomiche attraverso *istruzioni indivisibili* fornite dal computer, insieme a variabili condivise dette

**Variabili di Lock**
	Le variabili di Lock sono variabili a due stati
	Stato *aperto* -> 0
	Stato *chiuso* -> 1
	Per cambiare il valore del lock, vengono utilizzate particolari istruzioni macchina, che prendono il nome di *istruzioni indivisibili*
	Quando un processo vuole eseguire una sezione critica, legge il contenuto della variabile di lock e:
	*Se il lock è aperto* (0)
		Il processo imposta il valore del lock a *chiuso*(1), ed esegue la sua sezione critica, per poi re-impostarne il valore ad *aperto*(0)
	*Se il lock è chiuso*(1)
		Il processo deve attendere che il valore del lock ritorni *aperto*(0)
	Per evitare *race condition* nell'impostazione del valore della variabile di lock, viene utilizzata un'istruzione indivisibile per lettura e chiusura, detta
	*Test and Set*
		L'istruzione *TSL* è un'operazione indivisibile che implementa il seguente algoritmo atomicamente:
```C
function test-and-set(var i : integer): boolean
begin
	if i=0 then
	begin
		i := 1
		test-and-set := true
		end
	else
		test-and-set := false
		end
```
-
		La CPU che esegue l'istruzione TSL blocca il bus di memoria per impedire che le altre CPU accedano alla memoria. In pratica, l'istruzione TSL legge il valore dell'argomento che gli viene passato, e se il valore è 0 lo rimpiazza con 1 e ritorna vero, altrimenti ritorna falso.
		*Vantaggi*
			Tipo di approccio che si può applicare con un *qualunque numero* di CPU
			Semplice, e facile da verificare
			Garantisce la mutua esclusione
		*Svantaggi*
			Busy waiting : i processi che attendono di eseguire la sezione critica restano in *attesa attiva*, quindi la CPU è utilizzata inutilmente per cicli d'attesa.
			*Starvation* : è presente in quanto non è garantita l'attesa limitata
	*Swap*
		Questa function prevede di *salvare il valore del lock in una variabile temporanea, per poi impostarlo a "chiuso", e ritornare il valore iniziale del lock*. 
		In questo modo, se ritorna *chiuso*, sappiamo che il lock era precedentemente chiuso, ed il fatto che lo re-impostiamo a chiuso cambia poco.
		Se ritorna *aperto*, sappiamo che il lock era aperto, e *lo chiudiamo tramite l'istruzione swap, così da assegnare il lock al processo che effettua la chiamata swap*



------
*Approccio Software*
	Questo approccio utilizza l'attesa attiva per ritardare un processo e fa uso di una complessa organizzazione di condizioni logiche per assicurare l'assenza di *race condition*. Gli approcci algoritmici sono **indipendenti dalla macchina hardware**.

**Algoritmi per due processi**
---
*Primo tentativo*
```C
var turn : 1...2;
begin
	turn := 1;
//P1                                          //P2
Parbegin                                      Parbegin
	repeat                                        repeat
		while turn = 2                               while turn = 1
			do {niente};                                 do {niente};
		{/*Sezione critica*/}                        {/*Sezione critica*/};
		turn := 2;                                   turn := 1;
		{/*Resto del ciclo*/}                        {/*Resto del ciclo*/}
	forever;                                      forever;
Parend;                                       Parend;
end;                                          end;
```
-
	La variabile *turn* può assumere due valori, 1 o 2, e viene inizializzata ad uno. Il processo P1 può entrare nella sezione critica **se la variabile turn ha valore 1**, mentre P2 può entrare **se turn ha valore 2**. In questo modo è garantita la mutua esclusione.
	Questo algoritmo soffre del fenomeno *buisy waiting*, quindi ci sono tre conseguenze negative:
	1) Non viene soddisfatta la proprietà dell' *attesa limitata*
	2) Se un processo *fallisce*, l'altro processo rimane bloccato **per sempre**, per cui *viene violata la proprietà del progresso*
	3) La *velocità d'esecuzione* è data dal processo più lento.
*Secondo tentativo*
```C
var c1,c2 : 0...1;
begin
	c1 := 1;
	c2 := 1;
//P1                                          //P2
Parbegin                                      Parbegin
	repeat                                        repeat
		while c2=0                               while c1 = 0
			do {niente};                                 do {niente};
		c1 := 0                                      c2 := 0
		{/*Sezione critica*/}                        {/*Sezione critica*/};
		c1 := 1                                      c2 := 1;
		{/*Resto del ciclo*/}                        {/*Resto del ciclo*/}
	forever;                                      forever;
Parend;                                       Parend;
end;                                          end;
```
-
	Ogni processo dovrebbe avere *la propria chiave per l'accesso alla sezione critica*, così se uno dei due fallisce, l'altro potrà comunque entrare nella propria sezione critica. 
	In questo algoritmo, vengono usate due variabili (*c1 e c2*), che possono essere considerate come **flag di stato** per P1 e P2.
	Il valore 0 indica che è in sezione critica, mentre 1 che non lo è.
	Prima di entrare in sezione, ogni processo controlla che l'altro non sia già entrato in sezione:
		In caso positivo, continua a ciclare finchè l'altro non ne esce; In caso negativo, entra in sezione.
	Se un processo fallisce mentre è in sezione critica, o dopo aver posto il suo flag a 0, l'altro rimarrà bloccato per sempre.
	Per evitare questo problema, le condizioni
```C
while(c2=0) {do niente};                      while(c1=0){do niente}
c1 := 0;                                      c2 := 0;
```
-
	Possono essere invertite. In questo modo, c1 sarà impostato a 0 *prima* che P1 controlli il valore di c2, e quindi entrambi i processi non potranno trovarsi nelle rispettive sezioni critiche allo stesso momento. Tuttavia, se entrambi *tentano* di entrare allo stesso momento, sia c1 che c2 saranno impostati a 0, per cui entrambi i processi aspetteranno l'un l'altro indefinitivamente. Questa situazione è detta **deadlock**.

**Algoritmo di Dekker**
```C
var turn : 1...2;
	c1,c2 : 0...1;
begin
	c1 := 1;
	c2 := 1;
	turn := 1;
//P1                                          //P2
Parbegin                                      Parbegin
	repeat                                        repeat
		c1 := 0;                                     c2 := 0;
		while c2=0 do                               while c1=0 do
			if turn=2 then                             if turn=1 then
			begin                                      begin
				c1 := 1;                                  c2 := 1;
				while turn=2                              while turn=1
					do {niente};                              do {niente};
				c1 := 0;                                  c2 := 0;
			end                                        end
		{/*Sezione critica*/}                        {/*Sezione critica*/};
		turn := 2;                                   turn := 1;
		c1 := 1;                                     c2 := 1;
		{/*Resto del ciclo*/}                        {/*Resto del ciclo*/}
	forever;                                      forever;
Parend;                                       Parend;
end;                                          end;
```
-
	L'algoritmo di Dekker combina le soluzioni adottate nei due algoritmi precedenti.
	Per evitare i vari problemi è necessario imporre un *ordine di attività* dei processi
	Se c'è competizione, si usa la variabile *turn* del primo algoritmo per indicare a quale processo dovrebbe essere concesso di entrare nella sezione critica. Nel caso in cui non ci sia competizione, *turn non ha effetto*.
	Quando un processo vuole entrare in sezione critica, mette il proprio flag a 0. L'istruzione successiva (*while...do*) serve a controllare se anche l'altro processo vuole entrare in sezione critica. Se ciò è falso, allora il processo può entrare in sezione critica, saltando il ciclo while. In caso contrario, entra nel while. In questo ciclo, il processo effettua un altro controllo:
		Prima sblocca la flag per la sezione critica, poi con un altro ciclo while attende *finchè la variabile turn non ha valore uguale all'identificativo del processo*
	Mediante questi accorgimenti, l'algoritmo **soddisfa la mutua esclusione**, ed inoltre *evita i deadlock*. Il valore attuale di turn ad ogni istante *non è determinante per la correttezza dell'algoritmo*

**Algoritmo di Peterson**
```C
var flag : array[0...1] of boolean;
	turn : 0...1;
begin
	flag[0] := false;
	flag[1] := false;
//P1                                          //P2
Parbegin                                      Parbegin
	repeat                                        repeat
		flag[0] := true;                              flag[1] := true;
		turn := 1;                                    turn := 2
		while flag[1] and turn=1                      while flag[0] and turn = 0
				do {niente}                                   do {niente};
		{/*Sezione critica*/}                        {/*Sezione critica*/}                    
		flag[0] := false;                            flag[1] := false;
		{/*Resto del ciclo*/}                        {/*Resto del ciclo*/}
	forever;                                      forever;
Parend;                                       Parend;
end;                                          end;
```
-
	L'algoritmo di Peterson risolve il problema della mutua esclusione *in modo più semplice*.
	La variabile *turn* indica a chi è concesso entrare in sezione critica, mentre l'array di flag indica *se il processo è pronto ad entrarci*, e l'algoritmo utilizza un array di flag contenente una flag *per ogni processo*.
	Un processo imposta la sua flag a true quando vuole entrare in sezione critica, mentre lo imposta a false quando ne esce. L'ID del processo è usato come indice per accedere al flag di stato nell'array *flag*
	Questo algotirmo **garantisce la mutua esclusione**, e *non è possibile che i due processi si blocchino a vicenda*. Inoltre, *può essere generalizzato nel caso di n processi*.

**ALGORITMI PER N PROCESSI**
---
*Algoritmo del Panettiere (**BERKLEY**)*
```C
const n = ... ;
var choosing : array[0....n-1] of boolean;//Flag per scelta
    number : array[0....n-1] of integer;
begin
	for j:=0 to n-1 do
		choosing[j] := false;
		number[j] := 0;
Parbegin
	//Processo i
	repeat
		choosing[i] := true;
		number[i] := max(number[0],...,number[n-1])+1;//Scelgo numero max fra scelti, +1
		choosing[i] := false;
		for j=0 to n-1 do
		begin
			while choosing[j] do {niente};
			while number[j] != 0 and (number[j],j) < (number[i],i)
				do {nothing};
		end
		{/*Sezione critica*/}
		number[i] := 0;
		{/*Resto del ciclo*/}
	forever
	//Processo j
	repeat....
	....
Parend
end
```
-
	Questo algoritmo è basato su uno schema comunemente usato nelle *panetterie*:
		All'ingresso, ogni cliente riceve un numero, e si serve sempre il cliente con il numero più basso.
	Le strutture dati comuni sono:
	*Choosing[i]*
		E' un array di flag booleane, che indica se *Pi è impegnato nella scelta di un numero*
	*Number[i]*
		Contiene il numero scelto dal processo Pi; number[i] =0 *se Pi non ha scelto un numero dall'ultima volta che è entrato in sezione critica*
	Per ovviare al fatto che possono esserci due numeri uguali, nei due cicli while si controlla se ci sono processi che hanno un numero minore del processo corrente, ed eventualmente, a parità di numero, se ci sono numeri *con ID minore* del processo Pi. 
	In questo modo, un processo che vuole entrare in sezione critica favorisce un processo che ha scelto un numero minore, o *eventualmente ha ID minore* in caso di parità del numero scelto.

**APPROCCIO SO**
---
*Message Passing*
	I meccanismi di **Inter Process Communication** sono essenzialmente:
	*Semafori*
		Variabili su cui sono definite operazioni *indivisibili*
	*Monitor*
		Costrutti linguistici che permettono di *incapsulare* le sezioni di codice che hanno funzioni di comunicazione e sincronizzazione
	*Message Passing*
		Meccanismi di comunicazione in stile *I/O* per il trasferimento di informazioni tra due o più processi.

*Semaforo*
	E' una particolare *struttura di sincronizzazione*. Consiste in una variabile intera *condivisa*, a **valori non negativi**, che può essere soggetta solo alle seguenti operazioni:
	*Inizializzazione*
		Impostazione del suo valore iniziale, fattibile tramite *keyword* e specificata come parte della sua dichiarazione
	*Operazioni Indivisibili*
		Le operazioni effettuabili sui semafori sono solo due: *wait* e *signal*
	Il principio fondamentale è il seguente:
		due o più processi possono comunicare attraverso semplici segnali, in modo da sincronizzarsi fra di loro. Le istruzioni usate per questa comunicazione sono *wait* e *signal*
```C
procedure wait(S)
begin
	if S>0
		then S := S-1;
	else blocca il processo su S;
end

procedure signal(S)
begin
	if qualche processo bloccato su S
		then attiva un processo bloccato
	else S := S+1;
end;

//Volendo rendere il semaforo funzionante anche con valori negativi
wait(Semaphore *S){
	S->value--;
	if(S->value < 0){
		aggiungi P a S->list;
		block();
	}
}
signal(Semaphore *S){
	S->value++;
	if(S->value <= 0){
		togli P da S->list;
		wakeup(P);
	}
}
```
-
	L'indivisibilità delle funzioni wait e signal è assicurata dal linguaggio di programmazione, o dal SO che le implementa.
	Quando un processo effettua una *wait* su un semaforo, controlla se il valore è > 0: in tal caso, *decrementa il valore del semaforo* e consente al processo di continuare la sua esecuzione; In caso contrario, blocca il processo sul semaforo.
	Quando un processo effettua una *signal* su un semaforo, controlla se ci sono processi bloccati sul semaforo (*se il suo valore è <= 0*). In tal caso, l'operazione attiva un processo bloccato sul semaforo, altrimenti, incrementa semplicemente di uno il suo valore.
	*Mutua Esclusione*
		Per quanto riguarda la mutua esclusione, possiamo usare i semafori per implementarla.
```C
var sem_CS : semaforo = 1;
Parbegin1)
	//P1                                 //P2
	repeat                               repeat
		wait(sem_CS);                       wait(sem_CS);
		{/*Sezione critica*/}               {/*Sezione critica*/}
		signal(sem_CS);                     signal(sem_CS);
		{/*Parte restante del ciclo*/}      {/*Parte restante del ciclo*/}
	forever                              forever
Parend
end
```
-
		Ogni processo effettua prima una wait, per controllare se può accedere in sezione critica, e se il valore del semaforo non è 1 (*l'altro processo è già entrato*), si blocca sul semaforo sem_CS. Dopodichè, effettua la sua sezione critica, per poi infine *effettuare la signal* per consentire all'altro processo di entrare in sezione critica
		La condizione di *Mutua Esclusione* è garantita dato che il semaforo è inzializzato a 1
		La condizione di *Progresso* è garantita dal fatto che un processo che effettua la *wait* ottiene accesso alla sua CS a meno che non vi sia già un altro processo
		La condizione di *Attesa Limitata* non è verificata, in quanto potrebbe verificarsi il fenomeno della *Starvation*
		Inoltre, essendo wait e signal funzioni *primitive*, un loro uso scorretto potrebbe portare a problemi di correttezza:
		*Se si sostituisse una signal alla wait* (signal->CS->signal)
			Più processi potrebbero entrare nelle loro CS, con il richio di trovarci con dati inconsistenti.
		*Se si sostituisse una wait alla signal* (wait->CS->wait)
			Un processo, all'uscita dalla CS, rimarrebbe bloccato al suo interno, e gli altri processi che volevano entrare nella loro CS rimarrebbero bloccati indefinitivamente al loro esterno.
	*Semafori **Binari** (mutex)*
		In alcune occasioni, può essere utilizzata una versione semplificata dei semafori, detta **Mutex**.
		Un mutex è un semaforo *binario*, ovvero che può avere uno fra due valori (0/1). E' sempre inizializzato ad 1.
		Le operazioni di wait e signa sono differenti rispetto a quelle effettuate sui semafori normali:
		*wait*
			S := S-1 => S=0
		*signal*
			S := S+1 => S=1
		Ogni volta che un processo ha bisogno di accedere ai dati condivisi, *acquisisce il mutex* (**mutex_lock**);
		Quando l'operazione è terminata, il mutex viene *rilasciato* (**mutex_unlock**), permettendo ad un altro processo di acquisirlo per farlo entrare in sezione critica.
	*Concorrenza Limitata*
		La concorrenza limitata implica che un'operazione può essere eseguita solo da *c* processi, con c>=1
		Il valore del semaforo rappresenta:
		*Se >= 0*
			Il numero di accessi consentiti
		*Se < 0*
			Il numero di processi in attesa
		I semafori utilizzati per implementare la concorrenza limitata vengono definiti *Semafori Contatore*.
	*Segnalazione fra processi*
		La segnalazione viene effettuata quando un processo Pi vuole effettuare un'operazione ai solo dopo che un processo Pj effettua un'operazione aj. Pj effettuerà una *signal* sul semaforo dopo aver svolto l'operazione aj.

*Monitor*
	Un monitor è un *modulo software* che contiene una o più funzioni e procedure, una sequenza d'inizializzazione e variabili locali. Inoltre, può contenere le dichiarazioni di speciali dati di sincronizzazione detti *variabili di condizione* su cui possono essere effettuate solo le operazioni *cond_wait* e *cond_signal*.
	I processi possono chiamare le procedure di un monitor ogni volta che vogliono, ma *non possono accedere* direttamente alle variabili *locali* del monitor.
	I monitor posseggono un'importante proprietà che li rende utili per ottenere la *mutua esclusione*:
		**Ad ogni istante, un solo processo può essere attivo in un monitor**
	![[Pasted image 20230320123912.png]]
	Il monitor ha un punto d'ingresso, rappresentato da una coda: *soltanto il processo in testa può entrare*
		Le altre code presenti sono quelle associate alle variabili di condizione.
	Nel momento in cui un processo entra nel monitor ed invoca una procedura, dovrà attendere che il buffer si svuoti invocando la *cond_wait*.
	Il costrutto monitor fa sì che il processo bloccato rilasci il lock, in maniera tale che un altro processo in attesa possa essere schedulato. Ad un certo punto, un processo segnalerà al processo bloccato che tale condizione si è verificato, tramite la *cond_signal*, per cui il processo si risveglierà.
	La scelta dell'approccio da utilizzare (*Hoare*,*Hansen*,*Mesa*), consente di scegliere quale processo risvegliare.
	*CORPO DI UN MONITOR*
```C
monitor assegnazione_risorse{
	boolean occupato;
	condition x;
	void acquisizione(int tempo){
		if(occupato){
			x.wait(tempo);
		}
		occupato = true;
	}
	void rilascio(){
		occupato = false;
		x.signal();
	}
	void inizializzazione(){
		occupato = false;
	}
}
```
-
		Una variabile di condizione è una variabile con l'attributo *condition*, ed è associata ad una condizione nel monitor. Le uniche operazioni eseguibili su una variabile di questo tipo sono *cond_wait* e *cond_signal*:
			La cond_wait sospende l'esecuzione del processo chiamante sulla condizione; il monitor diventa disponibile per gli altri processi (*il processo si blocca fino a che non arriva una signal*)
			La cond_signal riattiva un processo sospeso sulla condizione c; se i processi sospesi sono molti, ne sceglie uno, se non ce ne sono, non fa niente.
	*Regole per le variabili di condizione*
		Dopo una signal è necessario avere un processo attivo nel monitor, per cui esistono tre regole che consentono di scegliere in che modo risvegliare il meccanismo:
		1) Hoare (*signal urgent*)
			Questa tecnica riattiva immediatamente un processo in attesa sulla variabile per cui la notifica è chiamata, mentre l'altro che ha invocato la cond_signal viene accodato alla coda di attesa della stessa, per essere riattivato quando il processo risvegliato lascia il monitor o si mette in attesa su una variabile di condizione
		2) Hansen (*signal and return*)
			Questo metodo è quello concettualmente più semplice da implementare, poichè il processo che invoca la cond_signal deve uscire immediatamente dal monitor, quindi:
				cond_signal può apparire solo come *istruzione finale* di una procedura del monitor
				dopo la cond_signal, lo scheduler seleziona uno solo dei processi in attesa
		3) Mesa (*signal and continue*)
			Il processo $P_i$ che invoca la cond_signal continua la sua esecuzione, mentre il processo in attesa comincia dopo che questo è uscito dal monitor o si è messo in attesa su una variabile condizionale
	*Semafori vs Monitor*
		Ci sono varie differenze fra semafori e monitor:
			Ad ogni semaforo è associata *una coda di processi in attesa* sul semaforo, mentre in ogni monitor *ad ogni variabile condizionale è associata una coda su cui attendono i singoli processi*
			L'operazione wait su un semaforo è sospensiva *solo se il semaforo non è positivo*, mentre la wait su un monitor *è sempre ed immediatamente sospensiva*
		Per utilizzare un monitor come semaforo, si può implementare questo codice:
```C
type Sem_Mon_type = monitor
var
	busy : boolean;
	non_busy : condition;
procedure sem_wait;
begin
	if busy = true then non_busy.cond_wait;
	busy = true;
end
procedure sem_signal;
begin
	busy : false;
	non_busy.cond_signal;
end
begin {inizialization}
	busy = false
end
```
-
		Nei  processi invece:
```C
//P1                                        //P2
var binary_sem : Sem_Mon_type;               var binary_sem : Sem_Mon_type;
begin                                        begin
Parbegin                                     Parbegin
	repeat                                       repeat
		binary_sem.sem_wait;                         binary_sem.sem_wait;
		{/*Sezione Critica*/}                        {/*Sezione Critica*/}
		binary_sem.sem_signal;                       binary_sem.sem_signal;
		{/*Resto del ciclo*/}                        {/*Resto del ciclo*/}
	forever;                                     forever; 
Parend;                                      Parend;
end;                                         end;
```
-
	![[Pasted image 20230322111253.png]]

**Problemi classici di sincronizzazione dei processi**
	Esistono una serie di problemi classici nella sincronizzazione dei processi, che rappresentano molti dei casi che si presentano più spesso. Essi sono
	1) *Lettori/Scrittori* #LetScrit
	2) *Produttori/Consumatori* #ProdCons
	3) *Barbiere Addormentato* #Barb
	4) *Filosofi a Cena* #Filosofi

**SPIEGAZIONI**
---
#ProdCons  *Buffer Limitato*
	Questo problema rappresenta una classica situazione fra processi. Vi sono due "classi" di processi: un *produttore* e un *consumatore*, ma possono esserci più di due processi in esecuzione.
	Il produttore "produce" un elemento, e lo pone in un buffer (limitato), mentre il consumatore attende che il produttore produca l'oggetto, e lo consuma dal buffer.
	Vi sono alcune regole:
	1) Il produttore *non deve produrre un elemento se il buffer è pieno*
	2) Il consumatore *non deve consumare se il buffer è vuoto*
	3) I due processi devono accedere al buffer *in mutua esclusione*
	A volte, viene inclusa anche una quarta regola:
	4) Gli oggetti nel buffer devono essere consumati *nell'ordine FIFO* (quello con cui sono stati prodotti)
	Un buffer è *pieno* quando un produttore scrive un nuovo elemento al suo interno.
	Un buffer è *vuoto* quando un consumatore estrae un elemento contenuto in esso. 
	Un processo produttore produce *un elemento di informazione alla volta* e lo inserisce in un buffer vuoto. Un processo consumatore *estrae l'informazione, un elemento alla volta,* da un buffer pieno.

#LetScrit 
	Questo problema riguarda due classi di processi : un *lettore* ed uno *scrittore*. Il processo scrittore "scrive" all'interno di un buffer, mentre il lettore "legge" l'elemento scritto, ma possono esserci più di due processi in esecuzione.
	Le regole imposte per questo problema sono le seguenti:
	1) Molti lettori possono effettuare la lettura *concorrentemente*
	2) Solo uno scrittore per volta può scrivere, modificando i dati
	3) La lettura è proibita quando uno scrittore sta scrivendo.
	Alcune volte viene "imposta" una *preferenza*, ovvero che viene "favorito" un tipo di processo rispetto ad un altro, mediante una regola, che impone che un tipo di processo venga eseguito dopo la lettura o la scrittura. In tal caso si parla di *preferenza ai lettori/scrittori*

#Filosofi 
	Vi sono cinque filosofi a cena, seduti ad un tavolo rotondo: ogni filosofo ha di fronte a sè un piatto, mentre fra ogni coppia di filosofi vi sono delle forchette, usate per mangiare. I filosofi alternano momenti di meditazione e momenti in cui mangiano. Per mangiare, un filosofo deve prendere, una alla volta, le due forchette alla sua destra e alla sua sinistra. durante la meditazione le forchette devono essere poste sul tavolo. 
	Il numero di forchette impedisce a tutti i filosofi di mangiare contemporaneamente, quindi bisogna attuare una buona sincronizzazione per fare in modo che i filosofi portino a termine il pranzo senza soffrire di starvation o deadlock.
	La condizione di *correttezza* viene rispettata se un filosofo affamato non attende indefinitivamente per mangiare
	I *deadlock* vengono evitati se i processi non si bloccano rimanendo in attesa l'uno dell'altro
	I *livelock* sono evitati quando i processi non ritardano l'esecuzione a favore degli altri in modo indefinito

#Barb 
	Il problema del barbiere è pensabile come quello di un negozio di un barbiere.
	Il negozio ha una sola poltrona per tagliare i capelli, ed un certo numero di posti d'attesa (N).
	Se non ci sono clienti, il barbiere dorme, e quando arrivano dei clienti, controllano se possono sedersi e il barbiere in tal caso si risveglia e gli taglia i capelli uno alla volta.
	Una corretta sincronizzazione permette al barbiere di "dormire" se non ci sono clienti, di far entrare solo N clienti per volta, e di risvegliare il barbiere per fargli tagliare i capelli quando arriva un cliente.

**SOLUZIONI**
---
*SEZIONI CRITICHE*
#ProdCons 
```C
//Produttore                                            //Consumatore
begin                                                   begin
Parbegin                                                Parbegin
	var prodotto : boolean;                                var consumato : boolean;
	repeat                                                 repeat
		prodotto = false;                                     consumato : false;
		while(prodotto = false)                               while(consumato = false)
		if (esiste un buffer vuoto) then                      if(esiste buffer pieno)
			{/*Produci ednserisci nel buffer*/}               then {/*Consuma*/}
			prodotto = true;                                  consumato = true;
		{/*Parte restante del ciclo*/}                        {/*Resto del ciclo*/}
	forever;                                               forever;
Parend;                                                 Parend;
end;                                                    end;
```
-
	Il produttore controlla ripetutamente se vi sono buffer vuoti : non appena ne trova uno, *produce un elemento e lo inserisce nel buffer, e imposta la variabile prodotto a true*.
	Il consumatore controlla ripetutamente se esiste un buffer pieno : non appena lo trova, *consuma l'elemento del buffer e imposta la variabile consumato a true*.
	**PROBLEMI**
		Visto che entrambi gli accessi al buffer sono nelle sezioni critiche di ciascun processo, allora solo un processo per volta (*produttore o consumatore*) può accedere al buffer ad ogni istante di tempo, anche se avessimo a disposizione più buffer.
		Entrambi i processi soffrono di *buisy wait* controllando se vi sono buffer pieni/vuoti

#LetScrit 
```C
//LETTORE                                   //SCRITTORE
Parbegin                                    Parbegin
	repeat                                     repeat
		if(scrittore sta scrivendo)               if(lettori leggono, o scrittori scrivono)
		then {/*Attendi*/}                        then {/*Attendi*/}
		{/*Leggi*/}                               {/*Scrivi*/} //CS
		if(non ci sono lettori attivi)            if(ci sono letttori/scrittori in attesa)
		then                                      then 
			if(ci sono scrittori in attesa)          //Attiva uno scrittore o tutti i lettori
			then  {/*Attiva scrittore/i*/}
	forever;                                   forever;
Parend;                                     Parend;
```
-

*SEMAFORI*
#ProdCons 
**BUFFER SINGOLO**
```C
type item = ...;
var
	full : semaphore := 0;
	empty : semaphore := 1;
	buffer : array[0] of item;
//PRODUTTORE                            //CONSUMATORE
begin                                   begin
Parbegin                                Parbegin
	repeat                                  repeat
		wait(empty);                            wait(full);
		buffer[0] := ...;                       x := buffer[0];
		signal(full);                           signal(empty);
		{/*Resto del ciclo*/}                   {/*Resto del ciclo*/}
	forever;                               forever;
Parend;                                 Parend;
end;                                    end;
```
**N BUFFER**
```C
const n=...;
type item=...;
var
	buffer : array[0,...,n] of item;
	full : semaphore := 0;
	empty : semaphore := n;
	prod_ptr,cons_ptr : integer;
begin
	prod_ptr := 0;
	cons_ptr := 0;
//PRODUTTORE                              //CONSUMATORE
Parbegin                                  Parbegin
	repeat                                   repeat
		wait(empty);                            wait(full);
		buffer[prod_ptr] := ...;                x := buffer[cons_ptr];
		prod_ptr := prod_ptr + 1modn;           cons_ptr := cons_ptr + 1modn;
		signal(full);                           signal(empty);
		{/*Resto del ciclo*/}                   {/*Resto del ciclo*/}
	forever;                                  forever;
Parend;                                  Parend;
end;                                     end;
```
-
	Il pool di buffer è rappresentato da un array di buffer a singolo elemento, mentre i valori dei semafori indicano rispettivamente il numero di buffer pieni e vuoti, e cons_ptr e prod_ptr vengono usati come indici per l'array di buffer, e sono inizializzati a 0.
	*FUNZIONAMENTO*
		*PRODUTTORE*
			Il produttore attende che ci sia un buffer vuoto (*wait*), e in tal caso produce un elemento e lo inserisce nel buffer di indice prod_ptr. Successivamente, incrementa il valore di prod_ptr di $1 \mod n$ (rendendo array *circolare*), segnala (*signal*) che un buffer da vuoto è passato a pieno, e quindi aumenta il valore di full di 1.
		*CONSUMATORE*
			Il consumatore attende che ci sia un buffer pieno (*wait*), e consuma l'elemento del buffer indicizzato da cons_ptr. Consuma l'oggetto, e poi incrementa cons_ptr di $1 \mod n$ (rendendo l'array *circolare*), e segnala (*signal*) che un buffer si è svuotato, diminuendo il valore del semaforo di 1.
		L'uso dei semafori *empty* e *full* riduce le attese attive, perchè i semafori sono utilizzati per controllare il numero di buffer pieni e vuoti, bloccando i processi in caso non ve ne siano.
		Il *livello di concorrenza* di questo algoritmo è 1, in quanto ad ogni istante di tempo viene eseguito *al massimo* un processo, che sia produttore o consumatore. L'algoritmo scritto in questo modo assicura che i buffer siano usati in ordine **FIFO**.


#LetScrit **SOLUZIONE PROF**
	Vi sono *m* lettori ed *n* scrittori che tentano di accedere ad un dato da leggere o scrivere. Più lettori possono leggere concorrentemente, ma solo uno scrittore può essere eseguito per volta.
	Per poter gestire questa situazione, si utilizzano una serie di contatori:
	*runread*, che identifica il numero di lettori in esecuzione
	*runwrite*, che identifica il numero di scrittori in esecuzione
	*totread*, che identifica il numero **totale** di lettori
	*totwrite*, che identifica il numero **totale** di scrittori
```C
//Lettore/i                                 //Scrittore/i
Parbegin                                    Parbegin
	repeat                                      repeat
		{/*CS*/                                   {/*CS*/
		if runwrite != 0                            if runread != 0 OR runwrite != 0
		then                                        then
		} {/*wait*/}                               } {/*wait*/}
		{/*read*/}                                 {/*write*/}
		{/*CS*/                                    {/*CS*/
		if runread = 0 AND totwrite != 0           if totread != 0 OR totwrite != 0 
		then                                       then
		}{/*Activate writer(s)*/}                  } {/*Activate writer or all readers*/}
	forever;                                    forever;
Parend;                                     Parend;
```
-
	Si utilizzano tre semafori: 
	*reading*, che serve per sapere quando i lettori possono leggere
	*writing*, che serve per sapere quando lo scrittore può scrivere
	Un *Mutex* per la mutua esclusione (quindi inizializzato a 1)
```C
//PRIORITA' LETTORI
var
	totread,runread,totwrite,runwrite : integer;
	reading, writing : semaphore := 0;
	sem_CS : semaphore := 1;
begin
	totread := 0;
	runread := 0;
	totwrite := 0;
	runwrite := 0;
//Lettore/i                                  //Scrittore/i
Parbegin                                     Parbegin
	repeat                                     repeat
		wait(sem_CS);                             wait(sem_CS);
		totread := totread+1;                     totwrite:=totwrite+1;
		if runwrite = 0 then                      if runread=0 AND runwrite=0 then
			runread := runread+1;                     runwrite := 1;
			signal(reading);                          signal(writing);
		signal(sem_CS);                           signal(sem_CS);
		wait(reading);                            wait(writing);
		{/*read*/}                                {/*write*/}
		wait(sem_CS);                             wait(sem_CS);
		runread := runread-1;                     runwrite :=runwrite-1;
		totread := totread-1;                     totwrite := totwrite-1;
		if runread=0 AND totwrite > runwrite      while(runread < totread) do
		then                                      begin
			runwrite := 1;                             runread := runread+1;
			signal(writing);                           signal(reading);
		signal(sem_CS);                           end;
	                                              if runread = 0 AND totwrite > runwrite then
												      runwrite := 1;
												      signal(writing);
											      signal(sem_CS);
	forever;                                   forever;
Parend;                                      Parend;  
end;                                         end;
```
-
	**FUNZIONAMENTO**
		*Lettore*
			Un processo dichiara che è un potenziale lettore per cui, una volta effettuata la wait sul mutex (*per la mutua esclusione*), aggiunge 1 alla variabile totread. Si procede alla verifica di eventuali scrittori in esecuzione, controllando *in mutua esclusione* se runwrite = 0 : se è così, si può leggere, per cui si incrementa la variabile runread e si segnala il semaforo *reading* (+1). A questo punto si esce dalla sezione critica, potendo effettuare la lettura.
			Al termine di questa, si rientra in sezione critica, si decrementano totread e runread, verifica se era l'ultimo lettore e se ci sono scrittori in attesa (runread=0&totwrite>runwrite), e in tal caso si pone *runwrite* a 1 ("attiva" uno scrittore).
			Quindi, si dà la possibilità ad uno scrittore di andare a scrivere, mediante la signal su *writing*. Infine, si abbandona la sezione critica (*signal(sem_CS)*)
		*Scrittore*
			Dopo aver effettuato la *wait(sem_CS)*, si dichiara che è uno scrittore, aggiungendo uno alla variabile totwrite. Per diventare scrittore è prima necessario verificare se ci sono lettori che stanno leggendo, o scrittori che stanno scrivendo : si controlla quindi se runread=0 e runwrite=0. Se ciò è vero, allora il processo può ufficialmente scrivere, e si pone *runwrite* a 1, e si fa una *signal(writing)* per dire che esiste. Dopodichè, è possibile uscire dalla mutua esclusione e fare una *wait(writing)* per confermare la scrittura.
			Dopo di ciò, si rientra in mutua esclusione, si diminuisce di 1 *runwrite* e *totwrite*, e bisogna far leggere tutti i lettori *in attesa*, per cui finchè *totread > runread* si fa una *signal(reading)* per ogni lettore intenzionato. Alla fine, si effettua lo stesso controllo fatto per i lettori : si verifica che non ci siano lettori in corso e se ci sono scrittori in attesa (*runread = 0* e *totwrite>runwrite*), quindi si imposta runwrite a 1 e viene fatta una *signal(writing)* per sbloccare lo scrittore.
			Infine, si abbandona la sezione critica.

#LetScrit  *Priorità ai Lettori*
```C
program lettori_scrittori;
var
	numlettori,numscrittori : integer;
	&mutex1,&mutex2 : semaforo (:=1);
	&UnoAllaVolta : semaforo (:=1);
	&scrittura,&lettura : semaforo (:=1);
procedure lettore;                          procedure scrittore;
begin                                       begin
	repeat                                     repeat
		wait(UnoAllaVolta);                        wait(mutex1);
		wait(lettura);                             numscrittori++;
		wait(mutex2);                              if(numscrittori == 1) then
		numlettori++;                              wait(lettura);
		if(numettori==1) then                      signal(mutex1);
			wait(scrittura);                       wait(scrittura);
		signal(mutex2);                            //SCRIVI:
		signal(lettura);                           signal(scrittura);
		signal(UnoAllaVolta);                      wait(mutex1);
		//LEGGI:                                   numscrittori--;
		wait(mutex2);                              if(numscrittori == 0) then
		numettori--;                               signal(lettura);
		if(numlettori == 0) then                   signal(mutex1);
			signal(scrittura);                forever;
		signal(mutex2);                     end;
	forever;
end; 

begin
	numlettori,numscrittori := 0;
	Parbegin
		lettore:
		scrittore:
	Parend;
end;
```
-
	In questa soluzione ogni lettore che vuole leggere è accettato, a meno che uno scrittore chieda di entrare: in questo caso viene inibito l'accesso ai lettori successivi
	**FUNZIONAMENTO**
		Questa soluzione usa:
		1) Due variabili *numlettori* e *numscrittori* per tenere traccia del numero di lettori e scrittori nel sistema
		2) I semafori binari *mutex1* e mutex2 per evitare inconsistenze quando si modificano le variabili precedenti
		3) Il semaforo binario *UnoAllaVolta* per far sì che *un solo lettore alla volta* possa accodarsi sulla scrittura
		4) Il semaforo binario *Lettura* che viene utilizzato *dagli scrittori per bloccare i lettori*
		5) Il semaforo binario *Scrittura* che viene usato dai lettori *per impedire che lettori e scrittori accedano contemporaneamente ai dati*
		Il primo lettore inibisce gli scrittori ma consente agli altri lettori di leggere. Il primo scrittore inibisce sia lettori che scrittori.
		*Spiegazione LETTORE*
			Quando un lettore vuole leggere, effettua una wait su *UnoAllaVolta*, dopodichè effettua la stessa operazione su *lettura*.
			A questo punto non deve far altro che incrementare il valore di *numlettori*, proteggendo la modifica bloccando il mutex.
			Durante quest'operazione, il processo *controlla se è il primo lettore*:
				Se lo è, *blocca eventuali scrittori* che vogliono scrivere, ma *permette ad altri lettori di leggere concorrentemente*
				Se non lo è, non fa nulla e *continua* eseguendo le prossime istruzioni
			Una volta letti i dati, il processo deve decrementare il valore di numlettori, *ribloccando il mutex*
		*Spiegazione SCRITTORE*
			Quando uno scrittore vuole scrivere non deve fare altro che *incrementare il valore di numscrittori*, sempre bloccando il mutex, e *controllare se è il primo scrittore*:
				Se lo è, allora *blocca tutti i lettori che vogliono leggere*
				Se non lo è *continua* eseguendo le prossime istruzioni
			Prima di poter scrivere, lo scrittore *deve effettuare una wait su scrittura*, in modo da controllare se c'è un altro processo scrittore impegnato.
			Una volta effettuata la scrittura, deve *decrementare il valore di numscrittori* (bloccando il mutex), e *controllare se è l'ultimo processo scrittore*. Se lo è, sblocca *uno dei lettori in attesa*.
		Il semaforo UnoAllaVolta è utile per quando ci sono uno o più lettori impegnati e vengono accettati uno o più scrittori che vogliono scrivere.
		Il primo lettore che vuole leggere effettua la wait su UnoAllaVolta, dopodichè si blocca sull'operazione wait(lettura), perchè il suo valore è già zero. Per questo motivo, tutti i successivi lettori si bloccheranno su UnoAllaVolta perchè il valore di quest ultimo è 0.
		In questo modo, non appena l'ultimo dei lettori termina di leggere, sblocca lo scrittore che scrive.

#Filosofi  *SEZIONI CRITICHE*
	La condizione di correttezza nel sistema dei filosofi a cena è che un filosofo affamato non dovrebbe attendere indefinitivamente quando decide di mangiare
```C
var 
	successful : boolean;
repeat
	successful = false;
	while(not successful)
	do
	{
	if(entrambe le forchette disponibili) then
		prendi forchette una alla volta;
		successful = true;
	}
	if(successful = false) 
	then block(P);
	{/*Mangia*/}
	{//CS
		{/*Posa entrambe le forchette*/}
	}
	if(vicino di sinistra è in attesa della forchetta destra)
	then {/*Activate vicino di sinistra*/}
	if(vicino di destra è in attesa della forchetta sinistra)
	then {/*Activate vicino di destra*/}
	{/*Pensa*/}
forever
```
-
	Un filosofo controlla la disponibilità delle forchette in una sezione critica *nella quale prendere anche le forchette*. Per questo motivo non possono verificarsi race condition. Questa struttura assicura che almeno *alcuni* filosofi possano mangiare ad ogni istante e previene il verificarsi di un deadlock.
	Un filosofo affamato che non trova forchette si blocca, e verrà riattivato quando uno dei suoi vicini lascia una delle sue forchette, tuttavia il ciclo (*while*) causa attesa attiva

#Filosofi *MONITOR*
```C
monitor fc{
	enum{pensa,affamato,mangia} stato[5];
	condition auto[5];
	prende(int i){
		stato[i] = affamato;
		verifica(i);
		if(stato[i] != mangia){
			auto[i].wait();
		}
	}
	void posa(int i){
		stato[i].pensa;
		verifica((i+4)%5);
		verifica((i+1)%5);
	}
	void verifica(int i){
		if((stato[(i+4)%5] != mangia && (stato[(i+1)%5] != mangia) && (stato[i] == affamato)){
			stato[i] = mangia;
			auto[i].signal();
		}
	}
	void codicediinizializzazione(){
		for(int i=0;i<5;i++){
			stato[i] = pensa;
		}
	}
}
```
-
	Questa sitazione è priva di stalli, ma un filosofo può attendere indefinitivamente.
	Per codificare questa soluzione, si devono distinguere i tre diversi stati in cui può trovarsi un filosofo: *pensa*, *affamato* e *mangia*, tramite un array di enum, di dimensione 5.
	Occorre ricordare che, per mangiare, un filosofo deve prendere *entrambe* le forchette ai suoi lati. Per questo motivo, un filosofo può mangiare *solo se* i suoi vicini *non stanno mangiando*
	*FUNZIONAMENTO*
		Il filosofo *i* può impostare la variabile stato[i] a mangia solo se i vicini non stanno mangiando.
		l'istruzione if(( stato[(i+4)%5] != mangia ) && ( stato[(i+1)%5] != mangia )) va a controllare lo stato dei due vicini al filosofo *i* tramite l'array circolare e l'aritmetica modulo 5. Occorre inoltre implementare la struttura condition auto[5], che permette al filosofo di ritardare se stesso se non riesce ad ottenere le forchette che necessita.

#Barb *SEMAFORI*
```C
program barbiere_addormentato;
const sedie N;
var
	coda : integer;
	mutex : semaforo (:=1);
	cliente : semaforo (:=0);
	barbiere : semaforo (:=0):
procedure barbiere:                           procedure cliente:
begin                                         begin
	repeat                                       repeat
		wait(cliente);                              wait(mutex);
		wait(mutex);                                if(coda<sedie){
		coda--;                                          coda++;
		signal(barbiere);                                signal(mutex);
		signal(mutex);                                   wait(barbiere);
		/*Taglia Capelli*/                               /*Taglio Capelli*/
		                                            }else{
		                                                 /*Vai via*/
		                                                 signal(mutex);
	forever;                                    forever
end;                                        end;
```
-
	*SPIEGAZIONE BARBIERE*
		In un negozio di barbiere c'è un solo barbiere, N sedie e una poltrona per tagliare i capelli.
		Il barbiere attende un cliente (si *addormenta*), e quando arriva un cliente, accede in mutua esclusione e decrementa il valore di *coda*, che rappresenta il numero di clienti in attesa.
		Dopodichè, segnala che è libero, ed effettua il taglio (*uscendo dalla mutua esclusione*)
	*SPIEGAZIONE CLIENTE*
		Il cliente, entrando nel negozio, *verifica che ci siano posti liberi*, in mutua esclusione. Se non ce ne sono (cioè se *il numero di clienti in attesa è uguale ad N*), sblocca il mutex e va via.
		Altrimenti, si siede (*incrementa il valore di coda*), segnala la sua presenza e si mette in attesa del barbiere.
		Una volta che questo è libero, si fa tagliare i capelli ed esce.
