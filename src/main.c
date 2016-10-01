#include <stdio.h>
#include "file_mng.h"

void test_ver_directorio() ;

int main(int argc, char **argv) {
    int fd = open("/home/jack/Projects/ROStrojan/src/algo",O_WRONLY);
    if (fd<0)
        exit(EXIT_FAILURE);
    int i = bloqueo(fd, 'w');
    bloqueo(fd, 'r');
    if(i==EXIT_SUCCESS)
        desbloqueo(fd);
    close(fd);
    return 0;
}

