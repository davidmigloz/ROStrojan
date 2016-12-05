/*
 * ****************************************************************************
 * cleaning_process.c
 *
 * Lógica del proceso cleaner.
 * Encargado de realizar tareas de limpieza.
 * ****************************************************************************
 */

#include "cleaner_process.h"

// PRIVATE HEADERS

int _get_max_time();
long _convert_to_timestamp(int period);

/**
 * Lógica del proceso cleaner.
 * @param sem_id semaforo para la memoria compartida.
 * @param shm_address dirección virtual del segmento de memoria compartida.
 * @param max_num_clients número máximo de clientes.
 * @return EXIT_SUCCESS o EXIT_FAILURE.
 */
int cleaner_process(int sem_id, char *shm_address, int max_num_clients) {
    // TODO llamar a _clean cuando se reciba la orden por la tubería
    return EXIT_SUCCESS;
}

int _clean(int sem_id, char *shm_address, int max_num_clients) {
    // Obtener antigüedad máxima
    int max_time = _get_max_time();
    // Obteber timestamp máximo
    long max_timestamp = _convert_to_timestamp(max_time);
    // Limpiar registros antiguos
    return clean_old_records(shm_address, max_timestamp, max_num_clients, sem_id);
}

/**
 * Obtiene del fichero de entorno la antigüedad máxima que puede tener un registro.
 * Por defecto 10 minutos.
 * @return antiguedad máxima.
 */
int _get_max_time() {
    int max_time;

    // Leer archivo de entorno
    char *val = get_var_value(CLEANING_SECTION, MAX_TIME_VAR);

    if (strlen(val) == 0) {
        // No existe variable -> crearla (por defecto MAX_TIME_DEFAULT)
        char max_num[3];
        sprintf(max_num, "%d", MAX_TIME_DEFAULT);                   // To convert int to string
        ver_entorno(CLEANING_SECTION, NULL);                        // Create section
        modificar_entorno(CLEANING_SECTION, MAX_TIME_VAR, max_num); // Add var
        max_time = MAX_TIME_DEFAULT;
    } else {
        // Si existe, obtener valor
        max_time = atoi(val);
    }
    return max_time;
}

/**
 * Dada un periodo de tiempo, devuelve el timestamp del momento actual menos ese periodo.
 * @param period periodo de tiempo en minutos.
 * @return unix timestamp.
 */
long _convert_to_timestamp(int period) {
    // Obtener timestamp actual
    long  now = time(0);
    // Substraer period
    return now - (period * 60);
}
