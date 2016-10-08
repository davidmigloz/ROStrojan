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
#define OF_READ 00
#define OF_WRITE 01

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
 * @param mode OF_READ o OF_WRITE segun sea lectura o escritura
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int bloqueo(int fd, int mode);

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

/**
 * Abre un archivo y lo bloquea con el modo elegido.
 * Los modos permitidos son OF_READ y OF_WRITE por el momento.
 * Ejemplos de uso: open_file("./Downloads/descarga1.txt", OF_READ);
 *                  open_file("/home/user/mitexto.txt", OF_WRITE);.
 * @param file puntero a la cadena de caracteres de la localizacion absoluta o relativa del archivo.
 * @param mode modo con el que abrir y bloquear: OF_READ o OF_WRITE.
 * @return El descriptor de archivo del archivo abierto y bloqueado.
 */
int open_file(const char* file, int mode);

/**
 * Cierra un archivo despues de desbloquearle.
 * @param fd Descriptor de archivo.
 * @return EXIT_FAILURE o EXIT_SUCCESS segun el resultado de cerrar el archivo.
 */
int close_file(int fd);

/**
 * Lee una línea y la devuelve en el buffer indicado.
 * Si la línea es mayor que el buffer la función devuelve -1.
 * @param fd descriptor del fichero (ya abierto y bloqueado)
 * @param buffer buffer donde escribir
 * @param buffer_size tamaño del buffer
 * @return EXIT_SUCCESS si la línea cabe en el buffer, -1 si no cabe, EXIT_FAILURE si error
 */
int read_line(int fd, char* buffer, size_t buffer_size);

#endif