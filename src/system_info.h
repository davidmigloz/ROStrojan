/**
 * system_info.h
 *
 * Libreria que haciendo uso de file_mng.h para conseguir informacion del sistema
 */

#include "file_mng.h"


#ifndef ROSTROJAN_SYSTEM_INFO_H
#define ROSTROJAN_SYSTEM_INFO_H

/**
 * ver_usuarioActual: function that returns a pointer to a string containing the user name of the caller.
 * @return pointer to a string
 */
int ver_usuarioActual(char* username, int length);

/**
 * ver_equipo: function that returns a pointer to a string containing the name of the host.
 * @return pointer to a string or null in operation failure
 */
int ver_equipo();

#endif //ROSTROJAN_SYSTEM_INFO_H

