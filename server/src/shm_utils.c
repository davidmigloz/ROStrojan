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
 * @param sem_id semaforo para la memoria compartida
 * @return número de clientes conectados.
 */
int get_num_clients(char *shm_address, int sem_id) {
    int ret;
    wait_sem(sem_id);
    ret = (int) *shm_address;
    signal_sem(sem_id);
    return ret;
}

/**
 * Incrementa una unidad el número de clientes conectados.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param sem_id semaforo para la memoria compartida
 * @return número de clientes conectados.
 */
int incr_num_clients(char *shm_address, int sem_id) {
    int ret;
    wait_sem(sem_id);
    ret = ++(*shm_address);
    signal_sem(sem_id);
    return ret;
}

/**
 * Decrementa una unidad el número de clientes conectados.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param sem_id semaforo para la memoria compartida
 * @return número de clientes conectados.
 */
int decr_num_clients(char *shm_address, int sem_id) {
    int ret;
    wait_sem(sem_id);
    ret = --(*shm_address);
    signal_sem(sem_id);
    return ret;
}

/**
 * Devuelve la información del cliente almacenado en la posicón pasada.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param n índice del cliente.
 * @param sem_id semaforo para la memoria compartida
 * @return información del cliente.
 */
client_info get_client_info(char *shm_address, int n, int sem_id) {
    struct client_info *client_info;
    wait_sem(sem_id);
    client_info = (struct client_info *) ((void *) shm_address + sizeof(int));
    signal_sem(sem_id);
    return client_info[n];
}


// TODO add_client_info: busca posición libre y añade la información del nuevo cliente

int add_client_info(char *shm_address, client_info *client_info, int sem_id){
    wait_sem(sem_id);
    // Search empty pos

    // Fill pos
    return EXIT_SUCCESS;
}

int search_empty_pos(char *shm_address){

}

// TODO code review: delete_cliente_info: marca una posición como libre.
/**
 * Marca una posicion de la memoria como libre.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param n índice del cliente.
 * @param sem_id semaforo para la memoria compartida
 * @return EXIT_SUCCESS
 */
int delete_client_info(char *shm_address, int n, int sem_id){
    struct client_info *client_info;
    wait_sem(sem_id);
    client_info = (struct client_info *) ((void *) shm_address + sizeof(int));
    client_info->used = 0;
    signal_sem(sem_id);
    return EXIT_SUCCESS;
}


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
