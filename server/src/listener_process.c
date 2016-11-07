/*
 * ****************************************************************************
 * listener_process.c
 *
 * Lógica del proceso listener.
 * Encargado recibir peticiones de conexión, desconexión y los datos de los
 * clientes.
 * *En esta entrega será simulado.
 * ****************************************************************************
 */

#include "listener_process.h"

// PRIVATE HEADERS

client_info _random_client_info();

void _free_shm_space(char *shm_address, int sem_id, int max_num_clients);

long _random(long max);

// GLOBAL VARS
const char *NAMES[NUM_NAMES] = {"Aaron", "Audrey", "Warren", "Lisa", "Bradley", "Ruth", "Debra", "Alan", "Anna", "Joan",
                                "Danielle", "Frank ", "Tiffany", "Charles", "Clint", "Michael", "Eleanor", "Dwight",
                                "David", "Javier"};
const char *IPS[NUM_IPS] = {"253.103.164.194", "235.31.200.201", "35.107.142.29", "202.118.84.170", "227.173.176.51",
                            "121.7.141.193", "17.189.22.108", "206.118.152.63", "62.57.104.125", "59.89.115.133",
                            "34.66.73.158", "66.58.6.207 ", "136.42.33.74", "145.177.206.233", "151.46.224.80",
                            "60.127.218.88", "191.4.121.88", "241.249.69.75", "151.102.71.170", "113.252.115.50"};

const char *KERNELS[NUM_KERNELS] = {"Microsoft Windows v10.0", "Microsoft Windows v8.1", "Microsoft Windows v8.0",
                                    "Microsoft Windows v6.1", "Microsoft Windows v6.0", "Microsoft Windows v5.1",
                                    "Linux 3.19", "Linux 3.0", "Linux 2.6", "Linux 2.5", "Linux 2.4", "Linux 2.3",
                                    "Linux 2.0", "Linux 1.3", "Linux 1.0 ", "Darwin 16.1.0", "Darwin 16.0.0",
                                    "Darwin 15.6.0", "Darwin 14.0.0", "Darwin 13.4.0"};

/**
 * Lógica del proceso listener.
 * Encargado recibir peticiones de conexión, desconexión y los datos de los clientes.
 * @param sem_id semaforo para la memoria compartida.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param max_num_clients número máximo de clientes.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int listener_process(int sem_id, char *shm_address, int max_num_clients) {
    int end;
    // Bloquear señales
    if (bloq_signals()) {
        perror("LIST: bloq_signals error\n");
        exit(EXIT_FAILURE);
    }
    while (1) {
        // Generar datos aleatorios
        client_info client_info = _random_client_info();

        // Añadir info cliente
        int ok = add_client_info(shm_address, &client_info, max_num_clients, sem_id);
        if (ok == EXIT_FAILURE) {
            // Liberar espacio
            _free_shm_space(shm_address, sem_id, max_num_clients);
            // Añadir info cliente de nuevo
            add_client_info(shm_address, &client_info, max_num_clients, sem_id);
        }

        // Comprobamos si hay que terminar (si se ha recibido SIGUSR1)
        end = received_end();
        if (end == -1) {
            perror("LIST: received_end error\n");
            exit(EXIT_FAILURE);
        } else if (end == SIGNAL_RECEIVED) {
            break;
        }
        sleep(3);
    }
    return EXIT_SUCCESS;
}

/**
 * Generar información de un cliente aleatorio.
 * @return client_info·
 */
client_info _random_client_info() {
    client_info client_info;
    // Generar id
    client_info.id = (int) _random(1000);
    // Generar última conexión
    client_info.last_conn = (int) _random(INT_MAX);
    // Generar nombre de usuario
    char *username = malloc(255);
    strcpy(username, NAMES[_random(NUM_NAMES - 1)]);
    client_info.user = username;
    // Generar nombre del pc
    char *name = malloc(255);
    strcpy(name, username);
    strcat(name, "PC");
    client_info.name = name;
    // Generar IP
    char *ip = malloc(255);
    strcpy(ip, IPS[_random(NUM_IPS - 1)]);
    client_info.ip = ip;
    // Generar Kernel
    char *kernel = malloc(255);
    strcpy(kernel, KERNELS[_random(NUM_KERNELS - 1)]);
    client_info.kernel = kernel;
    return client_info;
}

/**
 * Libera un número aleatorio de espacios en el segmento de memoria compartida.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param sem_id semaforo para la memoria compartida.
 * @param max_num_clients número máximo de clientes.
 */
void _free_shm_space(char *shm_address, int sem_id, int max_num_clients) {
    int num_to_free = (int) _random(max_num_clients - 1);
    for (int i = 0; i < num_to_free; ++i) {
        delete_client_info(shm_address, (int) _random(max_num_clients - 1), sem_id);
    }
}

/**
 * Número aleatorio en el rango [0, max].
 * @param max límete superior.
 * @return número aleatorio.
 */
long _random(long max) {
    unsigned long num_bins = (unsigned long) max + 1,
            num_rand = (unsigned long) RAND_MAX + 1,
            bin_size = num_rand / num_bins,
            defect = num_rand % num_bins;

    long x;
    do {
        x = random();
    } while (num_rand - defect <= (unsigned long) x);

    return x / bin_size;
}