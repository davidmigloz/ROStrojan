/*
 * ********************************************************************
 * sender_process.h
 *
 * Lógica del proceso sender.
 * Encargado de enviar datos de cliente hasta el servidor.
 * ********************************************************************
 */
#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

// INCLUDES
#include <netinet/in.h>
#include <string.h>
#include "../../lib/file_mng.h"
#include "../../lib/system_info.h"
#include "../../lib/env_mng.h"
#include "../../lib/sig_mng.h"

// DEFINES
#define NAMES_MAXLENGHT 100
#define BUFFER_SIZE 1024
#define NO_RETRIES 3

// STRUCTS
typedef struct client_info client_info;
struct client_info {
    _Bool used;
    int id;
    time_t last_conn;
    char name[NAMES_MAXLENGHT + 1];
    char user[NAMES_MAXLENGHT + 1];
    char ip[NAMES_MAXLENGHT + 1];
    char kernel[NAMES_MAXLENGHT + 1];
};

// PROTOTYPES
int sender_process();

#endif //CLIENT_SENDER_H
