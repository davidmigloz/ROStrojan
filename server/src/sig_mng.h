/*
 * ****************************************************************************
 * sig_mng.h
 *
 * Libreria para controlar señales.
 * ****************************************************************************
 */

#ifndef SERVER_SIG_MNG_H
#define SERVER_SIG_MNG_H

//INCLUDES
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

//DEFINES
#define SIGNAL_RECEIVED 1
#define NO_SIGNAL 0

//PROTOTYPES

/**
 * Comprueba si la señal SIGUSR1 esta siendo bloqueada.
 * @return EXIT_FAILURE o 0 (Ejecucion correcta, no esta siendo bloqueada)
 * o 1 (Ejecucion correcta esta siendo bloqueada).
 */
int received_end();

/**
 * Bloqueamos todas las señales posibles.
 * @return EXIT_FAILURE o EXIT_SUCCESS.
 */
int bloq_signals();

/**
 * Manda la señal SIGUSR1 a el proceso del pid.
 * @param pid pid del proceso.
 * @return EXIT_FAILURE o EXIT_SUCCESS.
 */
int kill_pid(int pid);

#endif
