#include <stdio.h>
#include "file_mng.h"

void test_ver_directorio() ;

int main(int argc, char **argv) {
    test_ver_directorio();

    return 0;
}

void test_ver_directorio() {
    puts("----------------------------------");
    puts("| Test_ver_directorio()          |");
    puts("----------------------------------");

    ver_directorio(".");
}