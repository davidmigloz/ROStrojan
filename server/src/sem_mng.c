/*
 * ****************************************************************************
 * sem_mng.h
 *
 * Libreria para controlar el semaforo.
 * ****************************************************************************
 */

#include "sem_mng.h"

/**
 * Inicializa el semaforo
 * @return id de semaforo
 */
int init_sem() {
    key_t sem_key;
    int sem_id;
    struct sembuf sem;

    // Pido key de estructura IPC a ftok
    if ((sem_key = ftok( "/tmp", 's'))==(key_t)-1){
        perror("SEM: ftok error\n");
        exit(EXIT_FAILURE);
    }

    // Pido un conjunto de semaforos nuevo con un semaforo
    if ((sem_id = semget(sem_key, 1,IPC_CREAT | IPC_EXCL | 0600))==-1){
        perror("SEM: semget error\n");
        exit(EXIT_FAILURE);
    }else{
        // Inicializo el semaforo a ser el 0 del array con 1 recurso sin NOWAIT para que tengan que esperar
        sem.sem_num = 0;
        sem.sem_op = 1;
        sem.sem_flg = 0;
        if (semop(sem_id, &sem, 1) == -1) {
            perror("SEM: semop error\n");
            exit(EXIT_FAILURE);
        }
    }

    return sem_id;
}

/**
 * Elimina el semaforo
 * @param sem_id id del semaforo
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int tear_sem(int sem_id){
    // Elimino el semaforo
    if (semctl(sem_id, IPC_RMID, NULL) == -1) {
        perror("SEM: semctl error\n");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

/**
 * Signal o V al semaforo
 * @param sem_id id del semaforo
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int signal_sem(int sem_id){
    // Incremento el semaforo en uno
    struct sembuf sem_op = { 0, 1, NULL };
    if((semop(sem_id, &sem_op, 1) == -1){
        perror("SEM: semop signal error\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * Wait o P al semaforo
 * @param sem_id id del semaforo
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int wait_sem(int sem_id){
    // Decremento el semaforo en uno
    struct sembuf sem_op = { 0, -1, NULL };
    if((semop(sem_id, &sem_op, 1) == -1){
        perror("SEM: semop wait error\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
