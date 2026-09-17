#include <random>
#include "bits.h"
#include "combinaciones.h"
#include "cascadas.h"

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

int ejecutarCicloCascadas(unsigned char* tablero, int filas, int columnas,
                          int* combinacionesTotal, int* fichasEliminadasTotal) {
    // Relleno inicial obligatorio: si esta funcion se llama justo despues
    // de una eliminacion manual, hay exactamente un hueco que todavia
    // nadie lleno. Quitar una sola ficha no puede por si sola crear una
    // combinacion nueva, asi que no tiene sentido esperar a "detectar
    // algo" antes de rellenar por primera vez.
    aplicarGravedadYRelleno(tablero, filas, columnas);

    int cascadas = 0;
    int sumaCombinaciones = 0;
    int sumaFichasEliminadas = 0;

    int combinacionesEncontradas = detectarYMarcarCombinaciones(tablero, filas, columnas);

    while (combinacionesEncontradas > 0) {
        sumaCombinaciones += combinacionesEncontradas;
        sumaFichasEliminadas += convertirMarcasAVacio(tablero, filas, columnas);
        aplicarGravedadYRelleno(tablero, filas, columnas);
        cascadas++;

        combinacionesEncontradas = detectarYMarcarCombinaciones(tablero, filas, columnas);
    }

    if (combinacionesTotal != nullptr) {
        *combinacionesTotal = sumaCombinaciones;
    }
    if (fichasEliminadasTotal != nullptr) {
        *fichasEliminadasTotal = sumaFichasEliminadas;
    }

    return cascadas;
}