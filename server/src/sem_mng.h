/*
 * ****************************************************************************
 * sem_mng.h
 *
 * Libreria para controlar el semáforo.
 * ****************************************************************************
 */
#ifndef SERVER_SEM_MNG_H
#define SERVER_SEM_MNG_H

// INCLUDES
#include <sys/sem.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>

// DEFINES
#define SEM_INDEX 0

// PROTOTYPES

/**
 * Crea un conjunto de semáforos con un semáforo inicializado a 1.
 * @return identificador IPC del conjunto de semáforos.
 */
int create_sem();

/**
 * Elimina el conjunto de semáforos que contiene al semáforo.
 * @param sem_id identificador IPC del conjunto de semáforos.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int delete_sem(int sem_id);

/**
 * Wait o P al semáforo.
 * Decrementa el valor del semáforo, y se utiliza para adquirirlo o bloquearlo.
 * Si el semáforo está bloqueado se bloquea el proceso hasta que el semáforo liberado.
 * @param sem_id identificador IPC del conjunto de semáforos.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int wait_sem(int sem_id);

/**
 * Signal o V al semáforo.
 * Incrementa el valor del semáforo, y se utiliza para liberarlo o inicializarlo.
 * @param sem_id identificador IPC del conjunto de semáforos.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int signal_sem(int sem_id);

#endif