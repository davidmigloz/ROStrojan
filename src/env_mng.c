/*
 * ****************************************************************************
 * env_mng.c
 *
 * Libreria que permite usar un archivo para declarar variables en distintos entornos.
 * ****************************************************************************
 */
#include "env_mng.h"

int open_env(int mode);

int point_to_env(int fd, char *env);
int check_field(const char *field);

/**
 * Muestra todas las variables de entorno creadas en el entotno en el que estan.
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int mostrar_entornos() {
    int fd;
    //Abre el archivo
    if ((fd = open_file("../entorno.dat", OF_READ)) == EXIT_FAILURE) { return EXIT_FAILURE; }
    char buffer[BUFFER_SIZE];
    printf("entorno.dat\n");
    int ok;
    do {
        //lee hasta que termine
        if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) { return EXIT_FAILURE;}
        // si tiene > imprime con 2 indentaciones, si no con una
        if (check_field(buffer)) { _print_entry(buffer, 2); }
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
    if ((fd = open_env( OF_READ)) == EXIT_FAILURE) { return EXIT_FAILURE; }
    char buffer[BUFFER_SIZE];
    int ok;
    //encuentra el entorno
    int env = point_to_env(fd, entorno);
    //si no se puede
    if(env == EXIT_FAILURE){
        close_file(fd);
        return EXIT_FAILURE;
        //si no existe el entorno crealo
    }else if(env==N_E_ENV){
        close_file(fd);
        if ((fd = open_env(OF_WRITE)) == EXIT_FAILURE) { return EXIT_FAILURE; }
        lseek(fd, 0, SEEK_END);
        write(fd, entorno, strlen(entorno));
        write(fd, "\n", sizeof(char));
        close_file(fd);
        return EXIT_SUCCESS;
    }
    //The +1 is because '\0', strings in C :/
    lseek(fd, -(strlen(entorno)+1), SEEK_CUR);
    //sin comprobaciones porque hemos retrocedido linea
    read_line(fd, buffer, BUFFER_SIZE);
    _print_entry(buffer, 1);
    do {
        //lee linea a linea
        if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
        //si es variable imprimela
        if (check_field(buffer)) { _print_entry(buffer, 2); }
        else {
            //si se ha acabado el entorno termina
            return EXIT_SUCCESS;
        }
    } while (ok != END_OF_FILE);
    //Shouldnt get to here
    return EXIT_FAILURE;
}


/**
 * Visualiza la variable elegida del entorno elegido.
 * @param entorno puntero a un array de characteres.
 * @param variable puntero a un array de caracteres.
 * @return resultado de la ejevucion.
 */
int ver_variable(char *entorno, char *variable){
    int fd;
    //Abre el archivo
    if ((fd = open_env(OF_READ)) == EXIT_FAILURE) { return EXIT_FAILURE; }
    char buffer[BUFFER_SIZE];
    int ok;
    //Busca el entorno
    int env = point_to_env(fd, entorno);
    if(env == EXIT_FAILURE || env == N_E_ENV){ return EXIT_FAILURE; }
    do {
        //lee a partir del entorno linea a linea
        if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
        //mira a ver si la linea es variable.
        if (check_field(buffer)) {
            //si lo es mira a ver si es la que queremos.
            if(strcmp(variable, buffer)){
                _print_entry(buffer, 1);
                return EXIT_SUCCESS;
            }
        }
        else {
            //si se ha acabado el entorno falla
            return EXIT_FAILURE;
        }

    } while (ok != END_OF_FILE);
    //Shouldn't be here!
    return EXIT_FAILURE;
}


int cambiar_variable(char *entorno, char *variable, char *valor){

}


/**
 * Abre el archivo de entorno, lo crea si no existe.
 * @param mode modo en el que abrir el archivo.
 * @return el identificador del archivo o fallo si no se ha podido ni abrir ni crear.
 */
int open_env(int mode){
    int fd;
    if ((fd = open_file("../entorno.dat", mode)) == EXIT_FAILURE) {
        //TODO: crear el archivo si no existe en vez de devolver fallo
        return EXIT_FAILURE;
    }
    return fd;
}


/**
 * Mueve un puntero que apunta a un fichero hasta que este en el entorno elegido.
 * @param fd identificador del fichero.
 * @param env array de caracteres del nombre del entorno elegido.
 * @return EXIT_FAILURE, N_E_ENV (no existe el entorno), o EXIT_SUCCESS.
 */
int point_to_env(int fd, char *env){
    int ok;
    char buffer[BUFFER_SIZE];

    do {
        //lee hasta que encuentre entorno
        if ((ok = read_line(fd, buffer, BUFFER_SIZE)) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
        //Comprueba que sea el correcto.
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
int check_field(const char *field){
    char tmp[BUFFER_SIZE];
    strcpy(tmp, field);
    strtok(tmp, ">");
    return strtok(NULL, ">")!=NULL;
}
