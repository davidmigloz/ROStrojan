//
// Created by Jazriel on 20/09/16.
//

#ifndef ROSTROJAN_SYSTEM_INFO_H
#define ROSTROJAN_SYSTEM_INFO_H
#endif //ROSTROJAN_SYSTEM_INFO_H

#define H_N_LENGTH 20

#include <unistd.h>  //To include some functionalities specified in POSIX
#include <stdlib.h>


char* ver_usuarioActual();
int ver_equipo(char* hostname, int length);

/**
 * ver_usuarioActual: function that returns a pointer to a string containing the user name of the caller.
 * Do not use this function in segure or critical programs as is easily deceivable.
 * @return pointer to a string
 */
char* ver_usuarioActual() {
    return getlogin();
}

/**
 * ver_equipo: function that returns a pointer to a string containing the name of the host.
 * @return pointer to a string or null in operation failure
 */
int ver_equipo(char* hostname, int length){
    int errcheck = gethostname(hostname, length);
    if(errcheck==0){
        return 0;
    }else{
        exit(1);
    }
}
