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
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// PROTOTYPES

/**
 * Lógica del proceso listener.
 * Encargado recibir peticiones de conexión, desconexión y los datos de los clientes.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int listener_process();

#endif
