/*
 * ********************************************************************
 * sender_process.c
 *
 * Lógica del proceso sender.
 * Encargado de enviar datos de cliente hasta el servidor.
 * ********************************************************************
 */

#include <string.h>
#include "sender_process.h"

int sender_process() {
    // TODO move signal (sig_mng.h) to libs
    // Bloquear señales
    if (bloq_signals()) {
        perror("SEND: bloq_signals error\n");
        exit(EXIT_FAILURE);
    }
    int seconds = 60 * 5; // TODO read seconds from file
    int end;
    _Bool running = true;
    ssize_t written_bytes;
    // Para crear socket
    int socket_fd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in local_sock, remote_sock; // TODO read IP and port and Server Port from file-> REDO

    // Creamos un socket
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("SEND: socket error\n");
        exit(EXIT_FAILURE);
    }
    // Inicializamos local_sock
    memset(&local_sock, '0', sizeof(local_sock));
    // TODO REDO
    #define LOCALPORT 7654
    #define REMOTEPORT 7654

    local_sock.sin_family = AF_INET;
    local_sock.sin_addr.s_addr = INADDR_ANY; // TODO es necesario htonl?
    local_sock.sin_port = htons(LOCALPORT);
    // TODO END REDO

    // nos acoplamos al socket
    if (bind(socket_fd, (struct sockaddr *) &local_sock, sizeof(local_sock)) == -1) {
        perror("SEND: bind error\n");
        exit(EXIT_FAILURE);
    }

    // Inicializamos remote_sock
    memset(&remote_sock, '0', sizeof(remote_sock));

    remote_sock.sin_family = AF_INET;
    remote_sock.sin_port = htons(REMOTEPORT);

    while (running) {
        // TODO get information to send->BUFFER -> in struct client_info format.

        // enviamos informacion con N reintentos
        for (int errors = 0; errors < NO_RETRIES; errors++) {
            if (sendto(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &remote_sock, sizeof(remote_sock))!=-1) {
                break;
            }
            perror("SEND: sendto error\n");
        }
        // esperamos unos segundos
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
        } while (i <= seconds);
    }


}

