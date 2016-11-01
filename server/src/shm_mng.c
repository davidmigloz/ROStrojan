/*
 * ****************************************************************************
 * shm_mng.h
 *
 * Libreria para controlar la memoria compartida y su estructura.
 * ****************************************************************************
 */
#include "shm_mng.h"

// PRIVATE HEADERS


/**
 * Crea una estructura IPC y la añade a la memomria.
 * @return puntero a la memoria compartida.
 */
char *init_shm() {
    int shm_size = sizeof(device) * N_OF_DEVICES + sizeof(int);

    key_t mem_key;
    int shm_id;
    char *shm_address;
    /*
     * hay que crear el '/tmp/rostrojan' si queremos hacerlo sobre /tmp/rostrojan
     */
    // Conseguimos una estructura IPC quasi unica con ftok
    if ((mem_key = ftok("/tmp", 'm')) == (key_t) - 1) {
        perror("SHM: ftok error\n");
        exit(EXIT_FAILURE);
    }

    // Creamos la memoria compartida en esa estructura IPC con permisos de lectura escritura para el usuario unicamente
    if ((shm_id = shmget(mem_key, shm_size, IPC_CREAT | IPC_EXCL | 0600)) < 0) {
        perror("SHM: shmget error\n");
        exit(EXIT_FAILURE);
    }

    // Añadimos esa memoria compartida a nuestro proceso
    if ((shm_address = shmat(shm_id, NULL, 0)) == (char *) -1) {
        perror("SHM: shmat error\n");
        exit(EXIT_FAILURE);
    }

    // Nos aseguramos que el sistema sea capaz de limpiar esa estructura IPC cuando no haya procesos usandola
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("SHM: shmctl error\n");
        exit(EXIT_FAILURE);
    }
    return shm_address;
}

/**
 * Quitamos la memoria compartida de nuestra aplicación.
 * @param shm_pos puntero a la memoria compartida.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int tear_shm(char *shm_pos) {
    //Des-añadimos la memoria compartida de nuestro proceso
    if (shmdt(shm_pos) == -1) {
        perror("SHM: shmdt error\n");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

/**
 * Getter para el n_of_devices para que los usuarios de la biblioteca no tengan que conocer la implementacion.
 * @param shm_pos puntero a la memoria compartida.
 * @return número de dispositivos.
 */
int get_n_of_devices(char *shm_pos) {
    return (int) *shm_pos;
}

/**
 * Setter para el n_of_devices para que los usuarios de la biblioteca no tengan que conocer la implementacion.
 * @param shm_pos puntero a la memoria compartida.
 * @param n_of_devices numero de dispositivos.
 */
void set_n_of_devices(char *shm_pos, int n_of_devices) {
    (*(int *) (shm_pos)) = n_of_devices;
}

device get_n_device(char *shm_pos, int n) {
    return (device) *(device *) (shm_pos + sizeof(int) + sizeof(device) * n);
}

device *get_n_device_address(char *shm_pos, int n) {
    return (device *) (shm_pos + sizeof(int) + sizeof(device) * n);
}