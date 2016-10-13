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

// PROTOTYPES
/**
 * Muestra todas las variables de entorno creadas en el entotno en el que estan.
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int mostrar_entornos();

int ver_variable(char *entorno, char *variable);


int creat_entorno(char *entorno);


#endif //ROSTROJAN_ENV_MNG_H
