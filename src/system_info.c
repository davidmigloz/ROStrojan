/*
 * ****************************************************************************
 * system_info.h
 *
 * Libreria que permite acceder a información del sistema.
 * ****************************************************************************
 */

#include "system_info.h"

// PRIVATE HEADERS


/**
 * Get the current user of the system.
 * @return pointer to a string
 */
const char * ver_usuario_actual() {
    const char* user = getenv("USER");
    return (user != NULL) ? user : "";
}

/**
 * ver_equipo: function that shows the name of the host.
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int ver_equipo() {
    return ver_archivo("/etc/hostname");
}

/**
 * ver_sistema: function that shows the name of the operating system.
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int ver_sistema(){
    return ver_archivo("/etc/issue");
}

/**
 * ver kernel: function that shows the kernel version
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int ver_kernel(){
    return ver_archivo("/proc/version");
}