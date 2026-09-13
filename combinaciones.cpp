#include "bits.h"
#include "combinaciones.h"

bool detectarYMarcarHorizontal(unsigned char* tablero, int filas, int columnas) {
    bool huboCombinacion = false;

    for (int f = 0; f < filas; f++) {

        int valorTramo = obtenerFicha(tablero, columnas, f, 0);
        int inicioTramo = 0;
        int contador = 1;

        for (int c = 1; c < columnas; c++) {
            int valorActual = obtenerFicha(tablero, columnas, f, c);


            bool continuaRacha = valorTramo != FICHA_VACIA &&
                                 (valorActual == valorTramo ||
                                  valorActual == MARCA_ELIMINAR ||
                                  valorTramo == MARCA_ELIMINAR);

            if (continuaRacha) {
                contador++;
            } else {
                if (contador >= 3) {
                    for (int k = inicioTramo; k < c; k++) {
                        asignarFicha(tablero, columnas, f, k, MARCA_ELIMINAR);
                    }
                    huboCombinacion = true;
                }
                valorTramo = valorActual;
                inicioTramo = c;
                contador = 1;
            }
        }

        // La racha final de la fila no pasa por el "else" del ciclo,
        // asi que se revisa aparte al terminar de recorrer las columnas.
        if (contador >= 3) {
            for (int k = inicioTramo; k < columnas; k++) {
                asignarFicha(tablero, columnas, f, k, MARCA_ELIMINAR);
            }
            huboCombinacion = true;
        }
    }

    return huboCombinacion;
}

bool detectarYMarcarVertical(unsigned char* tablero, int filas, int columnas) {
    bool huboCombinacion = false;

    for (int c = 0; c < columnas; c++) {
        int valorTramo = obtenerFicha(tablero, columnas, 0, c);
        int inicioTramo = 0;
        int contador = 1;

        for (int f = 1; f < filas; f++) {
            int valorActual = obtenerFicha(tablero, columnas, f, c);

            bool continuaRacha = valorTramo != FICHA_VACIA &&
                                 (valorActual == valorTramo ||
                                  valorActual == MARCA_ELIMINAR ||
                                  valorTramo == MARCA_ELIMINAR);

            if (continuaRacha) {
                contador++;
            } else {
                if (contador >= 3) {
                    for (int k = inicioTramo; k < f; k++) {
                        asignarFicha(tablero, columnas, k, c, MARCA_ELIMINAR);
                    }
                    huboCombinacion = true;
                }
                valorTramo = valorActual;
                inicioTramo = f;
                contador = 1;
            }
        }

        if (contador >= 3) {
            for (int k = inicioTramo; k < filas; k++) {
                asignarFicha(tablero, columnas, k, c, MARCA_ELIMINAR);
            }
            huboCombinacion = true;
        }
    }

    return huboCombinacion;
}

bool detectarYMarcarCombinaciones(unsigned char* tablero, int filas, int columnas) {
    // Se ejecutan ambos recorridos siempre (sin "cortocircuitar"), porque
    // aunque el horizontal ya haya encontrado algo, el vertical tiene que
    // revisar el tablero igualmente.
    bool huboHorizontal = detectarYMarcarHorizontal(tablero, filas, columnas);
    bool huboVertical = detectarYMarcarVertical(tablero, filas, columnas);

    return huboHorizontal || huboVertical;
}