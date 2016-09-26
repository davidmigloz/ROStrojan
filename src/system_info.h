//
// Created by Jazriel on 20/09/16.
//

#ifndef ROSTROJAN_SYSTEM_INFO_H
#define ROSTROJAN_SYSTEM_INFO_H
#endif //ROSTROJAN_SYSTEM_INFO_H

#define H_N_LENGTH 20

#include <unistd.h>  //To include some functionalities specified in POSIX
#include <stdlib.h>
#include <pwd.h>
#include <string.h>

int ver_usuarioActual(char* username, int length);
int ver_equipo(char* hostname, int length);

/**
 * ver_usuarioActual: function that returns a pointer to a string containing the user name of the caller.
 * @return pointer to a string
 */
int ver_usuarioActual(char* username, int length) {
    struct passwd *pwd;
    int len;
    pwd = getpwuid(getuid());
    len = sizeof(pwd->pw_name);
    if(len>length){exit(1);}
    memcpy(username, pwd->pw_name, length);
    return 0;
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
