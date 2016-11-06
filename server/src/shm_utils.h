/*
 * ****************************************************************************
 * shm_utils.h
 *
 * Funciones para el manejo de la memoria compartida específicas a nuestro
 * problema.
 * ****************************************************************************
 */

#ifndef SERVER_SHM_UTILS_H
#define SERVER_SHM_UTILS_H

// INCLUDES
#include "shm_mng.h"

// DEFINES
#define NAMES_MAXLENGHT 100

// STRUCTS
typedef struct client_info client_info;
struct client_info {
    _Bool used;
    int last_conn;
    int id;
    char name[NAMES_MAXLENGHT + 1];
    char user[NAMES_MAXLENGHT + 1];
    char ip[NAMES_MAXLENGHT + 1];
    char kernel[NAMES_MAXLENGHT + 1];
};

// PROTOTYPES

/**
 * Devuelve el número de clientes conectados.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @return número de clientes conectados.
 */
int get_num_clients(char *shm_address);

/**
 * Incrementa una unidad el número de clientes conectados.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @return número de clientes conectados.
 */
int incr_num_clients(char *shm_address);

/**
 * Decrementa una unidad el número de clientes conectados.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @return número de clientes conectados.
 */
int decr_num_clients(char *shm_address);

/**
 * Devuelve la información del cliente almacenado en la posicón pasada.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param n índice del cliente.
 * @return información del cliente.
 */
client_info get_client_info(char *shm_address, int n);

/**
 * Devuelve el tamaño que tiene que tener el segmento de memoria compartida para almacenar información el número
 * de clientes pasado.
 * @param num_clients número de clientes a almacenar información.
 * @return tamaño del segmento de memoria.
 */
size_t get_shm_size(int num_clients);

#endif
