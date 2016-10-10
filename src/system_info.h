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
#include <ctype.h>

#include "file_mng.h"

// CONSTANTS
#define P_ID        3
#define PU_NAME     1
#define PU_GROUP    4
#define PU_HOME_DIR 6
#define PG_NAME     1
#define PG_GID      3
#define PG_MEMBERS  4
#define F_PASSWD    "/etc/passwd"
#define F_GROUP     "/etc/group"

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
 * Muestra la IP (o las IPs) del equipo.
 * Estas las obtiene del fichero /proc/net/fib_trie.
 *
 * @return cadena con la/s IPs
 */
char *ver_ip();

/**
 * Imprime el uid, grupo principal y directorio home del usuario pasado,
 * o de todos los usuarios del sistema si se pasa NULL.
 * @param uid nombre de usuario
 */
void ver_usuario(char *uid);

/**
 * Imprime el nombre, gid y miembros del grupo pasado,
 * o de todos los grupos del sistema si se pasa NULL.
 * @param gid id del grupo
 */
void ver_grupo(char *gid);

#endif