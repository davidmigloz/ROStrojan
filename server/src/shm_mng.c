/*
 * ****************************************************************************
 * shm_mng.h
 *
 * Libreria para controlar la memoria compartida y su estructura.
 * ****************************************************************************
 */
#include "shm_mng.h"

/**
 * Crea un segmento de memoria compartida y lo mapea al segmento de datos del proceso que llama a la función.
 * @param shm_size tamaño del segmento de memoria compartida.
 * @return dirección virtual del segmento de memoria compartida.
 */
char *create_shm(size_t shm_size) {
    key_t mem_key;
    int shm_id;
    char *shm_address;

    // Conseguimos una estructura IPC quasi unica con ftok
    if ((mem_key = ftok("/tmp/rostrojan/server/shm", 'm')) == -1) {
        perror("SHM: ftok error\n");
        exit(EXIT_FAILURE);
    }

    // Creamos la memoria compartida en esa estructura IPC con permisos de lectura escritura para el usuario unicamente
    if ((shm_id = shmget(mem_key, shm_size, IPC_CREAT | IPC_EXCL | 0600)) < 0) {
        perror("SHM: shmget error\n");
        exit(EXIT_FAILURE);
    }

    // Mapear el segmento de memoria compartida
    shm_address = shmat(shm_id, 0, 0);
    if (shm_address == (void *) -1) {
        perror("SHM: shmat error\n");
        exit(EXIT_FAILURE);
    }

    // Marcar el segmento para que se libere cuando no haya ningún proceso asociado
    struct shmid_ds shm_desc;
    if (shmctl(shm_id, IPC_RMID, &shm_desc) == -1) {
        perror("SHM: shmctl error\n");
        exit(EXIT_FAILURE);
    }

    return shm_address;
}

/**
 * Desasocia el segmento de memoria compartida del segmento de datos del proceso.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int detach_shm(char *shm_address) {
    return -shmdt(shm_address);
}