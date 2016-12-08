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

    // Configurar socket
    struct sockaddr_in server_addr;
    struct hostent *host;
    char buffer[BUFFER_SIZE];

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("SOCKET: socket error.\n");
        exit(EXIT_FAILURE);
    }

    atexit(_close_socket);
    memset(&server_addr, 0, sizeof(server_addr));
    host= gethostbyname(get_var_value("CONECTIONS", "server_ip"));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons((uint16_t) atoi(get_var_value("CONECTIONS", "server_port")));
    memcpy(&server_addr.sin_addr, host->h_addr_list[0], (size_t) host->h_length);

    // Configurar bucle de reenvío de información
    _Bool running = true;
    int interval = atoi(get_var_value("CONECTIONS", "interval")), end;
    client_info client_inf;

    while (running) {

        // Captar información del pc
        memset((char *) &client_inf, 0, sizeof(client_inf));
        strcpy(client_inf.ip, ver_ip());
        strcpy(client_inf.kernel, ver_kernel());
        strcpy(client_inf.name, ver_equipo());
        strcpy(client_inf.user, ver_usuario_actual());

        // Rellenar buffer
        memset(buffer, '\0', sizeof(buffer));
        memcpy(buffer, (char *) &client_inf, sizeof(client_inf));

        // Enviamos informacion con N reintentos
        for (int errors = 0; errors < NO_RETRIES; errors++) {
            if (sendto(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &server_addr,
                       sizeof(struct sockaddr)) != -1) {
                puts("Informacion enviada!\n");
                break;
            }
            perror("Error while sending data.\n");
            if((errors + 1) < NO_RETRIES) {
                puts("Retrying...\n");
                sleep(10);
            } else {
                puts("Error alcanzado maximo numero de reintentos\nCerrando...\n");
                exit(EXIT_FAILURE);
            }
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
        } while (i <= interval);
    }
    return EXIT_SUCCESS;
}

void _close_socket() {
    shutdown(socket_fd, SHUT_RDWR);
}
