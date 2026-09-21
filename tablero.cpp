#include "tablero.h"
#include <iostream>
#include <random>

using namespace std;

char obtenerSimboloFicha(int valor) {
    switch (valor) {
    case 0: return '@';
    case 1: return '#';
    case 2: return '&';
    case 3: return '$';
    case 4: return '0';
    case 5: return '=';
    case FICHA_VACIA:    return '.'; // Código 6 (0b110)
    case MARCA_ELIMINAR: return 'X'; // Código 7 (0b111)
    default: return '?';
    }
}

unsigned char* crearTableroInicial(int filas, int columnas) {
    unsigned char* tablero = reservarTablero(filas, columnas);
    if (tablero == nullptr) return nullptr;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 5);

    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            asignarFicha(tablero, columnas, f, c, dist(gen));
        }
    }

    // El llenado aleatorio puede, por azar, generar combinaciones de 3 o
    // mas fichas ya formadas desde el inicio (antes de que el jugador
    // haga cualquier movimiento), lo cual no tiene sentido en un juego
    // de tipo match-3: el tablero inicial debe estar "estable". Se
    // detectan y regeneran EN EL MISMO LUGAR (sin aplicar gravedad, ya
    // que aqui no se trata de una eliminacion del jugador, solo de
    // "volver a tirar los dados" para esas posiciones), repitiendo hasta
    // que no quede ninguna combinacion.
    int combosEncontrados = detectarYMarcarCombinaciones(tablero, filas, columnas);
    while (combosEncontrados > 0) {
        for (int f = 0; f < filas; ++f) {
            for (int c = 0; c < columnas; ++c) {
                if (obtenerFicha(tablero, columnas, f, c) == MARCA_ELIMINAR) {
                    asignarFicha(tablero, columnas, f, c, dist(gen));
                }
            }
        }
        combosEncontrados = detectarYMarcarCombinaciones(tablero, filas, columnas);
    }

    return tablero;
}

void mostrarTableroFichas(unsigned char* tablero, int filas, int columnas) {
    cout << "\n--- TABLERO DE FICHAS ---" << endl;
    cout << "    ";
    for (int c = 0; c < columnas; ++c) cout << c << " ";
    cout << "\n   +";
    for (int c = 0; c < columnas; ++c) cout << "--";
    cout << "+\n";

    for (int f = 0; f < filas; ++f) {
        if (f < 10) cout << " " << f << " | ";
        else cout << f << " | ";

        for (int c = 0; c < columnas; ++c) {
            int val = obtenerFicha(tablero, columnas, f, c);
            cout << obtenerSimboloFicha(val) << " ";
        }
        cout << "|\n";
    }
    cout << "   +";
    for (int c = 0; c < columnas; ++c) cout << "--";
    cout << "+\n";
}

void mostrarTableroBits(unsigned char* tablero, int filas, int columnas) {
    cout << "\n--- TABLERO DE BITS ---" << endl;
    cout << "    ";
    for (int c = 0; c < columnas; ++c) cout << " " << c << "  ";
    cout << "\n   +";
    for (int c = 0; c < columnas; ++c) cout << "----";
    cout << "+\n";

    for (int f = 0; f < filas; ++f) {
        if (f < 10) cout << " " << f << " |";
        else cout << f << " |";

        for (int c = 0; c < columnas; ++c) {
            int val = obtenerFicha(tablero, columnas, f, c);
            for (int b = 2; b >= 0; --b) {
                cout << ((val >> b) & 1);
            }
            cout << "|";
        }
        cout << "\n";
    }
    cout << "   +";
    for (int c = 0; c < columnas; ++c) cout << "----";
    cout << "+\n";
}

void eliminarFichaManual(unsigned char* tablero, int columnas, int fila, int columna) {
    // Se usa FICHA_VACIA (definida en bits.h) en lugar de hardcodear el número 6
    asignarFicha(tablero, columnas, fila, columna, FICHA_VACIA);
}