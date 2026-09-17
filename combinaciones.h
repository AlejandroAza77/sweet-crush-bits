#ifndef COMBINACIONES_H
#define COMBINACIONES_H

// Recorre cada fila y marca las rachas de 3 o mas fichas iguales.
// Devuelve cuantas combinaciones (rachas) se marcaron (0 si no hubo ninguna).
int detectarYMarcarHorizontal(unsigned char* tablero, int filas, int columnas);

// Recorre cada columna y marca las rachas de 3 o mas fichas iguales.
// Devuelve cuantas combinaciones (rachas) se marcaron (0 si no hubo ninguna).
int detectarYMarcarVertical(unsigned char* tablero, int filas, int columnas);

// Funcion principal del modulo: ejecuta ambos recorridos (horizontal y
// vertical) sobre el tablero actual. Devuelve el total de combinaciones
// marcadas entre ambos recorridos (0 si no se encontro ninguna).
int detectarYMarcarCombinaciones(unsigned char* tablero, int filas, int columnas);

#endif