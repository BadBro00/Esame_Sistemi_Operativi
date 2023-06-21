-----------------------------------------------------------------------------------------
**FILE SYSTEM UNIX**
---
*File e Directory*
	La maggior parte dei file in UNIX sono di due tipi : *file regolari* o *directory*. Esistono anche altri tipi di file :
	*Regolari*:
		E' il tipo più classico e diffuso di file in un file system, per il kernel non c'è distinzione fra file di testo e binari
	*Directory*:
		Sono file speciali, al cui interno vi sono altri file. Contengono un nome e puntatori ad altri file.
	*File speciali a blocco*:
		Usati per rappresentare dispositivi che consistono in un insieme a blocchi ad indirizzamento casuale (*dischi*)
	*File speciali a caratteri*:
		Usati per rappresentare dispositivi che costituiscono flussi di caratteri (*terminali, stampanti,...*)
	*FIFO*
		Metodo di IPC, per la comunicazione fra processi
	*Socket*
		Tipo di file usato per la comunicazione *su rete* fra processi
	*Link Simbolici*
		Link al path di un file, usati per accedere ad un file tramite il *path name*
	Sui file possono essere svolte diverse operazioni, e per controllare le informazioni su di un file, esistono le system call:
	*Stat* : 
		Ritorna una struttura dati contenente le informazioni sul file specificato da *path*, come la data di creazione, il size, l'ultima modifica...
	*Fstat*:
		Ritorna una struttura dati contenente le informazioni sul file specificato da *filedescr*
	*Lstat*:
		Ritorna informazioni *sul link simbolico*, e non sul file cui esso punta.
	Non è necessario avere permessi di lettura per eseguire con successo una di tali system call
	![[Pasted image 20230509125539.png]]
	L'informazione sul campo *st_mode* è necessaria per capire di che tipo di file si tratta:
	![[Pasted image 20230509125611.png]]
	*UID e GID*
		Lo User ID è l'ID dell'utente proprietario del file, mentre il Group ID è l'ID del gruppo cui il proprietario appartiene.
		Tali informazioni ci permettono di risalire al proprietario del file, e se sono settati i permessi per il gruppo, anche a chi ha i permessi sul file.
		A ciascun processi vengono associati i seguenti identificativi:
			*Real UID e Real GID* : Identificano l'utente proprietario ed il gruppo cui egli appartiene
			*Effective UID, Effective GID e Supplementary GID* : Determinano i permessi d'accesso al file
			*Saved Set-UID e Saved Set-GID* : Contengono copia dell'effective UID e GID durante l'esecuzione di un file
				Tale informazione è utile per mantenere traccia del proprietario se durante l'esecuzione il file viene eseguito con *su* o *impersonando* un altro utente
		*Set User ID*
			Normalmente, un file viene eseguito con i permessi di chi lo manda in esecuzione, non di chi lo possiede. E' però possibile che un file venga eseguito da un utente A *impersonando* un altro utente B. Quando ciò accade, serve mantenere l'informazione di chi effettivamente ha creato il file, e tale metodo è l'Effective User ID.
			Potrebbe essere necessario che un programma venga eseguito con permessi maggiori di chi lo esegue. Ad esempio, il comando passwd (*per il quale il set user id è settato*), è eseguibile da chiunque, e deve avere possibilità di cambiare il file */etc/passwd*.
		*Set Group ID*
			Analogamente, è possibile mandare in esecuzione un processo con Effective Group ID uguale al Group ID dell'eseguibile, ed il relativo flag è detto Set-Group-ID. Se tale bit è applicato ad una directory, *i file creati in tale directory erediteranno il GID dalla directory*.
	*Sticky Bit*
		Bit che permette di richiedere al kernel che *l'immagine del segmento di testo di un processo resti allocata nell'area di swap*, anche dopo la sua terminazione. Se usato per le directory (**S_IVTX**), i file possono essere rinominati o cancellati *solo se l'utente ha i permessi di scrittura sulla directory e se vale una delle seguenti condizioni*:
			E' il proprietario del file
			E' il proprietario della directory
			E' root
		Esso viene usato sulle directory per cui tutti gli utenti devono poter creare file : gli utenti non dovrebbero avere la possibilità di rinominare o cancellare file altrui.
		Le tre categorie di permessi (*read, write, execute*) sono usate da varie funzioni in maniera differente.
		Quando si vuole aprire un qualunque tipo di file mediante il nome, è necessario avere i permessi di esecuzione in ciascuna directory citata dal nome (*inclusa la corrente*):
			1) Ciò motiva il fatto che il bit del permesso di esecuzione per le directory è anche detto *permesso di ricerca*
			2) Per aprire */usr/include/stdio.h* dobbiamo avere i permessi di esecuzione nella directory */*, nella directory */usr* e nella directory */usr/include*, oltre ai permessi sul file in base a come cerchiamo di aprirlo.
			3) I permessi di lettura ed esecuzione su una directory hanno diversi significati : 
				Leggere la directory ci permette di elencarne il contenuto
				L'esecuzione della directory ci permette di passare attraverso la directory
			4) I permessi di scrittura determinano se possiamo *aprire un file per la scrittura*
			5) E' necessario avere permessi di scrittura su di un file per specificare il flag *O_TRUNC* nella *open()*
			6) Non è possibile creare un file o una directory a meno che non si abbiano permessi di scrittura ed esecuzione sulla directory
			7) Per cancellare un file esistente, è necessario avere permessi di scrittura ed esecuzione nella directory che contiene il file
			8) E' necessario avere i permessi di esecuzione su un file se lo vogliamo eseguire usando una delle funzioni della famiglia *exec()*. Inoltre, dev'essere un file *regolare*
	*Test di accesso ai file del kernel*
		I permessi di accesso quando un processo apre, cancella o crea un file, dipendono dal proprietario del file (*st_UID,st_GID*), gli *Effective ID* del processo, e il *supplementary Group ID* del processo :
			Gli ID del proprietario sono una prerogativa dei file, i due effective ID e il supplementary GID sono una prerogativa del processo
			I passi eseguiti in sequenza sono:
				1) Se l'effective UID del processo è 0, l'accesso è consentito
				2) Se l'effective UID del processo coincide con il proprietario (*ovvero, il processo è il proprietario*), l'accesso è consentito se l'utente ha i relativi bit di permesso impostati, altrimenti è negato
				3) Se l'effective GID del processo o uno dei supplementary GID coincidono con il GID del file, l'accesso è consentito se i permessi d'accesso al gruppo sono impostati
	*Proprietà dei nuovi file/directory*
		Lo UID dei nuovi file e nuove directory è impostato all'UID del processo che li crea. Per determinare il GID, POSIX consente all'implementazione di scegliere fra due modi:
			1) Il GID di un nuovo file può essere *l'effective GID del processo*
			2) Il GID di un nuovo file può essere *il GID della directory*
		Linux consente di scegliere l'una o l'altra tramite flag
	*Dimensione dei file*
		Il campo *st_size* della struct stat contiene la dimensione *in byte* del file, e ciò ha senso solo per i file regolari, directory e link simbolici. Se presenti, *st_blksize* e *st_blocks* si riferiscono rispettivamente al miglior fattore di blocco per eseguire operazioni di I/O sul file, e al numero di blocchi da 512 byte allocati per il file.
	*File System e partizioni*
		Consideriamo il FS di UNIX. Possiamo pensare ad un HD diviso in più partizioni, dove ognuna può contenere un file system.
		![[Pasted image 20230510102940.png]]
		L'*index-node* è una struttura di controllo, associata ad ogni file : molti nomi dei file possono essere associati con lo stesso i-node.
		![[Pasted image 20230510103156.png]]

-----------------------------------------------------------------------------------------
