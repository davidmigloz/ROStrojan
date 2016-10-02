/*
 * ****************************************************************************
 * file_mnh.h
 *
 * Librería que contiene funciones para la gestión de archivos y directorios.
 * ****************************************************************************
 */

#ifndef ROSTROJAN_FILE_MNG_H
#define ROSTROJAN_FILE_MNG_H

// INCLUDES

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

// CONSTANTS

#define BUFFER_SIZE 1024

// PROTOTYPES

/**
 * Muestra el contenido del directorio especificado recursivamente.
 * Ej: ver_directorio(".");
 *
 * @param dirPath Puntero al nombre de la ruta (absoluta o relativa)
 * @return EXIT_SUCCESS si ok, EXIT_FAILURE si error
 */
int ver_directorio(const char *dirPath);

/**
 * Muestra la ruta hasta el archivo buscado.
 * Ej: buscar_archivo(".", "README.md");
 *
 * @param currDir Puntero al nombre de la ruta (absoluta o relativa)
 * @param fileName Nombre del archivo con extension incluida
 * @return EXIT_SUCCESS si ok, EXIT_FAILURE si error
 */
int buscar_archivo(const char *currDir, const char *fileName);

/**
 * Bloquea el archivo pasado como fd y según lo que ponga en rw lo bloquea como lectura o escritura
 * @param fd archivo
 * @param rw 'r' o 'w' segun sea lectura o escritura
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int bloqueo(int fd, char rw);

/**
 * Desbloquea el archivo bloqueado por este mismo programa
 * @param fd archivo
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int desbloqueo(int fd);

/**
 * Imprime por pantalla el archivo pasado.
 * @param file puntero a la ruta, absoluta o relativa.
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int ver_archivo(const char *file);

#endif