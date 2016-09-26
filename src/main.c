#include <stdio.h>
#include "file_mng.h"

void test_ver_directorio() ;

int main(int argc, char **argv) {
    test_ver_directorio();

    return 0;
}

void test_ver_directorio() {
    puts("----------------------------------");
    puts("| Test_buscar_archivo()          |");
    puts("----------------------------------");

    buscar_archivo("/home/jack/Projects", "main.c");
}