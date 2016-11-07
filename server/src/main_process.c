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

void _menu_loop(int sem_id);

void _print_menu();

void _show_num_clients(int sem_id);

void _show_num_free_slots(int sem_id);

void _show_connected_clients(int sem_id);

void _show_info_client(int sem_id);

// GLOBAL VARS
char *shm_address;

/**
 * Lógica del proceso principal.
 * Inicializa el segmento de memoria compartida y crea los procesos hijo.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int main_process() {
    // Leer número máximo de clientes
    int max_num_clients = _get_max_num_clients();

    // Crear archivos temporales
    if (_create_tmp_dirs() == -1) {
        perror("create tmp dirs error\n");
        exit(EXIT_FAILURE);
    }

    // Crear semáforo
    int sem_id = create_sem();

    // Crear segmento de memoria compartida y mapearlo al segmento de memoria la proceso
    size_t shm_size = get_shm_size(max_num_clients);
    shm_address = create_shm(shm_size);

    // Inicializar procesos hijo
    pid_t child_pid;
    int listener_process_exit;
    switch (child_pid = fork()) {
        case -1: // Error
            perror("fork error\n");
            exit(EXIT_FAILURE);
        case 0: // Child 1: listener process
            listener_process_exit = listener_process(sem_id, shm_address, max_num_clients);
            exit(listener_process_exit);
        default: // Parent
            break;
    }

    // Escuchar órdenes de usuario
    _menu_loop(sem_id);

    // Cierre ordenado
    puts("Terminando ordenadamente...");
    kill_pid(child_pid);
    detach_shm(shm_address);
    delete_sem(sem_id);
    _delete_tmp_dirs();
    return EXIT_SUCCESS;
}

/**
 * Bucle del menú de usuario.
 * El bucle termina cuando se selecciona la opción de cerrar.
 */
void _menu_loop(int sem_id) {
    _Bool running = true;
    int sel;
    int c;
    _print_menu();

    while (running) {
        printf("_____________________________________________\n");
        printf("Seleccione una opción [1-5]: ");

        // Leer opción introducida
        sel = -1;
        scanf("%d", &sel);
        switch (sel) {
            case 1:
                // Número de equipos conectados
                _show_num_clients(sem_id);
                break;
            case 2:
                // Número de espacios disponibles
                _show_num_free_slots(sem_id);
                break;
            case 3:
                // Mostrar todos los clientes conectados
                _show_connected_clients(sem_id);
                break;
            case 4:
                // Mostrar la información de un cliente
                _show_info_client(sem_id);
                break;
            case 5:
                // Cerrar
                running = false;
                break;
            default:
                while ((c = getchar()) != '\n' && c != EOF) {} // Vaciar buffer
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
    printf("=============================================\n");
    printf("                   M E N Ú                   \n");
    printf("=============================================\n");
    printf("> 1: Número de equipos conectados            \n");
    printf("> 2: Número de espacios disponibles          \n");
    printf("> 3: Mostrar todos los clientes conectados   \n");
    printf("> 4: Mostrar la información de un cliente    \n");
    printf("> 5: Cerrar                                  \n");
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
    char mkdirs[2048];
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

/**
 * Muestra el múmero de equipos conectados.
 */
void _show_num_clients(int sem_id) {
    printf("> Número de equipos conectados: %d\n\n", get_num_clients(shm_address, sem_id));
}

/**
 * Muestra el número de espacios disponibles.
 */
void _show_num_free_slots(int sem_id) {
    int free_slots = _get_max_num_clients() - get_num_clients(shm_address, sem_id);
    printf("> Número de espacios disponibles: %d\n\n", free_slots);
}

/**
 * Muestra todos los clientes conectados.
 */
void _show_connected_clients(int sem_id) {
    printf("> Clientes conectados:\n");
    for (int i = 0; i < _get_max_num_clients(); i++) {
        client_info info = get_client_info(shm_address, i, sem_id);
        if (info.used) {
            printf("  %d. %s\n", i, info.name);
        }
    }
    printf("\n");
}

/**
 * Muestra la información de un cliente.
 */
void _show_info_client(int sem_id) {
    printf("> Introduzca el índice del cliente: ");
    // Leer índice
    int sel = -1;
    scanf("%d", &sel);
    // Validar índice
    if (sel < 0 || sel >= _get_max_num_clients()) {
        printf("Índice inválido!!!\n\n");
        return;
    }
    client_info info = get_client_info(shm_address, sel, sem_id);
    if (!info.used) {
        printf("El índice no se encuentra en uso.\n\n");
        return;
    }
    // Mostrar info
    printf("> Información del cliente:\n");
    printf("  -ID:\t\t\t%d\n", info.id);
    printf("  -NAME:\t\t%s\n", info.name);
    printf("  -USER:\t\t%s\n", info.user);
    printf("  -IP:\t\t\t%s\n", info.ip);
    printf("  -KERNEL:\t\t%s\n", info.kernel);
    printf("  -LAST CONN:\t%i\n\n", info.last_conn);
}
