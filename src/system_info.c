/*
 * ****************************************************************************
 * system_info.h
 *
 * Libreria que permite acceder a información del sistema.
 * ****************************************************************************
 */

#include "system_info.h"

// PRIVATE HEADERS
char *_read_one_line_file(char *file, int max_length);

/**
 * Devuelve el usuario actual del sistema.
 * @return string con el usuario
 */
char *ver_usuario_actual() {
    const char *user = getenv("USER");
    return (char *) ((user != NULL) ? user : "");
}

/**
 * Devuelve el nombre del equipo.
 * @return string con el equipo
 */
char *ver_equipo() {
    // Fichero donde se almacena el nombre del equipo
    char *FILE = "/etc/hostname";
    return _read_one_line_file(FILE, HOST_NAME_MAX);
}

/**
 * Devuelve el nombre del sistema operativo.
 * @return string con el so
 */
char *ver_sistema() {
    // Fichero donde se almacena el nombre del SO
    char *FILE = "/etc/issue";
    return _read_one_line_file(FILE, 128);
}

/**
 * Devuelve la versión del kernel.
 * @return string con el kernel
 */
char *ver_kernel() {
    // Fichero donde se almacena el nombre del kernel
    char *FILE = "/proc/version";
    return _read_one_line_file(FILE, 1024);
}

/**
 * Muestra la IP del equipo (host name).
 * @return pointer to a string
 */
char *ver_ip() {
    FILE *pp = popen("hostname --ip-address", "r");
    char *line = NULL;
    char buf[BUFFER_SIZE];
    if (pp != NULL) {
        line = fgets(buf, sizeof buf, pp);
    }
    return line;
}

/**
 * Lee archivos de una línea devolviendo una cadena de texto.
 * @param file ubicación del archivo
 * @param max_length longitud máxima de la cadena de texto
 * @return cadena de texto con la línea leida
 */
char *_read_one_line_file(char *file, int max_length) {
    // Abrimos el archivo
    int fd;
    if ((fd = open_file(file, OF_READ)) == EXIT_FAILURE) {
        return "";
    }

    // Leer archivo
    size_t buffer_size = max_length * sizeof(char) + 1;
    char *buffer = malloc(buffer_size);
    if (read_line(fd, buffer, buffer_size) == EXIT_FAILURE) {
        return "";
    }

    // Cerramos el archivo
    close_file(fd);
    return buffer;
}