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

/**
 * Lógica del proceso listener.
 * Encargado recibir peticiones de conexión, desconexión y los datos de los clientes.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int listener_process() {
    //set de señales que bloquear o desbloquear
    sigset_t* sigset;
    //llenamos el set de bloqueos
    sigfillset(sigset);
    while(1){
        if (bloq_signals(sigset)){
            perror("LIST: bloq_signals error\n");
            exit(EXIT_FAILURE);
        }
        // TODO fill part of the shm
        if (unbloq_signals(sigset)){
            perror("LIST: unbloq_signals error\n");
            exit(EXIT_FAILURE);
        }
        //comprobamos que no nos llegue la señal de salida
        if(received_end()){
            break;
        }
        sleep(20);
    }
    return EXIT_SUCCESS;
}



