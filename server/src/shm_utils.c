/*
 * ****************************************************************************
 * shm_utils.c
 *
 * Funciones para el manejo de la memoria compartida específicas a nuestro
 * problema.
 * ****************************************************************************
 */

#include "shm_utils.h"

// TODO utilizar el semáforo cada vez que se acceda o modifique la shm

/**
 * Devuelve el número de clientes conectados.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @return número de clientes conectados.
 */
int get_num_clients(char *shm_address) {
    return (int) *shm_address;
}

/**
 * Incrementa una unidad el número de clientes conectados.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @return número de clientes conectados.
 */
int incr_num_clients(char *shm_address) {
    return ++(*shm_address);
}

/**
 * Decrementa una unidad el número de clientes conectados.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @return número de clientes conectados.
 */
int decr_num_clients(char *shm_address) {
    return --(*shm_address);
}

/**
 * Devuelve la información del cliente almacenado en la posicón pasada.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param n índice del cliente.
 * @return información del cliente.
 */
client_info get_client_info(char *shm_address, int n) {
    struct client_info *client_info = (struct client_info *) ((void *) shm_address + sizeof(int));
    return client_info[n];
}


// TODO add_client_info: busca posición libre y añade la información del nuevota cliente
// TODO delete_cliente_info: marca una posición como libre.

/**
 * Devuelve el tamaño que tiene que tener el segmento de memoria compartida para almacenar información el número
 * de clientes pasado.
 * @param num_clients número de clientes a almacenar información.
 * @return tamaño del segmento de memoria.
 */
size_t get_shm_size(int num_clients) {
    // numClientesConectados + clienteInfo * numClientes
    return sizeof(int) + sizeof(client_info) * num_clients;
}
