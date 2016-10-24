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

void _info_user(char *user_line);

void _print_user_info(char *name, char *gid, char *members);

void _info_group(char *group_line);

void _print_info_group(char *name, char *gid, char *members);

void _iterate_file(char *file);

char *_get_line_by_id(char *id, char *file);

char *_parse_line(char *line, int field);

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
 * Muestra la IP (o las IPs) del equipo.
 * Estas las obtiene del fichero /proc/net/fib_trie.
 *
 * @return cadena con la/s IPs
 */
char *ver_ip() {
    // Abrir archivo
    int fd, ok;
    if ((fd = open_file("/proc/net/fib_trie", OF_READ)) == EXIT_FAILURE) {
        perror("Error al abrir archivo");
        return NULL;
    }
    // Recorrer archivo
    char *line_prev = malloc(BUFFER_SIZE);
    char *line_act = malloc(BUFFER_SIZE);
    char *ips = malloc(BUFFER_SIZE);
    ips[0] = '\0';

    do {
        if ((ok = read_line(fd, line_act, BUFFER_SIZE)) == EXIT_FAILURE) {
            perror("Error al leer passwd");
            free(line_prev);
            free(line_act);
            free(ips);
            close_file(fd);
            return NULL;
        }
        // Comprobar si se ha llegado a la sección "Local" -> salir
        if (strstr(line_act, "Local") != NULL) {
            ips[strlen(ips) - 2] = '\0'; // Quitar último separador
            free(line_prev);
            free(line_act);
            close_file(fd);
            return ips;
        }
        // Comprobar si la línea contine "32 host LOCAL"
        if (strstr(line_act, "32 host LOCAL") != NULL) {
            if (strstr(line_prev, "127.0.0.1") != NULL) {
                // Si es Loopback IP -> no mostrar
            } else {
                // Si no, la IP está en la línea anterior
                for (int i = 0; i < strlen(line_prev); i++) {
                    if (isdigit(line_prev[i])) {
                        strcat(ips, strncpy(line_prev, line_prev + i, strlen(line_prev) - (i - 1)));
                        strcat(ips, " / ");
                    }
                }
            }

        }
        // Si no lo contiene, copiar la línea actial a línea anterior
        strcpy(line_prev, line_act);
    } while (ok != END_OF_FILE);
    // Liberar memoria
    free(line_prev);
    free(line_act);
    free(ips);
    // Cerrar archivo
    close_file(fd);
    return ips;
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
    size_t buffer_size = (size_t) (max_length + 1);
    char *buffer = malloc(buffer_size);
    if (read_line(fd, buffer, buffer_size) == EXIT_FAILURE) {
        close_file(fd);
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
        _iterate_file(F_PASSWD);
    } else {
        _info_user(_get_line_by_id(uid, F_PASSWD));
    }
}

/**
 * Imprime el uid, grupo principal y directorio home del usuario.
 * @param user_line línea del usuario en el archivo passwd
 */
void _info_user(char *user_line) {
    if (user_line == NULL) {
        puts("El usuario no existe.");
        return;
    }
    // Obtener info
    char *name = _parse_line(user_line, PU_NAME);
    char *group = _parse_line(user_line, PU_GROUP);
    char *home_dir = _parse_line(user_line, PU_HOME_DIR);
    _print_user_info(name, group, home_dir);
}

/**
 * Imprime por pantalla el usuario, grupo y directorio bien formateado.
 * @param uid nombre usuario
 * @param group grupo
 * @param home_dir directorio home
 */
void _print_user_info(char *uid, char *group, char *home_dir) {
    printf("-Usuario:\t%s\n-Grupo:\t\t%s\n-Home dir:\t%s\n", uid, group, home_dir);
}

/**
 * Imprime el nombre, gid y miembros del grupo pasado,
 * o de todos los grupos del sistema si se pasa NULL.
 * @param gid id del grupo
 */
void ver_grupo(char *gid) {
    if (gid == NULL) {
        _iterate_file(F_GROUP);
    } else {
        _info_group(_get_line_by_id(gid, F_GROUP));
    }
}

