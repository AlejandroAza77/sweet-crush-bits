#include "estructura.h"
#include <random>

// Genera un valor de ficha aleatorio entre 0 y 5
static int fichaAleatoria() {
    static std::random_device semilla;
    static std::mt19937 generador(semilla());
    static std::uniform_int_distribution<int> distribucion(0, 5);
    return distribucion(generador);
}

int agregarFila(unsigned char** tablero, int* filas, int columnas, int posicion,
                int* capacidadReservada,
                int* combinacionesTotal, int* fichasEliminadasTotal) {
    if (posicion < 0 || posicion > *filas) return 0;

    int nuevasFilas = *filas + 1;
    // Asignacion de un bloque nuevo exacto para las nuevas dimensiones
    // (al crecer, la reserva SIEMPRE es exacta, sin umbral de por medio).
    unsigned char* nuevoTablero = reservarTablero(nuevasFilas, columnas);

    for (int f = 0; f < nuevasFilas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            if (f < posicion) {
                // Copia directa de las filas previas a la insercion
                int val = obtenerFicha(*tablero, columnas, f, c);
                asignarFicha(nuevoTablero, columnas, f, c, val);
            } else if (f == posicion) {
                // Insercion de la nueva fila rellena con fichas aleatorias
                asignarFicha(nuevoTablero, columnas, f, c, fichaAleatoria());
            } else {
                // Desplazamiento de las filas posteriores (leen de f - 1)
                int val = obtenerFicha(*tablero, columnas, f - 1, c);
                asignarFicha(nuevoTablero, columnas, f, c, val);
            }
        }
    }

    liberarTablero(*tablero);
    *tablero = nuevoTablero;
    *filas = nuevasFilas;
    *capacidadReservada = bytesNecesarios(nuevasFilas, columnas);

    return ejecutarCicloCascadas(*tablero, *filas, columnas, combinacionesTotal, fichasEliminadasTotal);
}

int eliminarFila(unsigned char** tablero, int* filas, int columnas, int posicion,
                 int* capacidadReservada,
                 int* combinacionesTotal, int* fichasEliminadasTotal) {
    if (*filas <= 1 || posicion < 0 || posicion >= *filas) return 0;

    int nuevasFilas = *filas - 1;
    int bytesNuevos = bytesNecesarios(nuevasFilas, columnas);

    unsigned char* temp = reservarTablero(nuevasFilas, columnas);

    for (int f = 0; f < nuevasFilas; ++f) {
        // Se omite la fila eliminada tomando datos de (f + 1) cuando se alcanza la posicion
        int filaOrigen = (f < posicion) ? f : f + 1;
        for (int c = 0; c < columnas; ++c) {
            int val = obtenerFicha(*tablero, columnas, filaOrigen, c);
            asignarFicha(temp, columnas, f, c, val);
        }
    }

    // Regla del 65%: se compara contra la capacidad FISICA real (no contra
    // el requerimiento recalculado de las dimensiones actuales, que podria
    // ya no coincidir con lo realmente reservado si una reduccion previa
    // no cruzo el umbral).
    if (debeReducirse(bytesNuevos, *capacidadReservada)) {
        liberarTablero(*tablero);
        *tablero = temp;
        *capacidadReservada = bytesNuevos;
    } else {
        // Si no cae por debajo del 65%, se copia el contenido compactado
        // al bloque existente (que sigue siendo mas grande de lo
        // estrictamente necesario); capacidadReservada NO cambia, porque
        // el bloque fisico sigue siendo el mismo de antes.
        for (int i = 0; i < bytesNuevos; ++i) {
            (*tablero)[i] = temp[i];
        }
        liberarTablero(temp);
    }

    *filas = nuevasFilas;
    return ejecutarCicloCascadas(*tablero, *filas, columnas, combinacionesTotal, fichasEliminadasTotal);
}

int agregarColumna(unsigned char** tablero, int filas, int* columnas, int posicion,
                   int* capacidadReservada,
                   int* combinacionesTotal, int* fichasEliminadasTotal) {
    if (posicion < 0 || posicion > *columnas) return 0;

    int nuevasCols = *columnas + 1;
    unsigned char* nuevoTablero = reservarTablero(filas, nuevasCols);

    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < nuevasCols; ++c) {
            if (c < posicion) {
                int val = obtenerFicha(*tablero, *columnas, f, c);
                asignarFicha(nuevoTablero, nuevasCols, f, c, val);
            } else if (c == posicion) {
                asignarFicha(nuevoTablero, nuevasCols, f, c, fichaAleatoria());
            } else {
                int val = obtenerFicha(*tablero, *columnas, f, c - 1);
                asignarFicha(nuevoTablero, nuevasCols, f, c, val);
            }
        }
    }

    liberarTablero(*tablero);
    *tablero = nuevoTablero;
    *columnas = nuevasCols;
    *capacidadReservada = bytesNecesarios(filas, nuevasCols);

    return ejecutarCicloCascadas(*tablero, filas, *columnas, combinacionesTotal, fichasEliminadasTotal);
}

int eliminarColumna(unsigned char** tablero, int filas, int* columnas, int posicion,
                    int* capacidadReservada,
                    int* combinacionesTotal, int* fichasEliminadasTotal) {
    if (*columnas <= 1 || posicion < 0 || posicion >= *columnas) return 0;

    int nuevasCols = *columnas - 1;
    int bytesNuevos = bytesNecesarios(filas, nuevasCols);

    unsigned char* temp = reservarTablero(filas, nuevasCols);

    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < nuevasCols; ++c) {
            int colOrigen = (c < posicion) ? c : c + 1;
            int val = obtenerFicha(*tablero, *columnas, f, colOrigen);
            asignarFicha(temp, nuevasCols, f, c, val);
        }
    }

    if (debeReducirse(bytesNuevos, *capacidadReservada)) {
        liberarTablero(*tablero);
        *tablero = temp;
        *capacidadReservada = bytesNuevos;
    } else {
        for (int i = 0; i < bytesNuevos; ++i) {
            (*tablero)[i] = temp[i];
        }
        liberarTablero(temp);
    }

    *columnas = nuevasCols;
    return ejecutarCicloCascadas(*tablero, filas, *columnas, combinacionesTotal, fichasEliminadasTotal);
}