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
 * Obtener el usuario actual del sistema.
 * @return string con el usuario
 */
char *ver_usuario_actual();

/**
 * Devuelve el nombre del equipo.
 * @return string con el equipo
 */
char *ver_equipo();

/**
 * Devuelve el nombre del sistema operativo.
 * @return string con el so
 */
char *ver_sistema();

/**
 * Devuelve la versión del kernel.
 * @return string con el kernel
 */
char *ver_kernel();

/**
 * Devuelve la IP del equipo (host name).
 * @@param hostname  pointer to a string
 */
char *ver_ip();

#endif