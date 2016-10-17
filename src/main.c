/*
 * ****************************************************************************
 * main.c - ROStrojan
 *
 * @author David Miguel Lozano
 * @author Javier Martínez Riberas
 * @version 1.0 (17/10/2016)
 * ****************************************************************************
 */
#include "file_mng.h"
#include "env_mng.h"
#include "system_info.h"
#include "help.h"

// CONSTANTS
#define N_ARGS_DEF 2

// PRIVATE HEADERS
int menu(int argc, char **argv);

int main(int argc, char **argv) {
    return menu(argc, argv);
}

/**
 * Menu principal de la aplicacion. Recibe los mismos argumentos que el main.
 * @param argc
 * @param argv
 * @return EXIT_SUCCESS o EXIT_FAILURE
 */
int menu(int argc, char **argv) {

    int ret = EXIT_FAILURE;

    char path[PATH_MAX];
    char *f_arg = argv[1];

    if (f_arg[0] != '-') { return EXIT_FAILURE; }

    switch (f_arg[1]) {
        case 'b':
            if (argv[2] != NULL)
                ret = buscar_archivo(getcwd(path, PATH_MAX), argv[2]);
            break;
        case 'd':
            if (argv[2] != NULL)
                ret = ver_directorio(argv[2]);
            break;
        case 'a':
            if (argv[2] != NULL)
                ret = ver_archivo(argv[2]);
            break;
        case 'e':
            switch (argc) {
                case N_ARGS_DEF + 0:
                    ret = ver_entorno(NULL, NULL);
                    break;
                case N_ARGS_DEF + 1:
                    ret = ver_entorno(argv[2], NULL);
                    break;
                case N_ARGS_DEF + 2:
                    ret = ver_entorno(argv[2], argv[3]);
                    break;
                case N_ARGS_DEF + 3:
                    ret = modificar_entorno(argv[2], argv[3], argv[4]);
                    break;
                default:
                    ret = EXIT_FAILURE;
            }
            break;
        case 'u':
            if (argc == N_ARGS_DEF) {
                ret = ver_usuario(NULL);
            } else if (argc == N_ARGS_DEF + 1) {
                ret = ver_usuario(argv[2]);
            }
            break;
        case 'g':
            if (argc == N_ARGS_DEF) {
                ret = ver_grupo(NULL);
            } else if (argc == N_ARGS_DEF + 1) {
                ret = ver_grupo(argv[2]);
            }
            break;
        case 'U':
            printf("Usuario actual:\t%s\n", ver_usuario_actual());
            ret = EXIT_SUCCESS;
            break;
        case 'h':
            printf("Nombre del equipo:\t%s\n", ver_equipo());
            ret = EXIT_SUCCESS;
            break;
        case 's':
            printf("Sistema operativo:\t%s\n", ver_sistema());
            ret = EXIT_SUCCESS;
            break;
        case 'k':
            printf("Kernel:\t%s\n", ver_kernel());
            ret = EXIT_SUCCESS;
            break;
        case 'n':
            printf("Ip:\t%s\n", ver_ip());
            ret = EXIT_SUCCESS;
            break;
        default:
            break;
    }
    if (ret == EXIT_FAILURE) {
        help(f_arg[1]);
    }
    return ret;
}