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

void test_bloqueo();

void test_ver_archivo();

char *concatPath(const char *s1, const char *s2);

int lsLocks();

// GLOBAL VAR
char *testDirPath;

void run_tests() {
    // Config test dir
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    testDirPath = concatPath(homedir, "ClionProjects/ROStrojan/test");
    // Run tests
    test_ver_directorio();
    test_buscar_archivo();
    test_bloqueo();
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

void test_bloqueo() {
    puts("----------------------------------");
    puts("| Test_bloqueo()                 |");
    puts("----------------------------------");

    char *filePath = concatPath(testDirPath, "lista-barcenas.txt");

    // Abrir archivo
    int fd1 = open(filePath, O_RDONLY);
    // Bloquear fichero para lectura
    bloqueo(fd1, 'r');
    puts("Bloqueado para lectura. Locks:");
    if (lsLocks() == 1) {
        puts("PASS: archivo bloqueado.");
    } else {
        puts("FAIL: archivo no bloqueado.");
    }
    // Desbloquar archivo
    desbloqueo(fd1);
    close(fd1);
    puts("Desbloqueado. Locks:");
    if (lsLocks() == 0) {
        puts("PASS: archivo desbloqueado.");
    } else {
        puts("FAIL: archivo no desbloqueado.");
    }
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

/**
 * Run "lslocks | grep ROStrojan" command.
 */
int lsLocks() {
    FILE *pp;
    int n_locks = 0;
    pp = popen("lslocks", "r");
    if (pp != NULL) {
        while (1) {
            char *line;
            char buf[1000];
            line = fgets(buf, sizeof buf, pp);
            if (line == NULL) break;
            if (strstr(line, "ROStrojan") != NULL) {
                printf("> %s", line);
                n_locks++;
            }
        }
        pclose(pp);
    }
    return n_locks;
}