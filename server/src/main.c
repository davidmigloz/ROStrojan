#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/sem.h>
#include <unistd.h>
#include "shm_mng.h"

int main() {
    device devices[N_OF_DEVICES];
    char* shm_address;

    shm_address = init_shm();

    set_n_of_devices(shm_address, 10);

    int i = get_n_of_devices(shm_address);

    printf("%d", i);

    tear_shm(shm_address);
    /*
    //Init semaphore
    key_t sem_key;
    int sem_id;
    struct sembuf sem;

    if ((sem_key = ftok( "/tmp/rostrojan", 's'))==(key_t)-1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    if ((sem_id = semget(sem_key, 1,IPC_CREAT | IPC_EXCL ))==-1){
        perror("semget error\n");
        exit(EXIT_FAILURE);
    }
    else{
        sem.sem_num = 0;
        sem.sem_op = 1;
        sem.sem_flg = 0;
        if (semop(sem_id, &sem, 1) == -1) {
            perror("semop error\n");
            exit(EXIT_FAILURE);
        }
    }
    //End semaphore init
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


int son_proccess(){
    /*Son does stuff*/

    /*Añadir cosas falsas*/
    return EXIT_SUCCESS;
    /*Son stops doing stuff*/
}



int parent_proccess(){
    /*Parent does stuff*/
    while(1){
        /*Menu hasta que haya que cerrar*/


        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
    /*Parent stops doing stuff*/
}

