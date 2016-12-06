/*
 * ****************************************************************************
 * cleaning_process.h
 *
 * Lógica del proceso cleaner.
 * Encargado de realizar tareas de limpieza.
 * ****************************************************************************
 */

#ifndef SERVER_CLEANING_PROCESS_H
#define SERVER_CLEANING_PROCESS_H

// INCLUDES
#include <stdlib.h>
#include <time.h>
#include "shm_utils.h"
#include "sem_mng.h"
#include "sig_mng.h"
#include "../../lib/env_mng.h"

// DEFINES
#define CLEANING_SECTION "CLEANING"
#define MAX_TIME_VAR "max_time"
#define MAX_TIME_DEFAULT 10
#define DELAY 5

// PROTOTYPES

/**
 * Lógica del proceso cleaner.
 * @param sem_id semaforo para la memoria compartida.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param max_num_clients número máximo de clientes.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int cleaner_process(int pipe_fd[2], int sem_id, char *shm_address, int max_num_clients);

#endif
