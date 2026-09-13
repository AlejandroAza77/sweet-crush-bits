#ifndef COMBINACIONES_H
#define COMBINACIONES_H

// Modulo combinaciones
// Recorre el tablero buscando 3 o mas fichas iguales consecutivas, en
// horizontal y en vertical. Las posiciones encontradas se marcan con el
// codigo MARCA_ELIMINAR (111), en vez de vaciarse de inmediato, para que
// una ficha que pertenezca a la vez a una combinacion horizontal y a una
// vertical no se procese dos veces ni se pierda. La conversion final de
// esas marcas a "vacio" es responsabilidad del modulo cascadas.

// Recorre cada fila y marca las rachas de 3 o mas fichas iguales.
// Devuelve true si se marco al menos una combinacion.
bool detectarYMarcarHorizontal(unsigned char* tablero, int filas, int columnas);

// Recorre cada columna y marca las rachas de 3 o mas fichas iguales.
// Devuelve true si se marco al menos una combinacion.
bool detectarYMarcarVertical(unsigned char* tablero, int filas, int columnas);

// Funcion principal del modulo: ejecuta ambos recorridos (horizontal y
// vertical) sobre el tablero actual. Devuelve true si se marco alguna
// combinacion en cualquiera de los dos recorridos.
bool detectarYMarcarCombinaciones(unsigned char* tablero, int filas, int columnas);

#endif