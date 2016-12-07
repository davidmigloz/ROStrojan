

#include <stdbool.h>
#include "main_process.h"

int _menu_loop();

void _print_end();

int user_exit = 0;

/**
 * Proceso principal.
 * @return
 */
int main_process() {
    // Inicializar hijo
    pid_t sender_pid;
    switch (sender_pid = fork()) {
        case -1:
            perror("MAIN: fork error");
            _exit(EXIT_FAILURE);
        case 0:
            sender_process();
            return EXIT_SUCCESS;
        default:
            break;
    }
    // Prepararnos por si el hijo hace n intentos sin exito
    atexit(_print_end);
    // Ir al menu
    _menu_loop();

    // Cierre ordenado
    kill_pid(sender_pid);
    return EXIT_SUCCESS;
}

/**
 * Menu de la aplicacion que determina cuanto tiempo se ejecuta
 * @return EXIT_SUCCESS
 */
int _menu_loop() {
    _Bool running = true;
    int selection = 0;

    while (running) {
        printf("Menu (elige de las opciones):");
        printf("0 - Salir del programa.");
        scanf("%d", &selection);
        switch (selection) {
            case 0:
                user_exit = 1;
                running = false;
                break;
            default:
                break;
        }
    }
    return EXIT_SUCCESS;
}


/**
 * Dar aviso al usuario de cierre
 */
void _print_end() {
    if (user_exit) {
        printf("Timeout: no se ha podido comunicar con el servidor en demasiado tiempo\n");
    } else {
        printf("Cerrando\n");
    }
}
