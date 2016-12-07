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
#include "../../lib/sem_mng.h"
#include "../../lib/shm_mng.h"
#include <time.h>
#include <string.h>

// DEFINES
#define NAMES_MAXLENGHT 100

// STRUCTS
typedef struct client_info client_info;
struct client_info {
    _Bool used;
    int id;
    time_t last_conn;
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
int get_num_clients(char *shm_address, int sem_id);

/**
 * Devuelve la información del cliente almacenado en la posicón pasada.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param n índice del cliente.
 * @return información del cliente.
 */
client_info get_client_info(char *shm_address, int n, int sem_id);

/**
 * Añade la informacion de cliente a una posicion libre.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param client_inf información del cliente.
 * @param max_num_clients número máximo de clientes.
 * @param sem_id semaforo para la memoria compartida.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int add_client_info(char *shm_address, client_info *client_inf, int max_num_clients, int sem_id);

/**
 * Marca una posicion de la memoria como libre.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param n índice del cliente.
 * @param sem_id semaforo para la memoria compartida.
 * @return EXIT_SUCCESS.
 */
int delete_client_info(char *shm_address, int n, int sem_id);

/**
 * Recorre los registros almacenados liberando aquellos con una antiguedad mayor que
 * la indicadaa.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param max_timestamp máxima antiguedad.
 * @param max_num_clients número máximo de clientes.
 * @param sem_id semaforo para la memoria compartida.
 * @return
 */
int clean_old_records(char *shm_address, long max_timestamp, int max_num_clients, int sem_id);

/**
 * Devuelve el tamaño que tiene que tener el segmento de memoria compartida para almacenar información el número
 * de clientes pasado.
 * @param num_clients número de clientes a almacenar información.
 * @return tamaño del segmento de memoria.
 */
size_t get_shm_size(int num_clients);

#endif
