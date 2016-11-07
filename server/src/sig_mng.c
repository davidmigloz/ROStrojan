/*
 * ****************************************************************************
 * shm_mng.h
 *
 * Libreria para controlar señales.
 * ****************************************************************************
 */

#include "sig_mng.h"

/**
 * Comprueba si la señal SIGUSR1 esta siendo bloqueada.
 * @return EXIT_FAILURE o 0 (Ejecucion correcta, no esta siendo bloqueada)
 * o 1 (Ejecucion correcta esta siendo bloqueada).
 */
int received_end() {
    // Set de señales que recibimos
    sigset_t received_signals;
    if (sigpending(&received_signals) == -1) {
        perror("sigpending error\n");
        exit(EXIT_FAILURE);
    }
    return sigismember(&received_signals, SIGUSR1);
}

/**
 * Bloqueamos todas las señales posibles.
 * @return EXIT_FAILURE o EXIT_SUCCESS.
 */
int bloq_signals() {
    // Set de señales que bloquear o desbloquear
    sigset_t sigset;
    // Llenamos el set de bloqueos
    sigfillset(&sigset);
    // Bloqueamos todas las señales de sigset
    if ((sigprocmask(SIG_BLOCK, &sigset, NULL) == -1)) {
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

/**
 * Manda la señal SIGUSR1 a el proceso del pid.
 * @param pid pid del proceso.
 * @return EXIT_FAILURE o EXIT_SUCCESS.
 */
int kill_pid(pid_t pid) {
    if ((kill(pid, SIGUSR1)) == -1) {
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
