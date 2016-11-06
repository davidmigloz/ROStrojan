/*
 * ****************************************************************************
 * sig_mng.h
 *
 * Libreria para controlar señales.
 * ****************************************************************************
 */

#ifndef SERVER_SIG_MNG_H
#define SERVER_SIG_MNG_H
//INCLUDES
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


//PROTOTYPES
int received_end();
int bloq_signals(sigset_t* sigset);
int unbloq_signals(sigset_t* sigset);
int kill_pid(int pid);

#endif //SERVER_SIG_MNG_H
