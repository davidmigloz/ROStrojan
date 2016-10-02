/* file_mnh.h
 *
 * Librería que contiene funciones para la gestión de archivos y directorios.
 */

#ifndef ROSTROJAN_FILE_MNG_H
#define ROSTROJAN_FILE_MNG_H
#define BUFFER_SIZE 1024

void _print_entry(char *name, int depth);

int _iterate_dir(const char *dirPath, int depth);

void _get_new_path(const char *dirPath, char *dirName, char *newDirPath);

int buscar_archivo(const char *currDir, const char *fileName);

#endif //ROSTROJAN_FILE_MNG_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

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
int buscar_archivo(const char *currDir, const char *fileName){
    //Abrir el directorio
    DIR *dir = opendir(currDir);
    struct dirent *itdir;
    char newDir[PATH_MAX];
    //Si se ha podido
    if(dir){
        //Lee las entradas internas
        while((itdir = readdir(dir))!=NULL){
            //Si son directorios menos . y .. recursividad, si no comprueba si el nombre coincide
            if(itdir->d_type==DT_DIR && strcmp(itdir->d_name, ".") != 0 && strcmp(itdir->d_name, "..") != 0){
                _get_new_path(currDir,itdir->d_name,newDir);
                buscar_archivo(newDir ,fileName);
            } else {
                if(itdir->d_type==DT_REG && strcmp(itdir->d_name, fileName)==0){
                    _get_new_path(currDir,itdir->d_name,newDir);
                    _print_entry(newDir,0);
                }
            }
        }
        {
            closedir(dir);
            return EXIT_SUCCESS;
        }
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
int bloqueo(int fd, char rw){
    //lock y longitud del lock (tod0 el fichero)
    struct flock lock;
    off_t file_lenght;

    //Leemos el fichero hasta el final desde el principio
    lseek(fd, 0 , SEEK_SET);
    file_lenght = lseek(fd, 0, SEEK_END);
    //Pongo el puntero otra vez en la posicion inicial
    lseek(fd, 0 , SEEK_SET);

    //Bloqueamos el fichero desde la posicion inicial hasta la final
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = file_lenght;


    //si nos han pedido lectura
    if (rw == 'r'){
        lock.l_type = F_RDLCK;
    }else{
        //si nos han pedido escritura
        if (rw== 'w') {
            lock.l_type = F_WRLCK;
        //si hay error
        }else{
            perror("Segundo parametro incorrecto.");
            return EXIT_FAILURE;
        }
    }
    //ponemos el lock a tod0 el fichero
    if(fcntl(fd,F_SETLK, &lock)!=-1){
        return EXIT_SUCCESS;
    }
    perror("No se ha podido establecer el bloqueo; ¿estaba establecido anteriormente?");
    return EXIT_FAILURE;
}


/**
 * Desbloquea el archivo bloqueado por este mismo programa
 * @param fd archivo
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int desbloqueo(int fd){
    //lock y longitud del lock (tod0 el fichero)
    struct flock lock;
    off_t file_lenght;

    //Leemos el fichero hasta el final desde el principio
    lseek(fd, 0 , SEEK_SET);
    file_lenght = lseek(fd, 0, SEEK_END);
    //Pongo el puntero otra vez en la posicion inicial
    lseek(fd, 0 , SEEK_SET);

    //Desbloqueamos el fichero desde la posicion inicial hasta la final
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = file_lenght;
    lock.l_type = F_UNLCK;

    //ponemos el lock a tod0 el fichero
    if(fcntl(fd, F_SETLK, &lock)!=-1){
        return EXIT_SUCCESS;
    }
    perror("No se ha podido quitar el bloqueo.");
    return EXIT_FAILURE;
}


/**
 * Imprime por pantalla el archivo pasado.
 * @param file puntero a la ruta, absoluta o relativa.
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int ver_archivo(char *file){
    int fd;
    int bytes_read = 0;
    char buffer[BUFFER_SIZE+1];
    fd = open(file, O_RDONLY);
    if(fd == -1){
        perror("No se ha podido abrir el archivo.");
        return EXIT_FAILURE;
    }
    if(bloqueo(fd, 'r')==EXIT_FAILURE){
        perror("No se ha podido establecer el bloqueo.");
        close(fd);
        return EXIT_FAILURE;
    }
    while((bytes_read = read(fd, buffer, BUFFER_SIZE))>0){
        buffer[bytes_read]='\0';
        printf("%s", buffer);
    }
    if(bytes_read==-1){
        perror("Error en la lectura del archivo.");
        close(fd);
        return EXIT_FAILURE;
    }
    close(fd);
    return EXIT_SUCCESS;
}
