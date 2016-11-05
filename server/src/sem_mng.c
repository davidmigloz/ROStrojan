/*
 * ****************************************************************************
 * sem_mng.h
 *
 * Libreria para controlar el semáforo.
 * ****************************************************************************
 */

#include "sem_mng.h"

/**
 * Crea un conjunto de semáforos con un semáforo inicializado a 1.
 * @return identificador IPC del conjunto de semáforos.
 */
int create_sem() {
    key_t sem_key;
    int sem_id;

    // Pido key de estructura IPC a ftok
    if ((sem_key = ftok("/tmp/rostrojan/server/sem", 's')) == -1) {
        perror("SEM: ftok error\n");
        exit(EXIT_FAILURE);
    }

    // Pido un conjunto de semáforos nuevo con un semáforo
    if ((sem_id = semget(sem_key, 1, IPC_CREAT | IPC_EXCL | 0600)) == -1) {
        perror("SEM: semget error\n");
        exit(EXIT_FAILURE);
    }

    // Inicializo el semáforo a 1
    semctl(sem_id, SEM_INDEX, SETVAL, 1);
    return sem_id;
}

/**
 * Elimina el conjunto de semáforos que contiene al semáforo.
 * @param sem_id identificador IPC del conjunto de semáforos.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int delete_sem(int sem_id) {
    // Elimino el semáforo
    return semctl(sem_id, IPC_RMID, 0);
}

/**
 * Wait o P al semáforo.
 * Decrementa el valor del semáforo, y se utiliza para adquirirlo o bloquearlo.
 * Si el semáforo está bloqueado se bloquea el proceso hasta que el semáforo liberado.
 * @param sem_id identificador IPC del conjunto de semáforos.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int wait_sem(int sem_id) {
    // Decremento el semáforo en uno
    struct sembuf sem_op = {SEM_INDEX, -1, 0};
    return semop(sem_id, &sem_op, 1);
}

/**
 * Signal o V al semáforo.
 * Incrementa el valor del semáforo, y se utiliza para liberarlo o inicializarlo.
 * @param sem_id identificador IPC del conjunto de semáforos.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int signal_sem(int sem_id) {
    // Incremento el semáforo en uno
    struct sembuf sem_op = {SEM_INDEX, 1, 0};
    return semop(sem_id, &sem_op, 1);
}