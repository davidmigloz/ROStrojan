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
    if ((fd = open_file("../entorno.dat", OF_READ)) == EXIT_FAILURE) { return EXIT_FAILURE; }
    char buffer[BUFFER_SIZE];
    char tmp[BUFFER_SIZE];
    char *check;
    int ok;
    printf("entorno.dat");//_print_entry()
    while(read_line(fd, buffer, BUFFER_SIZE) == EXIT_SUCCESS) {
        strcpy(tmp, buffer);
        strtok(tmp, ">");
        check = strtok(NULL, ">");
        if (check!=NULL){ _print_entry(buffer, 2); }
        else { _print_entry(buffer, 1); }
    }
    return EXIT_SUCCESS;
}
