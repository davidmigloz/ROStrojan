#include "system_info.h"
#define H_N_LENGTH 20


/**
 * ver_usuarioActual: function that returns a pointer to a string containing the user name of the caller.
 * @return pointer to a string
 */
int ver_usuarioActual(char* username, int length) {
    return 0;
}

/**
 * ver_equipo: function that returns a pointer to a string containing the name of the host.
 * @return pointer to a string or null in operation failure
 */
int ver_equipo() {
    ver_archivo("/proc/sys/kernel/hostname");
}
