/*
 * ****************************************************************************
 * shm_utils.c
 *
 * Funciones para el manejo de la memoria compartida específicas a nuestro
 * problema.
 * ****************************************************************************
 */

#include "shm_utils.h"

// PRIVATE HEADERS

int _search_empty_pos(char *shm_address, int max_num_clients);

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
 * Devuelve la información del cliente almacenado en la posicón pasada.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param n índice del cliente.
 * @param sem_id semaforo para la memoria compartida
 * @return información del cliente.
 */
client_info get_client_info(char *shm_address, int n, int sem_id) {
    client_info *client_info;
    wait_sem(sem_id);
    client_info = (struct client_info *) ((void *) shm_address + sizeof(int));
    signal_sem(sem_id);
    return client_info[n];
}

/**
 * Añade la informacion de cliente a una posicion libre.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param client_inf información del cliente.
 * @param max_num_clients número máximo de clientes.
 * @param sem_id semaforo para la memoria compartida.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int add_client_info(char *shm_address, client_info *client_inf, int max_num_clients, int sem_id) {
    int pos;
    client_info *memory_client;
    wait_sem(sem_id);
    // Comprobar que hay posición libre
    if (max_num_clients - ((int) *shm_address) == 0) {
        signal_sem(sem_id);
        return EXIT_FAILURE;
    }
    // Buscar posición libre
    pos = _search_empty_pos(shm_address, max_num_clients);
    // Rellenar info
    memory_client = (struct client_info *) (shm_address + get_shm_size(pos));
    *memory_client = *client_inf;
    memory_client->used = 1;
    // Incrementar num clientes
    ++(*shm_address);
    signal_sem(sem_id);
    return EXIT_SUCCESS;
}

/**
 * Busca una posicion libre en el segmento de memoria compartida.
 * Si la encuentra devuelve su índice. Si no hay, devuelve -1.
 * El semaforo lo tiene que poseer el proceso que llame a la función.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param max_num_clients número máximo de clientes.
 * @return n posicion libre en memoria
 */
int _search_empty_pos(char *shm_address, int max_num_clients) {
    int i;
    struct client_info *client_info;
    // Buscar posición libre
    client_info = (struct client_info *) ((void *) shm_address + sizeof(int));
    for (i = 0; i < max_num_clients; ++i) {
        if (client_info[i].used == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Marca una posicion de la memoria como libre.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param n índice del cliente.
 * @param sem_id semaforo para la memoria compartida.
 * @return EXIT_SUCCESS.
 */
int delete_client_info(char *shm_address, int n, int sem_id) {
    struct client_info *client_info;
    wait_sem(sem_id);
    client_info = (struct client_info *) (shm_address + get_shm_size(n));
    if ((*client_info).used == 1) {
        // Marcar como libre
        (*client_info).used = 0;
        // Decrementar num clientes
        --(*shm_address);
    }
    signal_sem(sem_id);
    return EXIT_SUCCESS;
}

/**
 * Recorre los registros almacenados liberando aquellos con una antiguedad mayor que
 * la indicadaa.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param max_timestamp máxima antiguedad.
 * @param max_num_clients número máximo de clientes.
 * @param sem_id semaforo para la memoria compartida.
 * @return
 */
int clean_old_records(char *shm_address, long max_timestamp, int max_num_clients, int sem_id) {
    wait_sem(sem_id);
    client_info *client_info;
    // Buscar registros antiguos
    client_info = (struct client_info *) ((void *) shm_address + sizeof(int));
    for (int i = 0; i < max_num_clients; ++i) {
        if (client_info[i].used == 1 && client_info[i].last_conn < max_timestamp) {
            // Marcar como libre
            (*client_info).used = 0;
            // Decrementar num clientes
            --(*shm_address);
        }
    }
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
