#ifndef BITS_H
#define BITS_H

//Los codigos 0 a 5 representan los 6 tipos
// de ficha jugables; estos dos son los codigos que quedan libres con 3 bits.
const int FICHA_VACIA = 6;     // 0b110: posicion sin ficha
const int MARCA_ELIMINAR = 7;  // 0b111: marca temporal usada durante la
// deteccion de combinaciones (ver combinaciones.h)

// Lee el valor (0 a 7) almacenado en la posicion (fila, columna).
// "columnas" es necesario para calcular el indice lineal de la posicion.
int obtenerFicha(unsigned char* tablero, int columnas, int fila, int columna);

// Escribe "valor" (0 a 7) en la posicion (fila, columna), sin alterar
// los bits de las fichas vecinas.
void asignarFicha(unsigned char* tablero, int columnas, int fila, int columna, int valor);

#endif