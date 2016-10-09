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
#define LONG_LINE -1
#define END_OF_FILE -2

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
 * Bloquea el archivo pasado como fd y según lo que ponga en rw lo bloquea como lectura o escritura.
 * @param fd archivo
 * @param mode OF_READ o OF_WRITE segun sea lectura o escritura
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int bloqueo(int fd, int mode);

/**
 * Desbloquea el archivo bloqueado por este mismo programa.
 * @param fd archivo
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int desbloqueo(int fd);

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
 * El máximo de bytes que puede leer es (buffer_size-1), el último byte se reserva para \0.
 * Si la línea es mayor la función devuelve LONG_LINE, si llega al final del archivo devuelve END_OF_FILE.
 * Nota: los caracteres no ASCII ocupan 2 bytes.
 * @param fd descriptor del fichero (ya abierto y bloqueado)
 * @param buffer buffer donde escribir
 * @param buffer_size tamaño del buffer
 * @return EXIT_SUCCESS si línea <  buffer_size,
 *         LONG_LINE    si línea >= buffer_size,
 *         END_OF_FILE  si línea <  buffer_size y EOF encontrado,
 *         EXIT_FAILURE si error
 */
int read_line(int fd, char* buffer, size_t buffer_size);

/**
 * Imprime por pantalla el archivo pasado.
 * @param file puntero a la ruta, absoluta o relativa.
 * @return EXIT_FAILURE o EXIT_SUCCESS
 */
int ver_archivo(const char *file);

#endif