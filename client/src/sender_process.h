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
#include <stdbool.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <zconf.h>

#include "../../lib/sig_mng.h"

// DEFINES
#define BUFFER_SIZE 1024
#define NO_RETRIES 3

// PROTOTYPES
int sender_process();

#endif //CLIENT_SENDER_H
