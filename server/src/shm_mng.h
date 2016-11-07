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

// DEFINES
#define TMP_FILE_SHM "/tmp/rostrojan/server/shm"

// PROTOTYPES

/**
 * Crea un segmento de memoria compartida y lo mapea al segmento de datos del proceso que llama a la función.
 * @param shm_size tamaño del segmento de memoria compartida.
 * @return dirección virtual del segmento de memoria compartida.
 */
char *create_shm(size_t shm_size);

/**
 * Desasocia el segmento de memoria compartida del segmento de datos del proceso.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int detach_shm(char *shm_address);

#endif
