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
#include "sig_mng.h"

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
