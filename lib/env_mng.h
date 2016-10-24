/*
 * ****************************************************************************
 * env_mng.h
 *
 * Libreria que permite usar un archivo para declarar variables en distintos entornos.
 * ****************************************************************************
 */

#ifndef ROSTROJAN_ENV_MNG_H
#define ROSTROJAN_ENV_MNG_H

//INCLUDES
#include "file_mng.h"

//DEFINES
#define N_E_ENV 2
#define ENV_PATH "../entorno.dat"

// PROTOTYPES

/**
 * Muestra el contenido del fichero entorno.dat.
 * Si no existe el fichero, lo crea.
 * Si se le pasa una sección, muestra solo el contenido de esta.
 * Si no existe la sección, la crea.
 * Si se le pasa una sección y una variable, muestra el contenido de esta.
 * @param sec nombre de la sección (o NULL)
 * @param var nombre de la variable (o NULL)
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int ver_entorno(char *sec, char *var);

/**
 * Modifica una variable del entorno o la añade si no existe.
 * Si no existe el archivo de entorno lo crea.
 * La sección tiene que existir.
 * @param sec sección del entorno
 * @param var variable de la sección
 * @param val valor de la variable
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int modificar_entorno(char *sec, char *var, char *val);

#endif