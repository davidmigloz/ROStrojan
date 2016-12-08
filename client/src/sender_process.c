/*
 * ********************************************************************
 * sender_process.c
 *
 * Lógica del proceso sender.
 * Encargado de enviar datos de cliente hasta el servidor.
 * ********************************************************************
 */
#include "sender_process.h"

// PRIVATE HEADERS
void _close_socket();

// GLOBAL VARS
int socket_fd;

/**
 * Lógica del proceso sender.
 * Encargado enviar los datos del cliente al servidor.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int sender_process() {
    int end;
    _Bool running = true;

    // Leemos el num de segundos del entorno
    int seconds = atoi(get_var_value("client", "seconds"));

    // Para crear socket
    char buffer[BUFFER_SIZE];
    struct sockaddr_in local_sock, remote_sock;

    // Creamos un socket
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("SEND: socket error\n");
        exit(EXIT_FAILURE);
    }

    // Inicializamos local_sock
    memset(&local_sock, 0, sizeof(local_sock)); // Establecer a 0 the toda la estructura
    local_sock.sin_family = AF_INET;
    local_sock.sin_addr.s_addr = htonl(INADDR_ANY);
    local_sock.sin_port = htons((uint16_t) atoi(get_var_value("client", "client_port")));

    // Nos acoplamos al socket
    if (bind(socket_fd, (struct sockaddr *) &local_sock, sizeof(local_sock)) == -1) {
        perror("SEND: bind error\n");
        exit(EXIT_FAILURE);
    }

    atexit(_close_socket);

    // Inicializamos remote_sock
    memset(&remote_sock, 0, sizeof(remote_sock));
    remote_sock.sin_family = AF_INET;
    remote_sock.sin_addr.s_addr = htonl((uint32_t) atoi(get_var_value("client", "server_ip")));
    remote_sock.sin_port = htons((uint16_t) atoi(get_var_value("client", "server_port")));

    // Obtener info del pc
    client_info client_inf;
    memset(&client_inf, 0, sizeof(client_inf));
    strcpy(client_inf.ip, ver_ip());
    strcpy(client_inf.kernel, ver_kernel());
    strcpy(client_inf.name, ver_equipo());
    strcpy(client_inf.user, ver_usuario_actual());

    // Rellenar buffer
    strncpy(buffer, (char *) &client_inf, sizeof(client_inf));

    while (running) {
        // Enviamos informacion con N reintentos
        for (int errors = 0; errors < NO_RETRIES; errors++) {
            if (sendto(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &remote_sock,
                       sizeof(remote_sock)) != -1) {
                break;
            }
            perror("SEND: sendto error\n");
            // Si falla la comunicacion le damos unos segundos para ver si se recupera
            sleep(10);
        }

        // Esperamos hasta el siguiente envío de información
        int i = 0;
        do {
            // Comprobamos si hay que terminar (si se ha recibido SIGUSR1)
            end = received_end();
            if (end == -1) {
                perror("LIST: received_end error\n");
                exit(EXIT_FAILURE);
            } else if (end == SIGNAL_RECEIVED) {
                running = 0;
                break;
            }
            // Dormimos el proceso
            sleep(1);
            i++;
        } while (i <= seconds);
    }
    return EXIT_SUCCESS;
}

void _close_socket() {
    shutdown(socket_fd, SHUT_RDWR);
}
