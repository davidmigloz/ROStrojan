/**
 * ********************************************************************
 * main_process.c
 *
 * Lógica del cliente, su menu y la invocación de su hijo que controla 
 * la red.
 * ********************************************************************
 */
#include "main_process.h"

// PRIVATE HEADERS

int _menu_loop();

void _print_end();

/**
 * Proceso principal.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
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

    // Prepararnos por si el hijo hace n intentos sin éxito
    atexit(_print_end);

    // Ir al menú
    _menu_loop();

    // Cierre ordenado
    kill_pid(sender_pid);
    return EXIT_SUCCESS;
}

/**
 * Menu de la aplicacion que determina cuánto tiempo se ejecuta.
 * @return EXIT_SUCCESS.
 */
int _menu_loop() {
    _Bool running = true;
    int selection = 0;

    while (running) {
        printf("=============================================\n");
        printf("                   M E N Ú                   \n");
        printf("=============================================\n");
        printf("> 0: Cerrar                                  \n");
        printf("_____________________________________________\n");
        printf("Seleccione una opción [1-5]:\n");

        scanf("%d", &selection);
        switch (selection) {
            case 0:
                running = false;
                break;
            default:
                break;
        }
    }
    return EXIT_SUCCESS;
}


/**
 * Dar aviso al usuario del cierre.
 */
void _print_end() {
    printf("Cerrando...\n");
}
