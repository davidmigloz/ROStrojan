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

void _print_info_users();

void _print_info_user(char *uid);

char *_get_user_line(char *uid);

char *_parse_passwd_line(char *line, int field);

void _print_info(char *uid, char *group, char *home_dir);

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

/**
 * Imprime el uid, grupo principal y directorio home del usuario pasado,
 * o de todos los usuarios del sistema si se pasa NULL.
 * @param uid nombre de usuario
 */
void ver_usuario(char *uid) {
    if (uid == NULL) {
        _print_info_users();
    } else {
        _print_info_user(uid);
    }
}

/**
 * Imprime el uid, grupo principal y directorio home de todos los usuarios del sistema.
 */
void _print_info_users() {
    int fd, ok;
    char *buffer = malloc(BUFFER_SIZE);
    char *tmp = malloc(BUFFER_SIZE);
    char *username;
    char *group;
    char *home_dir;

    // Abrir passwd
    if ((fd = open_file("/etc/passwd", OF_READ)) == EXIT_FAILURE) {
        perror("Error al abrir passwd");
        return;
    }
    // Iterar sobre todos los usuarios
    do {
        if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
            perror("Error al leer passwd");
            return;
        }
        // Imprimir info
        strcpy(tmp, buffer);
        username = strtok(tmp, ":");
        group = _parse_passwd_line(buffer, P_GROUP);
        home_dir = _parse_passwd_line(buffer, P_HOME_DIR);
        _print_info(username, group, home_dir);
        puts("------------------");
    } while (ok != END_OF_FILE);
    // Liberar memoria
    free(buffer);
    free(tmp);
}

/**
 * Imprime el uid, grupo principal y directorio home del usuario pasado.
 * @param uid nombre de usuario
 */
void _print_info_user(char *uid) {
    char *user_line = _get_user_line(uid);
    if (user_line == NULL) {
        puts("El usuario no existe.");
        return;
    }
    // Obtener grupo y directorio
    char *group = _parse_passwd_line(user_line, P_GROUP);
    char *home_dir = _parse_passwd_line(user_line, P_HOME_DIR);
    _print_info(uid, group, home_dir);
}

/**
 * Dado un usuario devuelve la línea de ese usuario en el archivo passwd.
 * Si no existe devuelve NULL.
 * @param uid nombre de usuario
 * @return línea del usuario en passwd
 */
char *_get_user_line(char *uid) {
    int fd, ok;
    char *buffer = malloc(BUFFER_SIZE);
    char *tmp = malloc(BUFFER_SIZE);
    char *username;

    // Abrir passwd
    if ((fd = open_file("/etc/passwd", OF_READ)) == EXIT_FAILURE) {
        return NULL;
    }

    // Iterar hasta encontrar usuario
    do {
        if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
            return NULL;
        }
        // Comprobar si es la línea del usuario
        strcpy(tmp, buffer);
        username = strtok(tmp, ":");
        if (strcmp(uid, username) == 0) {
            free(tmp);
            return buffer;
        }
    } while (ok != END_OF_FILE);
    return NULL; // No existe ese usuario
}

/**
 * Parsea el campo deseado de una línea del archivo passwd.
 * Campos disponibles:
 *      - P_GROUP: grupo primario del usuario.
 *      - P_HOME_DIR: directorio home del usuario.
 * @param line línea del usuario en el archivo passwd
 * @param field campo a extraer
 * @return valor del campo
 */
char *_parse_passwd_line(char *line, int field) {
    char *tmp = malloc(BUFFER_SIZE);
    strcpy(tmp, line);
    // Obtener campo deseado
    char *value = strtok(tmp, ":");
    for (int i = 1; i < field; i++) {
        value = strtok(NULL, ":");
    }
    return value;
}

/**
 * Imprime por pantalla el usuario, grupo y directorio bien formateado.
 * @param uid nombre usuario
 * @param group grupo
 * @param home_dir directorio home
 */
void _print_info(char *uid, char *group, char *home_dir) {
    printf("-Usuario:\t%s\n-Grupo:\t\t%s\n-Home dir:\t%s\n", uid, group, home_dir);
}