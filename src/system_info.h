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

#endif //ROSTROJAN_SYSTEM_INFO_H

