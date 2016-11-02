#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>

#include "shm_mng.h"

int main() {
    device devices[N_OF_DEVICES];
    char *shm_address;

    shm_address = init_shm();

    set_n_of_devices(shm_address, 10);

    int i = get_n_of_devices(shm_address);

    printf("%d", i);

    tear_shm(shm_address);

    /*

    //Start fork
    int pid;
    int son_exit;
    int parent_exit;

    switch(pid = fork()) {
        case -1:
            perror("fork error\n");
            break;
        case 0:
            son_exit = son_proccess();
            exit(son_exit);
        default:
            parent_exit = parent_proccess();
            break;
    }
    //End fork
    */
    return 0;
}


int son_proccess() {
    /*Son does stuff*/

    /*Añadir cosas falsas*/
    return EXIT_SUCCESS;
    /*Son stops doing stuff*/
}


int parent_proccess() {
    /*Parent does stuff*/
    while (1) {
        /*Menu hasta que haya que cerrar*/


        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
    /*Parent stops doing stuff*/
}

