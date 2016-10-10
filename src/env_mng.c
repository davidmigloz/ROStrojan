/*
 * ****************************************************************************
 * env_mng.c
 *
 * Libreria que permite usar un archivo para declarar variables en distintos entornos.
 * ****************************************************************************
 */
#include "env_mng.h"


/**
 * Muestra todas las variables de entorno creadas en el entotno en el que estan.
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int mostrar_entornos() {
    int fd;
    //Abre el archivo
    if ((fd = open_file("../entorno.dat", OF_READ)) == EXIT_FAILURE) { return EXIT_FAILURE; }
    char buffer[BUFFER_SIZE], tmp[BUFFER_SIZE];
    char *check;
    printf("entorno.dat\n");
    int ok;
    do {
        //lee hasta que termine
        if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) { return EXIT_FAILURE; }
        strcpy(tmp, buffer);
        strtok(tmp, ">");
        check = strtok(NULL, ">");
        // si tiene > imprime con 2 indentaciones, si no con una
        if (check != NULL) { _print_entry(buffer, 2); }
        else { _print_entry(buffer, 1); }
    } while (ok != END_OF_FILE);
    return EXIT_SUCCESS;
}


/**
 * Muestra las variables de un entorno a no ser que no exista, en ese caso lo crea.
 * @param entorno puntero a un array de caracteres que representan el entorno
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int creat_entorno(char *entorno) {
    int fd;
    //Abre el archivo
    if ((fd = open_file("../entorno.dat", OF_READ)) == EXIT_FAILURE) { return EXIT_FAILURE; }
    char buffer[BUFFER_SIZE], tmp[BUFFER_SIZE];
    char *check;
    int ok;

    do {
        //lee hasta que encuentre entorno
        if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
            close_file(fd);
            return EXIT_FAILURE;
        }
        if (strcmp(buffer, entorno) == 0) {
            _print_entry(buffer, 1);
            do {
                if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
                    close_file(fd);
                    return EXIT_FAILURE;
                }

                strcpy(tmp, buffer);
                strtok(tmp, ">");
                check = strtok(NULL, ">");
                if (check != NULL) { _print_entry(buffer, 2); }
                else {
                    close_file(fd);
                    return EXIT_SUCCESS;
                }

            } while (ok != END_OF_FILE);
            close_file(fd);
            return EXIT_FAILURE;
        }
    } while (ok != END_OF_FILE);
    close_file(fd);
    return EXIT_FAILURE;
    //TODO: crear el entorno aqui por que no existe
}