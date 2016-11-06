/*
 * ****************************************************************************
 * listener_process.c
 *
 * Lógica del proceso listener.
 * Encargado recibir peticiones de conexión, desconexión y los datos de los
 * clientes.
 * *En esta entrega será simulado.
 * ****************************************************************************
 */

#include "listener_process.h"


void _handler(int signum);
int set_handler();


/* If this flag is nonzero, don't handle the signal right away. */
volatile sig_atomic_t signal_pending = 0;

/* This is nonzero if a signal arrived and was not handled. */
volatile sig_atomic_t ignore_signal = 0;

/**
 * Lógica del proceso listener.
 * Encargado recibir peticiones de conexión, desconexión y los datos de los clientes.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int listener_process() {
    if (set_handler()==-1){
        perror("LIST: set_handler error\n");
    }

    while(1) {
        ignore_signal++;
        // TODO fill part of the shm
        ignore_signal--;
        if (ignore_signal == 0 && signal_pending != 0){
            perror("YOU KILLED ME!");
            break;
        }
        sleep(20);
    }
    return EXIT_SUCCESS;
}

int set_handler() {
    struct sigaction action;
    action.sa_handler = _handler;
    sigfillset(&action.sa_mask);
    action.sa_flags = 0;
    if((sigaction(SIGUSR1, &action, NULL))==-1){
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

void _handler(int signum)
{
    if (ignore_signal){
        signal_pending = signum;
    }
    else
    {
        perror("YOU KILLED ME!");
        exit(EXIT_SUCCESS);
    }
}

