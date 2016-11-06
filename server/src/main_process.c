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

int _get_max_num_clients();

int _create_tmp_dirs();

int _delete_tmp_dirs();

void _menu_loop();

void _print_menu();

/**
 * Lógica del proceso principal.
 * Inicializa el segmento de memoria compartida y crea los procesos hijo.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int main_process(int argc, char **argv) {
    // Leer número máximo de clientes
    int max_num_clients = _get_max_num_clients();

    // Crear archivos temporales
    if (_create_tmp_dirs() == -1) {
        perror("create tmp dirs error\n");
        exit(EXIT_FAILURE);
    }

    // Crear segmento de memoria compartida y mapearlo al segmento de memoria la proceso
    size_t shm_size = get_shm_size(max_num_clients);
    char *shm_address = create_shm(shm_size);

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
    _menu_loop();

    // Cierre ordenado
    //TODO
    return EXIT_SUCCESS;
}

/**
 * Bucle del menú de usuario.
 * El bucle termina cuando se selecciona la opción de cerrar.
 */
void _menu_loop() {
    _Bool running = true;
    int sel;
    int c;
    _print_menu();

    while (running) {
        printf("_____________________________________________\n"
               "Seleccione una opción [1-5]...               \n");

        // Leer opción introducida
        sel = -1;
        scanf("%d", &sel);
        switch (sel) {
            case 1:
                // Número de equipos conectados
                puts("1");
                // TODO
                break;
            case 2:
                // Número de espacios disponibles
                puts("2");
                // TODO
                break;
            case 3:
                // Mostrar todos los clientes conectados
                puts("3");
                // TODO
                break;
            case 4:
                // Mostrar información de un cliente
                puts("4");
                // TODO
                break;
            case 5:
                // Cerrar
                running = false;
            default:
                while ((c = getchar()) != '\n' && c != EOF) { } // Vaciar buffer
                printf(" Selección inválida!!!\n");
                _print_menu();
                break;
        }
    }
}

/**
 * Imprime el meú.
 */
void _print_menu() {
    printf("=============================================\n"
           "                   M E N Ú                   \n"
           "=============================================\n"
           "> 1: Número de equipos conectados            \n"
           "> 2: Número de espacios disponibles          \n"
           "> 3: Mostrar todos los clientes conectados   \n"
           "> 4: Mostrar información de un cliente       \n"
           "> 5: Cerrar                                  \n");
}

/**
 * Obtiene el número máximo de clientes del archivo de entorno.
 * Si el valor leído es mayor que MAX_NUM_CLIENTS, el val
 * @return
 */
int _get_max_num_clients() {
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

/**
 * Crea los directorios temporales utilizados en la memoria compartida y el semáforo.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int _create_tmp_dirs() {
    // Crear directorios
    char mkdirs[PATH_MAX];
    sprintf(mkdirs, "mkdir -p %s %s", TMP_FILE_SHM, TMP_FILE_SEM);
    return system(mkdirs);
}

/**
 * Elimina los directorios temporales utilizados en la memoria compartida y el semáforo.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int _delete_tmp_dirs() {
    return system("rm -rf /tmp/rostrojan/");
}