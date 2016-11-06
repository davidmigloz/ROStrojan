/*
 * ****************************************************************************
 * main_process.h
 *
 * Logíca del proceso principal.
 * Encargado de la inicialización los recursos necesarios (procesos,
 * estructuras...), del menejo del menú y del cierre ordenado de los procesos.
 * ****************************************************************************
 */

#ifndef SERVER_MAIN_PROCESS_H
#define SERVER_MAIN_PROCESS_H

// INCLUDES
#include <unistd.h>
#include <stdbool.h>
#include "shm_utils.h"
#include "sem_mng.h"
#include "listener_process.h"
#include "../../lib/env_mng.h"

// DEFINES
#define CONECTIONS_SECTION "CONECTIONS"
#define MAX_NUM_CLIENTS_VAR "max_num_clients"
#define MAX_NUM_CLIENTS 25

// PROTOTYPES

/**
 * Lógica del proceso principal.
 * Inicializa el segmento de memoria compartida y crea los procesos hijo.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int main_process(int argc, char **argv);

#endif