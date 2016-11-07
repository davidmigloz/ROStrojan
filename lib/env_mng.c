/*
 * ****************************************************************************
 * env_mng.c
 *
 * Libreria que permite usar un archivo para declarar variables en distintos entornos.
 * ****************************************************************************
 */
#include "env_mng.h"

// PRIVATE HEADERS
int _print_env();

int _print_sec(char *sec);

int _print_var(char *sec, char *var);

char *_parse_value(char *line);

int _find_env(int fd, char *env);

int _check_field(const char *field);

int _write_line(int fd, char *line);

int _create_var(int fd, char *var, char *val);

int _modify_var(int fd, int line_size, char *var, char *val);

int _modify_line(int fd, int line_size, char *new_line);

int _copy_to_EOF(int fd_src, int fd_des);

void _create_var_line(char *buffer, char *var, char *val);

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
    if ((fd = open_file(ENV_PATH, OF_CREAT | OF_READ)) == EXIT_FAILURE) { return EXIT_FAILURE; }
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
        _print_entry(buffer, _check_field(buffer) ? 2 : 1);
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
    if ((fd = open_file(ENV_PATH, OF_APPEND | OF_CREAT | OF_RDWR)) == EXIT_FAILURE) { return EXIT_FAILURE; }
    char buffer[BUFFER_SIZE];
    int ok;
    // Buscar sección
    switch (_find_env(fd, sec)) {
        case EXIT_FAILURE:
            close_file(fd);
            return EXIT_FAILURE;
        case N_E_ENV:
            // Crear entorno si no existe
            _write_line(fd, sec);
            _write_line(fd, "\n");
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
                if (_check_field(buffer)) {
                    _print_entry(buffer, 2);
                } else {
                    break;
                }
            } while (ok != END_OF_FILE);
            break;
        default:
            close_file(fd);
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
    char* val = get_var_value(sec, var);
    if(strlen(val) == 0) {
        return EXIT_FAILURE;
    }
    printf("%3s %s>%s\n", "└", var, val);
    return EXIT_SUCCESS;
}

/**
 * Busca una variable de una sección y devuelve un string con su valor.
 * Si no existe el fichero entorno.dat, lo crea.
 * @return string con el valor o string vacio si no existe.
 */
char *get_var_value(char *sec, char *var) {
    int fd;
    // Abre el archivo
    if ((fd = open_file(ENV_PATH, OF_CREAT | OF_READ)) == EXIT_FAILURE) { return ""; }
    char *buffer = malloc(BUFFER_SIZE);
    int ok;
    // Buscar sección
    switch (_find_env(fd, sec)) {
        case EXIT_FAILURE:
        case N_E_ENV:
            close_file(fd);
            free(buffer);
            return "";
        case EXIT_SUCCESS:
            // Si existe, iterar sobre las variables
            do {
                if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
                    close_file(fd);
                    free(buffer);
                    return "";
                }
                if (_check_field(buffer)) {
                    // Comprobar si es la variable buscada
                    if (strncmp(var, buffer, strlen(var)) == 0) {
                        // Si es, termina
                        break;
                    }
                } else {
                    free(buffer);
                    return ""; // No existe
                }
            } while (ok != END_OF_FILE);
            break;
        default:
            close_file(fd);
            free(buffer);
            return "";
    }
    // Parsear linea
    char *val = _parse_value(buffer);
    // Cerrar archivo
    close_file(fd);
    free(buffer);
    return val;
}

/**
 * Obtiene el valor de una variable de una línea del fichero de entorno.
 * @param line línea del fichero de entorno.
 * @return string con el valor.
 */
