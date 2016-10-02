/*
 * ****************************************************************************
 * File_mng.c
 *
 * Librería que contiene funciones para la gestión de archivos y directorios.
 * ****************************************************************************
 */

#include "file_mng.h"

// PRIVATE HEADERS
int _iterate_dir(const char *dirPath, int depth);

void _print_entry(char *name, int depth);

void _get_new_path(const char *dirPath, char *dirName, char *newDirPath);

int _print_file(int fd);

/**
 * Muestra el contenido del directorio especificado recursivamente.
 * Ej: ver_directorio(".");
 *
 * @param dirPath Puntero al nombre de la ruta (absoluta o relativa)
 * @return EXIT_SUCCESS si ok, EXIT_FAILURE si error
 */
int ver_directorio(const char *dirPath) {
    puts(dirPath);
    return _iterate_dir(dirPath, 1);
}

/**
 * Muestra el contenido del directorio especificado recursivamente.
 *
 * @param dirPath Puntero al nombre de la ruta (absoluta o relativa)
 * @param depth profundidad (utilizado para saber el nivel en el que está)
 * @return EXIT_SUCCESS si ok, EXIT_FAILURE si error
 */
int _iterate_dir(const char *dirPath, int depth) {
    DIR *dir;
    struct dirent *dp;

    // Abrir directorio
    if ((dir = opendir(dirPath)) == NULL) {
        perror("Error al abrir directorio");
        return EXIT_FAILURE;
    }

    // Leer entradas del directorio
    while ((dp = readdir(dir)) != NULL) {
        _print_entry(dp->d_name, depth);
        // Leer directorios recursivamente
        if (dp->d_type == DT_DIR && strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..")) {
            char newDirPath[PATH_MAX];
            _get_new_path(dirPath, dp->d_name, newDirPath);
            _iterate_dir(newDirPath, depth + 1);
        }
    }

    // Cerrar directorio
    return closedir(dir);
}

/**
 * Imprime la entrada indentada dependiendo de la profundidad.
 *
 * @param name nombre a imprimir
 * @param depth profundidad
 */
void _print_entry(char *name, int depth) {
    printf("%*s %s\n", depth * 2 + 1, "└", name);
}

/*
 * Devuelve el path del directorio pasado.
 * newDirPath = dirPath + "/" + dirName
 */
void _get_new_path(const char *dirPath, char *dirName, char *newDirPath) {
    strcpy(newDirPath, dirPath);
    strcat(newDirPath, "/");
    strcat(newDirPath, dirName);
}

/**
 * Muestra la ruta hasta el archivo buscado.
 * Ej: buscar_archivo(".", "README.md");
 *
 * @param currDir Puntero al nombre de la ruta (absoluta o relativa)
 * @param fileName Nombre del archivo con extension incluida
 * @return EXIT_SUCCESS si ok, EXIT_FAILURE si error
 */
int buscar_archivo(const char *currDir, const char *fileName) {
    // Abrir el directorio
    DIR *dir = opendir(currDir);
    struct dirent *itdir;
    char newDir[PATH_MAX];
    // Si se ha podido
    if (dir) {
        // Lee las entradas internas
        while ((itdir = readdir(dir)) != NULL) {
            // Si son directorios menos . y .. -> recursividad. Si no, comprueba si el nombre coincide
            if (itdir->d_type == DT_DIR && strcmp(itdir->d_name, ".") != 0 && strcmp(itdir->d_name, "..") != 0) {
                _get_new_path(currDir, itdir->d_name, newDir);
                buscar_archivo(newDir, fileName);
            } else {
                if (itdir->d_type == DT_REG && strcmp(itdir->d_name, fileName) == 0) {
                    _get_new_path(currDir, itdir->d_name, newDir);
                    _print_entry(newDir, 0);
                }
            }
        }
        closedir(dir);
        return EXIT_SUCCESS;
    }
    perror("Error al abrir directorio");
    return EXIT_FAILURE;
}


/**
 * Bloquea el archivo pasado como fd y según lo que ponga en rw lo bloquea como lectura o escritura
 * @param fd archivo
 * @param rw 'r' o 'w' segun sea lectura o escritura
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int bloqueo(int fd, char rw) {
    struct flock lock;
    memset (&lock, 0, sizeof(lock));

    // Establecer bloqueo solicitado
    switch (rw) {
        case 'r':
            lock.l_type = F_RDLCK; // Read block
            break;
        case 'w':
            lock.l_type = F_WRLCK; // Write block
            break;
        default:
            perror("Segundo parametro incorrecto.");
            return EXIT_FAILURE;
    }

    // Resto de opciones del bloquo
    lock.l_whence = SEEK_SET; // From the beginning
    lock.l_start = 0;        // From byte 0
    lock.l_len = 0;        // To EOF (0=EOF)
    lock.l_pid = getpid(); // our PID

    // Intentar bloquear
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        fcntl(fd, F_GETLK, &lock);
        perror("El archivo está bloqueado por otro proceso.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


/**
 * Desbloquea el archivo bloqueado por este mismo programa.
 * @param fd archivo
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int desbloqueo(int fd) {
    struct flock lock;

    // Desbloquear el fichero desde la posicion inicial hasta la final
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET; // From the beginning
    lock.l_start = 0;        // From byte 0
    lock.l_len = 0;        // To EOF (0=EOF)
    lock.l_pid = getpid(); // our PID

    // Intentar bloquear
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        fcntl(fd, F_GETLK, &lock);
        perror("No se ha podido desbloquear.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


/**
 * Imprime por pantalla el archivo pasado.
 * @param file puntero a la ruta, absoluta o relativa.
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int ver_archivo(const char *file) {
    int fd;

    // Abrir archivo
    if ((fd = open(file, O_RDONLY)) < 0) {
        perror("Error en la apertura del archivo\n");
        return EXIT_FAILURE;
    }
    // Bloquear fichero para lectura
    if (bloqueo(fd, 'r') == EXIT_FAILURE) {
        perror("No se ha podido establecer el bloqueo.");
        close(fd);
        return EXIT_FAILURE;
    }
    // Leer archivo
    int ok = _print_file(fd);
    // Liberar bloqueo
    desbloqueo(fd);
    // Cerrar archivo
    close(fd);
    return ok;
}

/**
 * Imprime el contenido de un archivo dado su descriptor.
 * Este debe estar listo para su lectura (bloqueo requerido).
 * @param fd descriptor del archivo
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int _print_file(int fd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = 0;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytes_read]='\0';
        printf("%s", buffer);
    }
    if (bytes_read == -1 && errno != 0) {
        perror("Error en la lectura del archivo.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
