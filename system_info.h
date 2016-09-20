//
// Created by Jazriel on 20/09/16.
//

#ifndef ROSTROJAN_SYSTEM_INFO_H
#define ROSTROJAN_SYSTEM_INFO_H
#endif //ROSTROJAN_SYSTEM_INFO_H

#include <unistd.h>


char* ver_usuarioActual();



/**
 * ver_usuarioActual; function that returns a pointer to a string containing the user name of the caller.
 * Do not use this function in segure or critical programs as is easily deceivable.
 * @return pointer to a string
 */
char* ver_usuarioActual() {
    return getlogin();
}
