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
 * @param socket_fd descriptor del socket.
 * @param max_num_clients número máximo de clientes.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int listener_process(int sem_id, char *shm_address, int socket_fd, int max_num_clients) {
    _Bool running = true;
    int end;

    // Bloquear señales
    if (bloq_signals()) {
        perror("LIST: bloq_signals error\n");
        exit(EXIT_FAILURE);
    }

    // Configurar socket
    ssize_t bytes_read;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    memset(&server_addr, 0, sizeof(server_addr)); // Establecer a 0 the toda la estructura
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t addr_len = sizeof(struct sockaddr);

    if (bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1) {
        perror("Error linking socket\n");
        exit(EXIT_FAILURE);
    }

    // Bucle de ejecución
    while (running) {
        // Recibir datos
        bytes_read = recvfrom(socket_fd, buffer, BUFFER_SIZE, 0,
                              (struct sockaddr *) &client_addr, &addr_len);

        if (bytes_read > 0) {
            puts("Data received!");
            // Parsear datos
            client_info *client_info = (struct client_info *) ((void *) buffer);

            // Añadir info cliente
            int ok = add_client_info(shm_address, client_info, max_num_clients, sem_id);
            if (ok == EXIT_SUCCESS) {
            } else {
                perror("Error while saving data.");
            }
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

    // Cerrar socket
    close(socket_fd);
    return EXIT_SUCCESS;
}
