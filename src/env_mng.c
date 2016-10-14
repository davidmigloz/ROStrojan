/*
 * ****************************************************************************
 * env_mng.c
 *
 * Libreria que permite usar un archivo para declarar variables en distintos entornos.
 * ****************************************************************************
 */
#include "env_mng.h"

int open_env(int mode);

// PRIVATE HEADERS
int _print_env();

int _print_sec(char *sec);

int _print_var(char *sec, char *var);

int _find_env(int fd, char *env);

int check_field(const char *field);

/**
 * Muestra el contenido del fichero entorno.dat.
 * Si no existe el fichero, lo crea.
 * Si se le pasa una sección, muestra solo el contenido de esta.
 * Si no existe la sección, la crea.
 * Si se le pasa una sección y una variable, muestra el contenido de esta.
 * @param sec nombre de la sección (o NULL)
 * @param var nombre de la variable (o NULL)
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int ver_entorno(char *sec, char *var) {
    if (sec == NULL) {
        return _print_env();
    } else {
        if (var == NULL) {
            return _print_sec(sec);
        } else {
            return _print_var(sec, var);
        }

    }
}

/**
 * Muestra tod0 el contenido del fichero entorno.dat.
 * Si no existe el fichero, lo crea.
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int _print_env() {
    int fd;
    // Abre el archivo
    if ((fd = open_file("entorno.dat", OF_CREAT | OF_READ)) == EXIT_FAILURE) { return EXIT_FAILURE; }
    char buffer[BUFFER_SIZE];
    printf("entorno.dat\n");
    int ok;
    // Leer archivo
    do {
        if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
            close_file(fd);
            return EXIT_FAILURE;
        }
        // Si tiene > imprime con 2 indentaciones, si no con una
        _print_entry(buffer, check_field(buffer) ? 2 : 1);
    } while (ok != END_OF_FILE);
    // Cerrar archivo
    close_file(fd);
    return EXIT_SUCCESS;
}


/**
 * Muestra el contenido de las variables de una sección.
 * Si no existe el fichero entorno.dat, lo crea.
 * Si no existe la sección, la crea.
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int _print_sec(char *sec) {
    int fd;
    // Abre el archivo
    if ((fd = open_file("entorno.dat", OF_APPEND | OF_CREAT | OF_RDWR)) == EXIT_FAILURE) { return EXIT_FAILURE; }
    char buffer[BUFFER_SIZE];
    int ok;
    // Buscar sección
    switch (_find_env(fd, sec)) {
        case EXIT_FAILURE:
            close_file(fd);
            return EXIT_FAILURE;
        case N_E_ENV:
            // Crear entorno si no existe
            write(fd, sec, strlen(sec));
            write(fd, "\n", sizeof(char));
            break;
        case EXIT_SUCCESS:
            // Si existe, mostrar su contenido
            // Retroceder puntero hasta inicio de sección
            lseek(fd, -(strlen(sec) + 1), SEEK_CUR); // +1 para el \n
            // Imprimir nombre sección
            read_line(fd, buffer, BUFFER_SIZE);
            _print_entry(buffer, 1);
            // Iterar sobre las variables
            do {
                if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
                    close_file(fd);
                    return EXIT_FAILURE;
                }
                // Imprimir variable o salir
                if (check_field(buffer)) {
                    _print_entry(buffer, 2);
                } else {
                    break;
                }
            } while (ok != END_OF_FILE);
        default:
            return EXIT_FAILURE;
    }
    // Cerrar archivo
    close_file(fd);
    return EXIT_SUCCESS;
}

/**
 * Muestra el contenido de una variable de una sección.
 * Si no existe el fichero entorno.dat, lo crea.
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int _print_var(char *sec, char *var) {
    int fd;
    // Abre el archivo
    if ((fd = open_file("entorno.dat", OF_CREAT | OF_READ)) == EXIT_FAILURE) { return EXIT_FAILURE; }
    char buffer[BUFFER_SIZE];
    int ok;
    // Buscar sección
    switch (_find_env(fd, sec)) {
        case EXIT_FAILURE:
        case N_E_ENV:
            close_file(fd);
            return EXIT_FAILURE;
        case EXIT_SUCCESS:
            // Si existe, iterar sobre las variables
            do {
                if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
                    close_file(fd);
                    return EXIT_FAILURE;
                }
                if (check_field(buffer)) {
                    // Comprobar si es la variable buscada
                    char tmp[BUFFER_SIZE];
                    strcpy(tmp, var);
                    strcat(tmp, ">");
                    if (strstr(buffer, tmp) != NULL) {
                        _print_entry(buffer, 1);
                        break;
                    }
                } else {
                    return EXIT_FAILURE; // No existe
                }
            } while (ok != END_OF_FILE);
        default:
            return EXIT_FAILURE;
    }
    // Cerrar archivo
    close_file(fd);
    return EXIT_SUCCESS;
}

/**
 * Mueve un puntero que apunta a un fichero hasta que este en el entorno elegido.
 * @param fd identificador del fichero.
 * @param env array de caracteres del nombre del entorno elegido.
 * @return EXIT_FAILURE, N_E_ENV (no existe el entorno), o EXIT_SUCCESS.
 */
int _find_env(int fd, char *env) {
    int ok;
    char buffer[BUFFER_SIZE];
    // Lee hasta que encuentre entorno
    do {
        if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) { return EXIT_FAILURE; }
        // Comprueba si es la sección
        if (strcmp(buffer, env) == 0) {
            return EXIT_SUCCESS;
        }
    } while (ok != END_OF_FILE);
    return N_E_ENV;
}

/**
 * Comprueba si una linea del archivo de datos es entorno o una variable.
 * @param field linea pasada.
 * @return 'true' (1) si es variable, 'false' (0) si es entorno.
 */
int check_field(const char *field) {
    char tmp[BUFFER_SIZE];
    strcpy(tmp, field);
    strtok(tmp, ">");
    return strtok(NULL, ">") != NULL;
}

int modificar_entorno(char *sec, char *var, char *val) {
    // TODO
    //
    return 0;
}