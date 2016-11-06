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
int listener_process(int sem_id) {
    int end;
    if (bloq_signals()){
        perror("LIST: bloq_signals error\n");
        exit(EXIT_FAILURE);
    }
    while(1){
        // TODO fill part of the shm
        //comprobamos que no nos llegue la señal de salida
        end = received_end();
        if(end==-1){
            perror("LIST: received_end error\n");
            exit(EXIT_FAILURE);
        }
        if(end==SIGNAL_RECEIVED){
            break;
        }
        sleep(3);
    }
    return EXIT_SUCCESS;
}


