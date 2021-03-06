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
#include <stdbool.h>
#include "shm_utils.h"
#include "../../lib/sem_mng.h"
#include "../../lib/sig_mng.h"
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
 * @param read_pipe_fd descritor de letura de la tubería con el proceso padre.
 * @param max_num_clients número máximo de clientes.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int cleaner_process(int sem_id, char *shm_address, int read_pipe_fd, int max_num_clients);

#endif
