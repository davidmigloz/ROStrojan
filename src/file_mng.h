/* file_mnh.h
 *
 * Librería que contiene funciones para la gestión de archivos y directorios.
 */

#ifndef ROSTROJAN_FILE_MNG_H
#define ROSTROJAN_FILE_MNG_H

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
 *
 *
 */

int bloqueo(int fd, char rw){
    struct flock lock;
    off_t file_lenght;

    file_lenght = lseek(fd, 0, SEEK_END);
    lseek(fd, 0 , SEEK_SET);

    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = file_lenght;
    if (rw == 'r'){
        lock.l_type = F_RDLCK;
    }else{
        if (rw== 'w') {
            lock.l_type = F_WRLCK;
        }else{
            perror("Segundo parametro incorrecto.");
            return EXIT_FAILURE;
        }
    }
    if(!fcntl(fd,F_SETLKW, &lock)){
        return EXIT_SUCCESS;
    }
    perror("No se ha podido establecer el bloqueo; ¿estaba establecido anteriormente?");
    return EXIT_FAILURE;
}



int desbloqueo(int fd){
    
}
