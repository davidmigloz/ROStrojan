/* file_mnh.h
 *
 * Librería que contiene funciones para la gestión de archivos y directorios.
 */

#ifndef ROSTROJAN_FILE_MNG_H
#define ROSTROJAN_FILE_MNG_H

void _print_entry(char *name, int depth);

int _iterate_dir(const char *dirPath, int depth);

void _get_new_path(const char *dirPath, char *dirName, char *newDirPath);

#endif //ROSTROJAN_FILE_MNG_H

#include <stdlib.h>
#include <stdio.h>
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
 * Duevuelve el path del directorio pasado.
 * newDirPath = dirPath + "/" + dirName
 */
void _get_new_path(const char *dirPath, char *dirName, char *newDirPath) {
    strcpy(newDirPath, dirPath);
    strcat(newDirPath, "/");
    strcat(newDirPath, dirName);
}