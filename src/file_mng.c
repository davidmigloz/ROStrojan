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
int bloqueo(int fd, int mode) {
    struct flock lock;
    memset (&lock, 0, sizeof(lock));

    // Establecer bloqueo solicitado
    switch (mode) {
        case OF_READ:
            lock.l_type = F_RDLCK; // Read block
            break;
        case OF_WRITE:
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
    int fd, ok;
    //abrimos el archivo
    if ((fd = open_file(file, OF_READ)) != EXIT_FAILURE) {
        ok = _print_file(fd);
    }
    //cerramos el archivo
    close_file(fd);
    //devolvemos si ha funcionado la impresion
    return ok;
}


/**
 * Imprime el contenido de un archivo dado su descriptor.
 * Este debe estar listo para su lectura (bloqueo requerido).
 * @param fd descriptor del archivo.
 * @return EXIT_FAILURE o EXIT_SUCCESS.
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



/**
 * Abre un archivo y lo bloquea con el modo elegido.
 * Los modos permitidos son OF_READ y OF_WRITE por el momento.
 * Ejemplos de uso: open_file("./Downloads/descarga1.txt", OF_READ);
 *                  open_file("/home/user/mitexto.txt", OF_WRITE);.
 * @param file puntero a la cadena de caracteres de la localizacion absoluta o relativa del archivo.
 * @param mode modo con el que abrir y bloquear: OF_READ o OF_WRITE.
 * @return El descriptor de archivo del archivo abierto y bloqueado.
 */
int open_file(const char* file, int mode){
    int fd;
    // Abrir archivo
    if ((fd = open(file, mode)) < 0) {
        perror("Error en la apertura del archivo\n");
        return EXIT_FAILURE;
    }
    // Bloquear fichero para lectura
    if (bloqueo(fd, mode) == EXIT_FAILURE) {
        perror("No se ha podido establecer el bloqueo.");
        close(fd);
        return EXIT_FAILURE;
    }
    return fd;
}

/**
 * Cierra un archivo despues de desbloquearle.
 * @param fd Descriptor de archivo.
 * @return EXIT_FAILURE o EXIT_SUCCESS segun el resultado de cerrar el archivo.
 */
int close_file(int fd){
    // Liberar bloqueo
    desbloqueo(fd);
    // Cerrar archivo
    return close(fd);
}

/**
 * Lee una línea y la devuelve en el buffer indicado.
 * Si la línea es mayor que el buffer la función devuelve -1.
 * @param fd descriptor del fichero (ya abierto y bloqueado)
 * @param buffer buffer donde escribir
 * @param buffer_size tamaño del buffer
 * @return EXIT_SUCCESS si la línea cabe en el buffer, -1 si no cabe, EXIT_FAILURE si error
 */
int read_line(int fd, char* buffer, size_t buffer_size) {
    ssize_t bytes_read = 0;

    if ((bytes_read = read(fd, buffer, buffer_size-1)) > 0) {
        buffer[bytes_read]='\0';
        for (int i = 0; i < strlen(buffer); i++){
            if(buffer[i] == '\n' || buffer[i] == EOF) {
                buffer[i]='\0';
                return EXIT_SUCCESS;
            }
        }
        return -1; // La línea es mayor que el buffer

    } else {
        return EXIT_FAILURE;
    }
}