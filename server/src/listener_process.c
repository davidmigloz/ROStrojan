/*
 * ********************************************************************
 * listener_process.c
 *
 * Lógica del proceso listener.
 * Encargado de recibir paquetes y datos de los clientes.
 * ********************************************************************
 */

#include "listener_process.h"

// PRIVATE HEADERS

/**
 * Lógica del proceso listener.
 * Encargado recibir peticiones de conexión, desconexión y los datos de los clientes.
 * @param sem_id semaforo para la memoria compartida.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param max_num_clients número máximo de clientes.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int listener_process(int sem_id, char *shm_address, int max_num_clients) {
    _Bool running = true;
    int end;

    // Bloquear señales
    if (bloq_signals()) {
        perror("LIST: bloq_signals error\n");
        exit(EXIT_FAILURE);
    }

    // Crear socket
    struct sockaddr_in entrada, cliente;
    int descriptor;
    char buffer[BUFFER_SIZE];

    if ((descriptor=socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Error creating socket\n");
        exit(EXIT_FAILURE);
    }

    memset((char *) &entrada, '0', sizeof(entrada));
    entrada.sin_family = AF_INET;
    entrada.sin_port = htons(PORT);
    entrada.sin_addr.s_addr = htonl(INADDR_ANY); // TODO es necesario el htonl?

    if( bind(descriptor , (struct sockaddr*)&entrada, sizeof(entrada) ) == -1) {
        perror("Error linking socket\n");
        exit(EXIT_FAILURE);
    }

    while (running) {
        // Recibir datos
        if (recvfrom(descriptor, buffer, BUFFER_SIZE, 0,
                     (struct sockaddr *) &cliente, (socklen_t *) sizeof(cliente)) == -1) {
            perror("Error reciving data\n");
            continue;
        }

        // Parsear datos
        client_info *client_info = (struct client_info *) ((void *) buffer);

        // Añadir info cliente
        int ok = add_client_info(shm_address, client_info, max_num_clients, sem_id);
        if (ok == EXIT_FAILURE) {
            // Añadir info cliente de nuevo
            add_client_info(shm_address, client_info, max_num_clients, sem_id);
        }

        int i = 0;
        do {
            // Comprobamos si hay que terminar (si se ha recibido SIGUSR1)
            end = received_end();
            if (end == -1) {
                perror("LIST: received_end error\n");
                exit(EXIT_FAILURE);
            } else if (end == SIGNAL_RECEIVED) {
                running = false;
                break;
            }
            // Dormimos el proceso
            sleep(1);
            i++;
        } while (i <= DELAY);
    }
    return EXIT_SUCCESS;
}
