/*
 * ****************************************************************************
 * shm_utils.c
 *
 * Funciones para el manejo de la memoria compartida específicas a nuestro
 * problema.
 * ****************************************************************************
 */

#include "shm_utils.h"


int _search_empty_pos(char *shm_address);

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



/**
 * Añade la informacion de cliente a una posicion libre.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param client_inf
 * @param sem_id semaforo para la memoria compartida.
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int add_client_info(char *shm_address, client_info *client_inf, int sem_id){
    int pos;
    struct client_info memory_client;
    // TODO: si no quedan huecos libres falla
    wait_sem(sem_id);
    // Search empty pos
    pos = _search_empty_pos(shm_address);
    // Fill pos
    memory_client = *(client_info*)(shm_address + get_shm_size(pos));
    memory_client = *client_inf;
    signal_sem(sem_id);
    return EXIT_SUCCESS;
}

/**
 * Busca una posicion libre en memoria, no para hasta encontrar posicion libre asi que hay que asegurarse de que hay una
 * antes de llamar, tampoco pide el semaforo asi que lo deberia tener el proceso que lo llame.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @return n posicion libre en memoria
 */
int _search_empty_pos(char *shm_address){
    int i = 0;
    while(*(_Bool*)(shm_address + get_shm_size(i))){
        i++;
    }
    return i;
}

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
