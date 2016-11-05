/*
 * ****************************************************************************
 * main_process.c
 *
 * Logíca del proceso principal.
 * Encargado de la inicialización los recursos necesarios (procesos,
 * estructuras...), del menejo del menú y del cierre ordenado de los procesos.
 * ****************************************************************************
 */

#include "main_process.h"

// PRIVATE HEADERS

int get_max_num_clients();

/**
 * Lógica del proceso principal.
 * Inicializa el segmento de memoria compartida y crea los procesos hijo.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int main_process() {
    client_info devices[get_max_num_clients()];
    int shm_id;
    char *shm_address;

    // Crear segmento de memoria compartida
    shm_id = create_shm(get_shm_size(get_max_num_clients()));

    // Mapear segmento de memoria la proceso
    shm_address = attach_shm(shm_id);

    // Inicializar procesos hijo
    int listener_process_exit;
    switch (fork()) {
        case -1: // Error
            perror("fork error\n");
            exit(EXIT_FAILURE);
        case 0: // Child 1: listener process
            listener_process_exit = listener_process();
            exit(listener_process_exit);
        default: // Parent
            break;
    }

    // Escuchar órdenes de usuario
    while (1) {
        // TODO menú
    }
    return EXIT_SUCCESS;
}

int get_max_num_clients() {
    // TODO obtener este dato de entorno.dat. Si no existe inicializarlo a 25.
    return 25;
}