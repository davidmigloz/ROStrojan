/*
 * ****************************************************************************
 * sem_mng.h
 *
 * Libreria para controlar el semaforo.
 * ****************************************************************************
 */

#include "sem_mng.h"

int init_sem() {
    key_t sem_key;
    int sem_id;
    struct sembuf sem;

    if ((sem_key = ftok( "/tmp", 's'))==(key_t)-1){
        perror("SEM: ftok error\n");
        exit(EXIT_FAILURE);
    }

    if ((sem_id = semget(sem_key, 1,IPC_CREAT | IPC_EXCL ))==-1){
        perror("SEM: semget error\n");
        exit(EXIT_FAILURE);
    }else{
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

int tear_sem(int sem_id){
    if (semctl(sem_id, IPC_RMID, NULL) == -1) {
        perror("SEM: semctl error\n");
        exit(EXIT_FAILURE);
    }
}

int signal_sem(int sem_id){
    struct sembuf sem_op = { 0, 1, NULL };
    if((semop(sem_id, &sem_op, 1) == -1){
        perror("SEM: semop signal error\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int wait_sem(int sem_id){
    struct sembuf sem_op = { 0, -1, NULL };
    if((semop(sem_id, &sem_op, 1) == -1){
        perror("SEM: semop wait error\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

