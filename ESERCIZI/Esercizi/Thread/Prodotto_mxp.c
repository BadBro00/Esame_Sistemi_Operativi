#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// DICHIARAZIONE COSTANTI
#define k 2
#define p 3

// STRUTTURA CONTENENTE DATI CONDIVISI
struct shared {
    int m;
    int **mat1, **mat2;
    int **matProd;
    int count; // Numero di elementi della matrice prodotto completati
    pthread_cond_t condvar;
    pthread_mutex_t mutex;
} shared;

// STRUTTURA PER GLI ARGOMENTI PASSATI AI THREAD
struct thread_args {
    int row;
    int col;
};

// ROUTINE DEI THREAD PER IL CALCOLO DEL PRODOTTO
void* routine(void* args) {
    struct thread_args* ta = (struct thread_args*)args;

    int row = ta->row;
    int col = ta->col;

    free(ta); // Liberiamo la memoria allocata per gli argomenti

    // Calcola il prodotto per l'elemento specifico
    for (int i = 0; i < shared.m; i++) {
        shared.matProd[row][col] += shared.mat1[row][i] * shared.mat2[i][col];
    }

    // Aggiorna il contatore e segnala l'ultimo thread quando tutti i calcoli sono completi
    pthread_mutex_lock(&shared.mutex);
    shared.count++;
    if (shared.count == k * p) {
        pthread_cond_signal(&shared.condvar); // Segnala che tutti i calcoli sono stati completati
    }
    pthread_mutex_unlock(&shared.mutex);

    pthread_exit(NULL);
}

// ROUTINE DEL THREAD CHE STAMPA IL RISULTATO
void* lastOp(void* args) {
    pthread_mutex_lock(&shared.mutex);

    // Aspetta che tutti i thread abbiano completato i calcoli
    while (shared.count < k * p) {
        pthread_cond_wait(&shared.condvar, &shared.mutex);
    }

    // Stampa la matrice prodotto
    printf("-----------MATRICE PRODOTTO------------\n");
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < p; j++) {
            printf(" %d ", shared.matProd[i][j]);
        }
        printf("\n");
    }

    pthread_mutex_unlock(&shared.mutex);
    pthread_exit(NULL);
}

// INIZIALIZZAZIONE DELLE MATRICI
void mat_init() {
    // Allocazione dinamica delle matrici
    shared.mat1 = malloc(k * sizeof(int*));
    for (int i = 0; i < k; i++) {
        shared.mat1[i] = malloc(shared.m * sizeof(int));
    }

    shared.mat2 = malloc(shared.m * sizeof(int*));
    for (int i = 0; i < shared.m; i++) {
        shared.mat2[i] = malloc(p * sizeof(int));
    }

    // Inizializzazione delle matrici con valori casuali
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < shared.m; j++) {
            shared.mat1[i][j] = rand() % 256;
        }
    }

    for (int i = 0; i < shared.m; i++) {
        for (int j = 0; j < p; j++) {
            shared.mat2[i][j] = rand() % 256;
        }
    }

    // Allocazione e inizializzazione della matrice prodotto
    shared.matProd = malloc(k * sizeof(int*));
    for (int i = 0; i < k; i++) {
        shared.matProd[i] = malloc(p * sizeof(int));
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < p; j++) {
            shared.matProd[i][j] = 0;
        }
    }
}

// STAMPA DELLE MATRICI INIZIALI
void prt_mats() {
    printf("-----------MAT 1------------\n");
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < shared.m; j++) {
            printf(" %d ", shared.mat1[i][j]);
        }
        printf("\n");
    }
    
    printf("-----------MAT 2------------\n");
    for (int i = 0; i < shared.m; i++) {
        for (int j = 0; j < p; j++) {
            printf(" %d ", shared.mat2[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    pthread_cond_init(&shared.condvar, NULL);
    pthread_mutex_init(&shared.mutex, NULL);
    srand(time(NULL));

    if (argc != 2) {
        fprintf(stderr, "Uso: ./a.out <int>\n");
        exit(-1);
    }

    shared.m = atoi(argv[1]);
    if (shared.m < 2) {
        fprintf(stderr, "Uso int >= 2\n");
        exit(-2);
    }

    mat_init();
    prt_mats();

    pthread_t tids[k * p];
    pthread_t last;

    int t = 0;
    // Crea i thread per il calcolo del prodotto (uno per ogni elemento della matrice prodotto)
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < p; j++) {
            struct thread_args* args = malloc(sizeof(struct thread_args));
            args->row = i;
            args->col = j;
            pthread_create(&tids[t], NULL, routine, (void*)args);
            t++;
        }
    }

    // Crea il thread aggiuntivo per la stampa della matrice risultato
    pthread_create(&last, NULL, lastOp, NULL);

    // Aspetta che tutti i thread del calcolo finiscano
    for (int i = 0; i < k * p; i++) {
        pthread_join(tids[i], NULL);
    }

    // Aspetta che il thread di stampa finisca
    pthread_join(last, NULL);

    return 0;
}
