#ifndef TABLERO_H
#define TABLERO_H

#include "bits.h"
#include "memoria.h"
#include "combinaciones.h"

// Crea e inicializa el tablero dinámico en el Heap con fichas aleatorias (0 a 5)
unsigned char* crearTableroInicial(int filas, int columnas);

// Muestra en consola la representación visual con símbolos (@, #, &, $, 0, =, .)
void mostrarTableroFichas(unsigned char* tablero, int filas, int columnas);

// Muestra la vista de bits binarios (3 bits por celda)
void mostrarTableroBits(unsigned char* tablero, int filas, int columnas);

// Traduce el código numérico de 3 bits a su carácter correspondiente
char obtenerSimboloFicha(int valor);

// Asigna FICHA_VACIA a la casilla elegida por el usuario
void eliminarFichaManual(unsigned char* tablero, int columnas, int fila, int columna);

#endif // TABLERO_H