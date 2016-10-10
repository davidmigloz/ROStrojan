#include "tests.h"
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
            ret = buscar_archivo(getcwd(path, PATH_MAX), argv[2]);
            break;
        case 'd':
            ret = ver_directorio(argv[2]);
            break;
        case 'a':
            ret = ver_archivo(argv[2]);
            break;
        case 'e':
            switch (argc) {
                case N_ARGS_DEF + 0:
                    ret = mostrar_entornos();
                    break;
                case N_ARGS_DEF + 1:
                    ret = creat_entorno(argv[2]);
                    break;
                case N_ARGS_DEF + 2:

                    break;
                case N_ARGS_DEF + 3:

                    break;
                default:
                    ret = EXIT_FAILURE;
            }
            break;
        case 'u':
            if (argc == N_ARGS_DEF) { ver_usuario(NULL); }
            else if (argc == N_ARGS_DEF + 1) { ver_usuario(argv[2]); }
            break;
        case 'g':
            if (argc == N_ARGS_DEF) { ver_grupo(NULL); }
            else if (argc == N_ARGS_DEF + 1) { ver_grupo(argv[2]); }
            break;
        case 'U':
            printf("Usuario actual:\t%s", ver_usuario_actual());
            break;
        case 'h':
            printf("Nombre del equipo:\t%s", ver_equipo());
            break;
        case 'S':
            printf("Sistema operativo:\t%s", ver_sistema());
            break;
        case 'k':
            printf("Kernel:\t%s", ver_kernel());
            break;
        case 'n':
            printf("Ip:\t%s", ver_ip());
            break;
        default:
            //TODO: help();
            return EXIT_FAILURE;
    }
    return ret;
}