/*
 * ****************************************************************************
 * shm_mng.h
 *
 * Libreria para controlar la memoria compartida y su estructura.
 * ****************************************************************************
 */

#ifndef SERVER_SHM_MNG_H
#define SERVER_SHM_MNG_H

// INCLUDES
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

// PROTOTYPES

/**
 * Crea un segmento de memoria compartida.
 * @param shm_size tamaño del segmento de memoria compartida.
 * @return identificador IPC del segmento de memoria compartida.
 */
int create_shm(size_t shm_size);

/**
 * Mapeaa el segmento de memoria compartida al segmento de datos del proceso que llama a la función.
 * @param shm_id identificador IPC del segmento de memoria compartida.
 * @return dirección virtual del segmento de memoria compartida.
 */
char *attach_shm(int shm_id);

/**
 * Separa el segmento de memoria compartida del segmento de datos del proceso.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int detach_shm(char *shm_address);

/**
 * QLiberar el espacio utilizado por el segmento de memoria compartida.
 * @param shm_id identificador IPC del segmento de memoria compartida.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int free_shm(int shm_id);

#endif