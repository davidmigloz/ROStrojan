#include <stdio.h>
#include "file_mng.h"
#include "system_info.h"

void test_ver_directorio() ;

int main(int argc, char **argv) {
    int k = ver_kernel();
    int j = ver_sistema();
    int i = ver_equipo();
    return 0;
}

