#ifndef BITS_H
#define BITS_H

// Modulo bits
// Unico lugar del programa donde se manipulan bits directamente.
// Cada ficha del tablero ocupa exactamente 3 bits, guardados de forma
// continua (sin relleno) dentro de un bloque de memoria (unsigned char*).
// Como 3 no divide a 8, una ficha puede quedar repartida entre dos bytes
// consecutivos; estas funciones manejan ese caso de forma transparente
// para el resto del programa.

// Lee el valor (0 a 7) almacenado en la posicion (fila, columna).
// "columnas" es necesario para calcular el indice lineal de la posicion.
int obtenerFicha(unsigned char* tablero, int columnas, int fila, int columna);

// Escribe "valor" (0 a 7) en la posicion (fila, columna), sin alterar
// los bits de las fichas vecinas.
void asignarFicha(unsigned char* tablero, int columnas, int fila, int columna, int valor);

#endif