char *_parse_value(char *line) {
    char *tmp = malloc(BUFFER_SIZE);
    strcpy(tmp, line);
    // Obtener el valor de la variable
    char *value = strtok(tmp, ">");
    value = strtok(NULL, ">");
    return value;
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
int _check_field(const char *field) {
    char tmp[strlen(field) + 1];
    strcpy(tmp, field);
    strtok(tmp, ">");
    return strtok(NULL, ">") != NULL;
}

/**
 * Escribe una línea en un archivo.
 * Añade \n al final de la línea.
 * @param fd descriptor del archivo (abierto y bloqueado para escritura)
 * @param line cadena de caracteres a escribir (acabada en \o)
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int _write_line(int fd, char *line) {
    ssize_t ok;
    write(fd, line, strlen(line));
    ok = write(fd, "\n", sizeof(char));
    return ok > 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

/**
 * Modifica una variable del entorno o la añade si no existe.
 * Si no existe el archivo de entorno lo crea.
 * La sección tiene que existir.
 * @param sec sección del entorno
 * @param var variable de la sección
 * @param val valor de la variable
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int modificar_entorno(char *sec, char *var, char *val) {
    int fd, ok;
    char buffer[BUFFER_SIZE];
    // Abir archivos
    if ((fd = open_file(ENV_PATH, OF_CREAT | OF_RDWR)) == EXIT_FAILURE) { return EXIT_FAILURE; }
    // Buscar sección
    switch (_find_env(fd, sec)) {
        case N_E_ENV:
            perror("ERROR: No existe la sección.");
        case EXIT_FAILURE:
            close_file(fd);
            return EXIT_FAILURE;
        case EXIT_SUCCESS:
            // Si existe, iterar sobre las variables
            do {
                if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
                    close_file(fd);
                    return EXIT_FAILURE;
                }
                if (_check_field(buffer)) {
                    // Comprobar si es la variable buscada
                    char tmp[strlen(var) + 2];
                    strcpy(tmp, var);
                    strcat(tmp, ">");
                    if (strstr(buffer, tmp) != NULL) {
                        // Si existe la variable -> modificar valor
                        // Retroceder descriptor al inicio de la variable
                        int line_length = (int) (strlen(buffer) + 1);
                        lseek(fd, -(line_length), SEEK_CUR);
                        _modify_var(fd, line_length, var, val);
                        break;
                    } else if (ok == END_OF_FILE) {
                        // Si no existe la variable (se acaba el archivo) -> crearla
                        _create_var(fd, var, val);
                    }
                } else {
                    // Si no existe la variable (se pasa de sección) -> crearla
                    // Retroceder descruptor al final de la sección
                    lseek(fd, -(strlen(buffer) + 1), SEEK_CUR);
                    _create_var(fd, var, val);
                    break;
                }
            } while (ok != END_OF_FILE);
            break;
        default:
            close_file(fd);
            return EXIT_FAILURE;
    }
    // Cerrar archivo
    close_file(fd);
    return EXIT_SUCCESS;
}

/**
 * Crea la variable en la sección indicada con el valor pasado.
 * @param fd descriptor del archivo de entorno posicionado donde va la variable
 * @param var variable a crear
 * @param val valor de la variable
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int _create_var(int fd, char *var, char *val) {
    // Nueva línea de la variable
    char var_line[strlen(var) + strlen(val) + 2];
    _create_var_line(var_line, var, val);
    // Crear variable
    return _modify_line(fd, 0, var_line);;
}

/**
 * Modifica la variable de la sección indicada con el valor pasado.
 * @param fd descriptor del archivo de entorno posicionado donde va la variable
 * @param var variable a modificar
 * @param val valor de la variable
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int _modify_var(int fd, int line_size, char *var, char *val) {
    // Nueva línea de la variable
    char var_line[strlen(var) + strlen(val) + 2];
    _create_var_line(var_line, var, val);
    // Modificar variable
    return _modify_line(fd, line_size, var_line);;
}

/**
 * Modifica una línea de una archivo sustituyéndola por new_line.
 * Si line_size=0, la línea se añade como una nueva línea.
 * La modificación se realiza en la posición indicada por fd.
 * @param fd descriptor del archivo
 * @param line_size tamaño de la línea existente a modificar (0 si nueva línea)
 * @param new_line contenido de la nueva línea
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int _modify_line(int fd, int line_size, char *new_line) {
    // Guardar posición inicial
    off_t initial_pos = lseek(fd, 0, SEEK_CUR);
    // Copiar archivo desde el final de la linea a modificar hasta el EOF en un archivo temporal
    int fd_tmp;
    if ((fd_tmp = open_file("tmp", OF_CREAT | OF_RDWR)) == EXIT_FAILURE) { return EXIT_FAILURE; }
    lseek(fd, line_size, SEEK_CUR);
    if (_copy_to_EOF(fd, fd_tmp) == EXIT_FAILURE) {
        close(fd_tmp);
        return EXIT_FAILURE;
    }
    // Añadir línea modificada
    lseek(fd, initial_pos, SEEK_SET);
    if (_write_line(fd, new_line) == EXIT_FAILURE) {
        close(fd_tmp);
        return EXIT_FAILURE;
    }
    // Copiar el contenido del archivo temporal a continuación
    lseek(fd_tmp, 0, SEEK_SET);
    if (_copy_to_EOF(fd_tmp, fd) == EXIT_FAILURE) {
        close(fd_tmp);
        return EXIT_FAILURE;
    }
    // Eliminar archivo temporal
    close(fd_tmp);
    unlink("tmp");
    return EXIT_SUCCESS;
}

/**
 * Copiar un archivo a otro desde la posición apuntada por fd_src hasta EOF.
 * @param fd_src descriptor del archivo origen apuntando a la posición desde la que copiar
 * @param fd_des descriptor del archivo destino apuntando a la posición a la que se desea copiar
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int _copy_to_EOF(int fd_src, int fd_des) {
    char buffer[BUFFER_SIZE];
    int ok;
    do {
        if ((ok = read_line(fd_src, buffer, BUFFER_SIZE)) == EXIT_FAILURE) { return EXIT_FAILURE; }
        if (ok != EOF) {
            _write_line(fd_des, buffer);
        }
    } while (ok != END_OF_FILE);
    return EXIT_SUCCESS;
}

/**
 * Concatena la variable y su valor con el formato del archivo de entorno.
 * @param buffer donde escribir el resultado
 * @param var variable
 * @param val valor
 */
void _create_var_line(char *buffer, char *var, char *val) {
    strcpy(buffer, var);
    strcat(buffer, ">");
    strcat(buffer, val);
}
