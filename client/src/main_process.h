/**
 * ********************************************************************
 * main_process.c
 *
 * Lógica del cliente, su menu y la invocación de su hijo que controla 
 * la red.
 * ********************************************************************
 */
#ifndef CLIENT_MAIN_PROCESS_H
#define CLIENT_MAIN_PROCESS_H

// INCLUDES
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "sender_process.h"


// PROTOTYPES
int main_process();

#endif //CLIENT_MAIN_PROCESS_H
