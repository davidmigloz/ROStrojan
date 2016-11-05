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
    char *shm_address;

    // Crear segmento de memoria compartida y mapearlo al segmento de memoria la proceso
    shm_address = create_shm(get_shm_size(get_max_num_clients()));

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

/**
 * Obtiene el número máximo de clientes del archivo de entorno.
 * Si el valor leído es mayor que MAX_NUM_CLIENTS, el val
 * @return
 */
int get_max_num_clients() {
    int max_num_clients;

    // Leer archivo de entorno
    char *val = get_var_value(CONECTIONS_SECTION, MAX_NUM_CLIENTS_VAR);

    if (strlen(val) == 0) {
        // No existe variable -> crearla (por defecto MAX_NUM_CLIENTS)
        char max_num[3];
        sprintf(max_num, "%d", MAX_NUM_CLIENTS);                             // To convert int to string
        ver_entorno(CONECTIONS_SECTION, NULL);                               // Create section
        modificar_entorno(CONECTIONS_SECTION, MAX_NUM_CLIENTS_VAR, max_num); // Add var
        max_num_clients = MAX_NUM_CLIENTS;
    } else {
        // Si existe, obtener valor
        max_num_clients = atoi(val);
        if (max_num_clients > MAX_NUM_CLIENTS) {
            // Si es > que MAX_NUM_CLIENTS, establecerlo a MAX_NUM_CLIENTS
            char max_num[3];
            sprintf(max_num, "%d", MAX_NUM_CLIENTS);                             // To convert int to string
            modificar_entorno(CONECTIONS_SECTION, MAX_NUM_CLIENTS_VAR, max_num); // Modify var
            max_num_clients = MAX_NUM_CLIENTS;
        }
    }
    return max_num_clients;
}