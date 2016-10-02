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