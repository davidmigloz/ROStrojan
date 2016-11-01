/*
 * shm_mng.h
 *
 * Libreria para controlar la memoria compartida y su estructura
 */

#ifndef SERVER_SHM_MNG_H
#define SERVER_SHM_MNG_H


#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>


#define N_OF_DEVICES 25
#define NAMES_MAXLENGHT 50

typedef struct device device;
/*Struct*/
struct device {
    _Bool used;
    int last_conn;
    int id;
    char name[NAMES_MAXLENGHT + 1];
    char user[NAMES_MAXLENGHT + 1];
    char ip[NAMES_MAXLENGHT + 1];
    char kernel[NAMES_MAXLENGHT + 1];
};


char* init_shm();
int get_n_of_devices(char* shm_pos);
device get_n_device(char* shm_pos, int n);
device* get_n_device_address(char* shm_pos, int n);
void set_n_of_devices(char* shm_pos, int n_of_devices);
int tear_shm(char* shm_pos);

#endif //SERVER_SHM_MNG_H