/**
 * Imprime el nombre, gid y miembros del grupo.
 * @param group_line línea del grupo en el archivo group
 */
void _info_group(char *group_line) {
    if (group_line == NULL) {
        puts("El grupo no existe.");
        return;
    }
    // Obtener info
    char *name = _parse_line(group_line, PG_NAME);
    char *gid = _parse_line(group_line, PG_GID);
    char *members = _parse_line(group_line, PG_MEMBERS);
    _print_info_group(name, gid, (members == NULL) ? "-" : members);
}

/**
 * Imprime por pantalla el nombre del gripo, gid y sus miembros.
 * @param name nombre grupo
 * @param gid id del grupo
 * @param members miembros del griupo
 */
void _print_info_group(char *name, char *gid, char *members) {
    printf("-Nombre:\t%s\n-GID:\t\t%s\n-Miembros:\t%s\n", name, gid, members);
}

/**
 * Itera sobre los distintos usuarios o grupos del sistema.
 * @param file PASSWD para usuarios o GROUP para grupos
 */
void _iterate_file(char *file) {
    int fd, ok;
    char *buffer = malloc(BUFFER_SIZE);
    char *tmp = malloc(BUFFER_SIZE);

    // Abrir archivo
    if ((fd = open_file(file, OF_READ)) == EXIT_FAILURE) {
        free(buffer);
        free(tmp);
        close_file(fd);
        perror("Error al abrir archivo");
        return;
    }
    // Iterar sobre todos los usuarios/grupos
    do {
        if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
            free(buffer);
            free(tmp);
            close_file(fd);
            perror("Error al leer passwd");
            return;
        }
        // Imprimir info
        if (strcmp(file, F_PASSWD) == 0) {
            _info_user(buffer);
        } else {
            _info_group(buffer);

        }
        puts("------------------");
    } while (ok != END_OF_FILE);
    // Liberar memoria
    close_file(fd);
    free(buffer);
    free(tmp);
}

/**
 * Dado un uid/gid devuelve la línea de ese usuario/grupo en el archivo passwd/group.
 * Si no existe devuelve NULL.
 * @param id uid de usuario o gid de grupo
 * @param file PASSWD para usuarios o GROUP para grupos
 * @return línea del usuario o grupo
 */
char *_get_line_by_id(char *id, char *file) {
    int fd, ok;
    char *buffer = malloc(BUFFER_SIZE);
    char *id_read;

    // Abrir archivo
    if ((fd = open_file(file, OF_READ)) == EXIT_FAILURE) {
        free(buffer);
        return NULL;
    }
    // Iterar hasta encontrar id
    do {
        if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
            close_file(fd);
            free(buffer);
            return NULL;
        }
        // Comprobar si es la línea con ese id
        id_read = _parse_line(buffer, P_ID);
        if (strcmp(id, id_read) == 0) {
            close_file(fd);
            return buffer;
        }
    } while (ok != END_OF_FILE);
    // Liberar memoria
    free(buffer);
    close_file(fd);
    return NULL; // No existe
}

/**
 * Parsea el campo deseado de una línea del archivo passwd o group.
 * Campos disponibles para usuarios:
 *      - PU_NAME: nombre de usuario.
 *      - PU_GROUP: grupo primario del usuario.
 *      - PU_HOME_DIR: directorio home del usuario.
 * Campos disponibles para grupos:
 *      - PG_NAME: nombre del grupo.
 *      - PG_GID: id del grupo.
 *      - PG_MEMBERS: miembros del grupo.
 * @param line línea del usuario/grupo en el archivo passwd/group
 * @param field campo a extraer
 * @return valor del campo
 */
char *_parse_line(char *line, int field) {
    char *tmp = malloc(BUFFER_SIZE);
    strcpy(tmp, line);
    // Obtener campo deseado
    char *value = strtok(tmp, ":");
    for (int i = 1; i < field; i++) {
        value = strtok(NULL, ":");
    }
    return value;
}