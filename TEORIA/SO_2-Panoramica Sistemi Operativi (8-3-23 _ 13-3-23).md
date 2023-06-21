
----------------------------------------------------------------------
**II)Classi di SO e Ambienti di Elaborazione**

*Ambienti di Elaborazione*
-------------------------

*Ambienti Non Interattivi*
	I primi ambienti di elaborazione non erano interattivi, ovvero **non era possibile sottomettere una richiesta utente durante l'elaborazione di un *job***.
	L'elaboratore riceveva in input *schede perforate* contenenti istruzioni per svolgere un *job* o *batch di job*, e dopo il calcolo restituiva l'output all'utente, che **solo a quel punto** poteva effettuare un'altra richiesta.
	In questi ambienti, l'obiettivo principale del Sistema operativo era **l'uso efficiente della CPU**.

*Ambienti Interattivi*
	Con questi ambienti si volle risolvere la problematica di poter sottoporre una richiesta utente al sistema durante l'esecuzione, per ridurre il tempo medio di attesa per l'interazione fra utente e sistema, facendo in modo che sia l'utente stesso a decidere cosa avviare.

*Ambienti Real Time*
	Gli ambienti Real-Time furono risultato di alcune necessita' specifiche, come ad esempio i razzi o le sonde. In questi ambienti di calcolo, il computer doveva sottostare a vincoli temporali ben specifici, altrimenti si rischiavano gravi conseguenze.
	Questi ambienti si dividono in:
	*Real Time **HARD***
		Dove i vincoli *devono* essere rispettati (*razzi,sonde,...*), e il superamento di un certo tempo di risposta comportava gravi rischi se non avarie o guasti.
	*Real Time **SOFT***
		Dove i vincoli *possono **NON*** essere rispettati, senza causare gravi problemi. 
	In tutti questi sistemi, vengono usate tecniche speciali per far si' che le elaborazioni vengano svolte nel lasso di tempo prestabilito

*Ambienti Distribuiti*
	Questi ambienti furono sviluppati per permettere agli utenti di usare risorse o dati *distribuiti all'interno di una rete*. Vi erano diversi **nodi**, ciascuno dei quali era una macchina, collegati attraverso una rete, e tramite istruzioni speciali potevano comunicare, scambiarsi dati, utilizzare risorse o effettuare calcoli e istruzioni gli uni con gli altri.

*Ambienti Embedded*
	Gli ambienti embedded furono sviluppati per rendere possibile il controllo di macchine HW tramite computer molto piccoli e poco costosi (*centralina di un'auto, forno,...*). Questi computer volgono elaborazioni utili a controllare il sistema hardware cui sono collegati

*Classi di Sistemi Operativi*
--------------------------

*Sistemi Batch*
	Questi SO avevano come scopo l'uso efficiente della CPU. Elaboravano un job alla volta, avendo in esecuzione un solo programma per volta.

*Sistemi Multiprogrammati*
	Migliorarono l'utilizzo dei dispositivi di I/O. Questi sistemi gestiscono diversi processi in uno stato di parziale completamento per unita' temporale, e a seconda della *priorita'* del programma concede o meno uso della CPU.

*Sistemi Time-Sharing*
	L'obiettivo principale e' la riduzione del tempo di risposta alle richieste effettuate da parte dei processi. Il SO serve tutti i processi a turno, *usando uno scheduling **ROUND-ROBIN***, e utilizza una **TIME-SLICE** affinche' non venga superato un certo tempo d'uso della CPU da parte di un processo. Utilizzavano come principale misura d'efficienza il *Tempo di Risposta* (rt = n*(delta+sigma)) e eta = delta/(delta+sigma), con n = numero utenti, delta = tempo per completare sottorichiesta, sigma = overhead scheduling, eta = efficienza di CPU.

*Sistemi Real-Time*
	Nei sistemi RT, i processi e le azioni devono essere eseguite in un certo lasso di tempo. Il sistema quindi impone specifici vincoli temporali, che verranno rispettati dalle **Applicazioni Real-Time**: programmi che rispondono ad attività in un sistema esterno, in un tempo massimo determinato dal sistema esterno. Se queste applicazioni impiegano troppo tempo, possono verificarsi fallimenti nel sistema. I sistemi RT si dividono in due classi: 
	*Real Time HARD*
		Sistemi in cui il requisito di risposta **DEVE** sempre essere rispettato, in qualsiasi condizione. 
	*Real Time SOFT*
		Il sistema fa di tutto per soddisfare i requisiti di risposta, ma non è detto che ci riesca, soddisfando quindi i requisiti **probabilisticamente**
		
*Sistemi Distribuiti*
	Sistemi che utilizzano le risorse di diversi *nodi*, divisi lungo una *rete*. Ogni nodo è una macchina con le proprie risorse, e gli utenti hanno istruzioni specifiche per far lavorare il computer all'interno della rete. Gestire i fallimenti di rete o dei singoli nodi richiede tecniche speciali.
	
**Struttura di un SO**
----------------------
*Politiche e Meccanismi*
	Il progettista di un SO deve pensare a due livelli distinti:
	1) Decidere cosa va fatto, ovvero decidere un principio secondo cui il SO deve eseguire una funzione (**POLITICA**)
	2) Decidere come va fatto, ovvero quale azione è necessaria per implementare la politica (**MECCANISMO**)
	
*Portabilità ed Estendibilità*
	La portabilità è la semplicità di porting di un software (di essere adattato per essere usato in un nuovo sistema).
	Il porting di un SO riguarda il cambiare le parti del suo codice che dipendono dall'architettura per funzionare con nuovo HW.
	L'estendibilità è la facilità con cui possono essere aggiunte nuove funzionalità ad un sistema SW. In un SO, è necessaria per due scopi:
	1) Incorporare nuovo HW
	2) Fornire nuove caratteristiche per soddisfare nuove richieste degli utenti
	I SO moderni forniscono anche la funzionalità di *plug and play*
	
*SO a struttura Monolitica*
	I primi SO avevano struttura monolitica, in cui l'utente si interfacciava con il SO che a sua volta si interfacciava con la "nuda macchina"
	In questi SO, vi era il problema che solo il sistema poteva interfacciarsi con la macchina, e aveva il codice dipendente dall'HW distribuito in tutto il SO rendendo difficile la portabilità, il testing ed il debugging.
	
*SO a strati*
	Si cercò di ovviare a questi problemi progettando un SO a strati, dove ogni strato è una parte del SO con strato 0 che è HW, e strato N che è l'interfaccia utente. In questi sistemi, ogni strato può utilizzare le funzioni e servizi degli strati inferiori.
	I problemi di questi SO sono che il sistema è rallentato dalla stratificazione, c'è il problema dell'ordinamento degli strati, avevano progettazione complessa, perdita di efficienza nell'esecuzione e limitata espandibilità e portabilità.
	
*SO basati su Kernel*
	I SO basati su kernel utilizzano un insieme definito e piccolo di funzioni chiave, raccolte all'interno del "Kernel", mentre tutto ciò che è superfluo viene implementato come "routine nonkernel". Il kernel è posto prima dell'HW, e l'utente è posto "sopra" le routine nonkernel. Nel tempo questi sistemi si sono evoluti, basandosi su microkernel, o utilizzando moduli caricabili dinamicamente, per snellire il kernel dal codice dipendente dall'HW, e per semplificare testing e debugging, come ad esempio i driver di dispositivo a livello utente.
