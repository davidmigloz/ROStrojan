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
#include "shm_utils.h"
#include "listener_process.h"
#include <unistd.h>

// PROTOTYPES

/**
 * Lógica del proceso principal.
 * Inicializa el segmento de memoria compartida y crea los procesos hijo.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int main_process();

#endif