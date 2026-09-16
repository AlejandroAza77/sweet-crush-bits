#include <random>
#include "bits.h"
#include "combinaciones.h"
#include "cascadas.h"

// Genera un valor de ficha aleatorio (0 a 5), usando la biblioteca <random>
// de C++
// El generador y la distribucion son "static": se crean una sola vez
// (la primera vez que se llama a esta funcion) y se reutilizan despues,
// en vez de reconstruirse en cada llamada.
static int fichaAleatoria() {
    static std::random_device semilla;
    static std::mt19937 generador(semilla());
    static std::uniform_int_distribution<int> distribucion(0, 5);

    return distribucion(generador);
}

int convertirMarcasAVacio(unsigned char* tablero, int filas, int columnas) {
    int contador = 0;

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (obtenerFicha(tablero, columnas, f, c) == MARCA_ELIMINAR) {
                asignarFicha(tablero, columnas, f, c, FICHA_VACIA);
                contador++;
            }
        }
    }

    return contador;
}

void aplicarGravedadYRelleno(unsigned char* tablero, int filas, int columnas) {
    for (int c = 0; c < columnas; c++) {
        // "destino" es la posicion (de abajo hacia arriba) donde debe
        // caer la proxima ficha no vacia que se encuentre.
        int destino = filas - 1;

        for (int f = filas - 1; f >= 0; f--) {
            int valor = obtenerFicha(tablero, columnas, f, c);

            if (valor != FICHA_VACIA) {
                if (f != destino) {
                    // Se "mueve" la ficha hacia abajo: se copia a la
                    // posicion destino y se vacia la posicion original.
                    asignarFicha(tablero, columnas, destino, c, valor);
                    asignarFicha(tablero, columnas, f, c, FICHA_VACIA);
                }
                destino--;
            }
        }

        // Todo lo que quedo por encima de "destino" son huecos: se
        // rellenan con fichas nuevas aleatorias.
        for (int f = destino; f >= 0; f--) {
            asignarFicha(tablero, columnas, f, c, fichaAleatoria());
        }
    }
}

int ejecutarCicloCascadas(unsigned char* tablero, int filas, int columnas) {

    aplicarGravedadYRelleno(tablero, filas, columnas);

    int cascadas = 0;
    bool huboCombinacion = detectarYMarcarCombinaciones(tablero, filas, columnas);

    while (huboCombinacion) {
        convertirMarcasAVacio(tablero, filas, columnas);
        aplicarGravedadYRelleno(tablero, filas, columnas);
        cascadas++;

        huboCombinacion = detectarYMarcarCombinaciones(tablero, filas, columnas);
    }

    return cascadas;
}