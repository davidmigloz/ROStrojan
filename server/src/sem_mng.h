/*
 * ****************************************************************************
 * sem_mng.h
 *
 * Libreria para controlar el semaforo.
 * ****************************************************************************
 */
#ifndef SERVER_SEM_MNG_H
#define SERVER_SEM_MNG_H
//INCLUDES
#include <sys/sem.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>

//PROTOTYPES
/**
 * Inicializa el semaforo
 * @return id de semaforo
 */
int init_sem();
/**
 * Elimina el semaforo
 * @param sem_id id del semaforo
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int tear_sem(int sem_id);
/**
 * Signal o V al semaforo
 * @param sem_id id del semaforo
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int signal_sem(int sem_id);
/**
 * Wait o P al semaforo
 * @param sem_id id del semaforo
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int wait_sem(int sem_id);

#endif //SERVER_SEM_MNG_H
