/*
 * ****************************************************************************
 * listener_process.h
 *
 * Lógica del proceso listener.
 * Encargado recibir peticiones de conexión, desconexión y los datos de los
 * clientes.
 * *En esta entrega será simulado.
 * ****************************************************************************
 */

#ifndef SERVER_LISTENER_PROCESS_H
#define SERVER_LISTENER_PROCESS_H

// INCLUDES
#include <signal.h>
#include <limits.h>
#include <string.h>
#include "sig_mng.h"
#include "shm_utils.h"

// DEFINES
#define NUM_NAMES   20
#define NUM_IPS     20
#define NUM_KERNELS 20

// PROTOTYPES

/**
 * Lógica del proceso listener.
 * Encargado recibir peticiones de conexión, desconexión y los datos de los clientes.
 * @param sem_id semaforo para la memoria compartida.
 * @param max_num_clients número máximo de clientes.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int listener_process(int sem_id, int max_num_clients);

#endif
