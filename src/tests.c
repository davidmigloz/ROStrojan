/*
 * ****************************************************************************
 * tests.c
 *
 * Test suite para testear las librerías.
 * ****************************************************************************
 */

#include "tests.h"

// PRIVATE HEADERS
void test_ver_directorio();

void test_buscar_archivo();

void test_ver_archivo();

char *concatPath(const char *s1, const char *s2);

// GLOBAL VAR
char *testDirPath;

void run_tests() {
    // Config test dir
    testDirPath = concatPath(getenv("PWD"), "ClionProjects/ROStrojan/test");
    // Run tests
    test_ver_directorio();
    test_buscar_archivo();
    test_ver_archivo();
}

void test_ver_directorio() {
    puts("----------------------------------");
    puts("| Test_ver_directorio()          |");
    puts("----------------------------------");

    ver_directorio(testDirPath);
}

void test_buscar_archivo() {
    puts("----------------------------------");
    puts("| Test_buscar_archivo()          |");
    puts("----------------------------------");

    buscar_archivo(testDirPath, "secrets.txt");
}

void test_ver_archivo() {
    puts("----------------------------------");
    puts("| Test_ver_archivo()             |");
    puts("----------------------------------");

    char *filePath = concatPath(testDirPath, "lista-barcenas.txt");

    ver_archivo(filePath);
}

char *concatPath(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 2);
    strcpy(result, s1);
    strcat(result, "/");
    strcat(result, s2);
    return result;
}