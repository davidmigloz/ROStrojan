/*
 * ****************************************************************************
 * listener_process.h
 *
 * Lógica del proceso listener.
 * Encargado de recibir peticiones de conexión, desconexión y los datos de los
 * clientes.
 * ****************************************************************************
 */

#ifndef SERVER_LISTENER_PROCESS_H
#define SERVER_LISTENER_PROCESS_H

// INCLUDES
#include <signal.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <netinet/in.h>
#include "../../lib/sig_mng.h"
#include "shm_utils.h"

// DEFINES
#define DELAY       5
#define PORT        7654
#define BUFFER_SIZE 1024

// PROTOTYPES

/**
 * Lógica del proceso listener.
 * Encargado recibir peticiones de conexión, desconexión y los datos de los clientes.
 * @param sem_id semaforo para la memoria compartida.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param max_num_clients número máximo de clientes.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int listener_process(int sem_id, char *shm_address, int max_num_clients);

#endif
