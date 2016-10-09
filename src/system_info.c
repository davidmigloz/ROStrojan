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




int ver_usuario(char *uid, char* buffer[3]){
    int fd;
    //Abre archivo
    if((fd = open_file("/etc/passwd", OF_READ))==EXIT_FAILURE){
        return EXIT_FAILURE;
    }
    int field;
    char line[BUFFER_SIZE];
    int ok;
    char *token;
    char* fields[7];
    //malloc para los campos del usuario
    for(int i=0;i<7;i++)
        fields[i] = malloc(BUFFER_SIZE*sizeof(char));
    //leo la primera linea
    ok = read_line(fd, line, BUFFER_SIZE);
    while(ok == EXIT_SUCCESS) {
        //la separo por :
        token = strtok(line, ":");
        //cuento cuantos campos he leido en field
        field=0;
        while (token != NULL) {
            //guardo los campos leidos
            fields[field]=token;
            field++;
            //leo el siguiente campo
            token = strtok(NULL, ":");
        }
        //Si el uid es igual al que me han pasado devuelve los campos interesantes terminados en '\0'
        if(strcmp(fields[2],uid)==0) {
            buffer[0] = fields[0];
            *(buffer[0] + strlen(buffer[0])) = '\0';
            buffer[1] = fields[2];
            *(buffer[1] + strlen(buffer[1])) = '\0';
            buffer[2] = fields[5];
            *(buffer[2] + strlen(buffer[2])) = '\0';
            return EXIT_SUCCESS;
        //si no es comprueba que no nos estan pidiendo imprimir todos
        }else if(strcmp(uid, "-1")==0){
            printf("Usuario: %s\t\tGrupo: %s\t\tDirectorio: %s", fields[0], fields[2], fields[5]);
        }
        //lee la siguiente linea
        ok = read_line(fd, line, BUFFER_SIZE);
    }
    return -1;
}