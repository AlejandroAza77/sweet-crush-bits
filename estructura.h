#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include "bits.h"
#include "memoria.h"
#include "cascadas.h"

// Modulo estructura
// Agrega o elimina filas/columnas en cualquier posicion del tablero,
// reconstruyendo el bloque de memoria con las nuevas dimensiones y
// ejecutando el ciclo de cascadas sobre el resultado.
//
// "capacidadReservada" es la cantidad de bytes FISICAMENTE reservados en
// este momento (puede ser mayor a lo que bytesNecesarios(filas,columnas)
// calcularia de nuevo, si una eliminacion anterior no redujo la memoria
// por la regla del 65%). Estas funciones LEEN y ACTUALIZAN esa variable:
//   - Al agregar: siempre se reserva exacto, asi que capacidadReservada
//     se actualiza siempre al nuevo valor exacto.
//   - Al eliminar: se compara el nuevo requerimiento contra
//     capacidadReservada (no contra un recalculo de las dimensiones
//     actuales). Si debeReducirse() da verdadero, se reduce de verdad y
//     capacidadReservada se actualiza; si no, el bloque fisico se
//     conserva IGUAL y capacidadReservada NO cambia.
//
// Todas devuelven la cantidad de cascadas producidas, y opcionalmente
// reportan (parametros con valor por defecto nullptr) el total de
// combinaciones y fichas eliminadas durante ese ciclo.
//
// "posicion" para agregar: 0 a la dimension actual, inclusive (se puede
// insertar al final). "posicion" para eliminar: 0 a dimension-1.

int agregarFila(unsigned char** tablero, int* filas, int columnas, int posicion,
                int* capacidadReservada,
                int* combinacionesTotal = nullptr, int* fichasEliminadasTotal = nullptr);

int eliminarFila(unsigned char** tablero, int* filas, int columnas, int posicion,
                 int* capacidadReservada,
                 int* combinacionesTotal = nullptr, int* fichasEliminadasTotal = nullptr);

int agregarColumna(unsigned char** tablero, int filas, int* columnas, int posicion,
                   int* capacidadReservada,
                   int* combinacionesTotal = nullptr, int* fichasEliminadasTotal = nullptr);

int eliminarColumna(unsigned char** tablero, int filas, int* columnas, int posicion,
                    int* capacidadReservada,
                    int* combinacionesTotal = nullptr, int* fichasEliminadasTotal = nullptr);

#endif