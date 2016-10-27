/*
 * ****************************************************************************
 * help.h
 *
 * Libreria que permite imprimir la información necesaria para usar ROStrojan
 * por linea de comandos.
 * ****************************************************************************
 */
#include "help.h"


void _buscar_archivo_help();
void _ver_directorio_help();
void _ver_archivo_help();
void _v_m_entorno_help();
void _ver_usuario_help();
void _ver_grupo_help();
void _ver_usuario_actual_help();
void _ver_equipo_help();
void _ver_sistema_help();
void _ver_kernel_help();
void _ver_ip_help();
void _all_helps();


void help(char mode){
    printf("Usage: ROStrojan:\n");
    switch (mode) {
        case 's':
            _buscar_archivo_help();
            break;
        case 'd':
            _ver_directorio_help();
            break;
        case 'a':
            _ver_archivo_help();
            break;
        case 'e':
            _v_m_entorno_help();
            break;
        case 'u':
            _ver_usuario_help();
            break;
        case 'g':
            _ver_grupo_help();
            break;
        case 'U':
            _ver_usuario_actual_help();
            break;
        case 'h':
            _ver_equipo_help();
            break;
        case 'S':
            _ver_sistema_help();
            break;
        case 'k':
            _ver_kernel_help();
            break;
        case 'n':
            _ver_ip_help();
            break;
        default:
            _all_helps();
    }
}


void _buscar_archivo_help(){
    printf(//Strings should start at column 14 at should end at column 94 (excluding \x characters)
            "  -s [FILE]        Busqueda recursiva del archivo especificado en FILE desde el\n"
            "                     directorio de trabajo actual.\n"
    );
}

void _ver_directorio_help(){
    printf(
            "  -d [DIR]         Muestra el contenido del directorio especificado en DIR\n"
            "                     recursivamente.\n"
    );
}

void _ver_archivo_help() {
    printf(
            "  -a [DIR]        Imprime por pantalla el archivo pasado en DIR. La ruta puede\n"
            "                    ser relativa o absolura.\n"
    );
}

void _v_m_entorno_help(){
    printf(
            "  -e              Imprime todos las secciones y todas las variables.\n"
            "      | [SECCION] Imprime la seccion y sus variables a no ser que la seccion no\n"
            "                    exista, entonces la creará.\n"
            "      | [SECCION][VAR]\n"
            "                  Imprime la variable elegida de la seccion elegida.\n"
            "      | [SECCION][VAR][VALOR]\n"
            "                  Modifica la variable, del entorno elegido, a tener el valor\n"
            "                    elegido. Si no existe, entoces la creará.\n"
    );
}

void _ver_usuario_help(){
    printf(
            "  -u              Imprime todos los uids, grupos principales y directorios home\n"
            "                    de los usuarios del sistema.\n"
    );
}

void _ver_grupo_help(){
    printf(
            "  -g              Imprime el nombre, gid y miembros de todos los grupos del\n"
            "                    sistema.\n"
    );
}

void _ver_usuario_actual_help(){
    printf(
            "  -U              Imprime el uid, grupo principal y directorio home del usuario\n"
            "                    actual.\n"
    );
}

void _ver_equipo_help(){
    printf(
            "  -h              Imprime el nombre del equipo.\n"
    );
}

void _ver_sistema_help(){
    printf(
            "  -S              Imprime el sistema operativo.\n"
    );
}

void _ver_kernel_help(){
    printf(
            "  -k              Imprime el kernel y su version.\n"
    );
}

void _ver_ip_help(){
    printf(
            "  -n              Imprime la(s) IP(s) del equipo.\n"
    );
}

void _all_helps(){
    _buscar_archivo_help();
    _ver_directorio_help();
    _ver_archivo_help();
    _v_m_entorno_help();
    _ver_usuario_help();
    _ver_grupo_help();
    _ver_usuario_actual_help();
    _ver_equipo_help();
    _ver_sistema_help();
    _ver_kernel_help();
    _ver_ip_help();
}