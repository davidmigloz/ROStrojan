/*
 * ****************************************************************************
 * shm_mng.h
 *
 * Libreria para controlar señales.
 * ****************************************************************************
 */

#include "sig_mng.h"



int received_end(){
    //set de señales que recibimos
    sigset_t* received_signals;
    sigpending(received_signals);
    return sigismember (received_signals, SIGUSR1);
}


int bloq_signals(sigset_t* sigset) {
    // bloqueamos todas las señales de sigset
    if ((sigprocmask(SIG_BLOCK, sigset, NULL) == -1)) {
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}


int unbloq_signals(sigset_t* sigset) {
    // desbloqueamos todas las señales
    if ((sigprocmask (SIG_UNBLOCK, sigset, NULL)==-1)){
        perror("LIST: sigprocmask error\n");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int kill_pid(int pid){
    if ((kill(pid, SIGUSR1))==-1){
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}



