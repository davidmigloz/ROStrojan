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

void test_ver_usuario_actual();

void test_ver_equipo();

void test_ver_sistema();

void test_ver_kernel();

void test_ver_ip();

char *concat_path(const char *s1, const char *s2);

int ls_locks();

// GLOBAL VAR
char *testDirPath;

void run_tests() {
    // Config test dir
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    testDirPath = concat_path(homedir, "ClionProjects/ROStrojan/test");
    // Test: file_mnh.h
//    test_ver_directorio();
//    test_buscar_archivo();
//    test_bloqueo();
//    test_ver_archivo();
    // Test
    test_ver_usuario_actual();
    test_ver_equipo();
    test_ver_sistema();
    test_ver_kernel();
    test_ver_ip();
}


/////////////////////////
// file_mnh.h tests
/////////////////////////

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

    char *filePath = concat_path(testDirPath, "lista-barcenas.txt");

    // Abrir archivo
    int fd1 = open(filePath, O_RDONLY);
    // Bloquear fichero para lectura
    bloqueo(fd1, 'r');
    puts("Bloqueado para lectura. Locks:");
    if (ls_locks() == 1) {
        puts("PASS: archivo bloqueado.");
    } else {
        puts("FAIL: archivo no bloqueado.");
    }
    // Desbloquar archivo
    desbloqueo(fd1);
    close(fd1);
    puts("Desbloqueado. Locks:");
    if (ls_locks() == 0) {
        puts("PASS: archivo desbloqueado.");
    } else {
        puts("FAIL: archivo no desbloqueado.");
    }
}

void test_ver_archivo() {
    puts("----------------------------------");
    puts("| Test_ver_archivo()             |");
    puts("----------------------------------");

    char *filePath = concat_path(testDirPath, "lista-barcenas.txt");

    ver_archivo(filePath);
}

/////////////////////////
// system_info.h tests
/////////////////////////

void test_ver_usuario_actual() {
    puts("----------------------------------");
    puts("| Test_ver_usuario_actual()      |");
    puts("----------------------------------");

    puts(ver_usuario_actual());
}

void test_ver_equipo() {
    puts("----------------------------------");
    puts("| Test_ver_equipo()              |");
    puts("----------------------------------");

    ver_equipo();
}

void test_ver_sistema() {
    puts("----------------------------------");
    puts("| Test_ver_sistema()              |");
    puts("----------------------------------");

    ver_sistema();
}

void test_ver_kernel() {
    puts("----------------------------------");
    puts("| Test_ver_kernel()              |");
    puts("----------------------------------");

    ver_kernel();
}

void test_ver_ip() {
    puts("----------------------------------");
    puts("| Test_ver_ip()                  |");
    puts("----------------------------------");

    puts(ver_ip());
}

/////////////////////////
// Utils
/////////////////////////

char *concat_path(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 2);
    strcpy(result, s1);
    strcat(result, "/");
    strcat(result, s2);
    return result;
}

/**
 * Run "lslocks | grep ROStrojan" command.
 */
int ls_locks() {
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