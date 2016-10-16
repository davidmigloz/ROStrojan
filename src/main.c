#include "file_mng.h"
#include "env_mng.h"
#include "system_info.h"

#define N_ARGS_DEF 2


int menu(int argc, char **argv);


int main(int argc, char **argv) {
    //run_tests();
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
        case 's':
            if (argv[2] != NULL)
                ret = buscar_archivo(getcwd(path, PATH_MAX), argv[2]);
            break;
        case 'd':
            if (argv[2] != NULL)
                ver_directorio(argv[2]);
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
                    if (argv[2] != NULL)
                        ret = ver_entorno(argv[2], NULL);
                    break;
                case N_ARGS_DEF + 2:
                    if (argv[2] != NULL && argv[3] != NULL)
                        ret = ver_entorno(argv[2], argv[3]);
                    break;
                case N_ARGS_DEF + 3:
                    if (argv[2] != NULL && argv[3] != NULL && argv[4] != NULL)
                        ret = modificar_entorno(argv[2], argv[3], argv[4]);
                    break;
                default:
                    ret = EXIT_FAILURE;
            }
            break;
        case 'u':
            if (argc == N_ARGS_DEF)
                ver_usuario(NULL);
            else if (argc == N_ARGS_DEF + 1 && argv[2] != NULL)
                ver_usuario(argv[2]);
            break;
        case 'g':
            if (argc == N_ARGS_DEF)
                ver_grupo(NULL);
            else if (argc == N_ARGS_DEF + 1 && argv[2] != NULL)
                ver_grupo(argv[2]);
            break;
        case 'U':
            printf("Usuario actual:\t%s\n", ver_usuario_actual());
            break;
        case 'h':
            printf("Nombre del equipo:\t%s\n", ver_equipo());
            break;
        case 'S':
            printf("Sistema operativo:\t%s\n", ver_sistema());
            break;
        case 'k':
            printf("Kernel:\t%s\n", ver_kernel());
            break;
        case 'n':
            printf("Ip:\t%s\n", ver_ip());
            break;
        default:
            //TODO: help();
            return EXIT_FAILURE;
    }
    return ret;
}