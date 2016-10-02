/*
 * ****************************************************************************
 * system_info.h
 *
 * Libreria que permite acceder a información del sistema.
 * ****************************************************************************
 */

#ifndef ROSTROJAN_SYSTEM_INFO_H
#define ROSTROJAN_SYSTEM_INFO_H

// INCLUDES
#include <unistd.h>

#include "file_mng.h"

// CONSTANTS

// PROTOTYPES

/**
 * Get the current user of the system.
 * @return pointer to a string
 */
char * ver_usuario_actual();

/**
 * ver_equipo: function that shows the name of the host.
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int ver_equipo();

/**
 * ver_sistema: function that shows the name of the operating system.
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int ver_sistema();

/**
 * ver kernel: function that shows the kernel version
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int ver_kernel();

/**
 * Devuelve la IP del equipo (host name).
 * @@param hostname  pointer to a string
 */
char* ver_ip();

#endif