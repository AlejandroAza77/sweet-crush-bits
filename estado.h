#ifndef ESTADO_H
#define ESTADO_H

// Modulo estado
// Mantiene y muestra los contadores exigidos por el desafio. No conoce
// el tablero ni las reglas del juego: solo recibe numeros ya calculados
// por otros modulos (tablero, combinaciones, cascadas) y los acumula.
//
// Puntos por combinacion (segun el criterio de puntuacion documentado):
// se otorgan 10 puntos por cada ficha eliminada como parte de una
// combinacion de 3 o mas fichas iguales (incluyendo cascadas). Las
// eliminaciones manuales del usuario y las fichas eliminadas por
// modificaciones estructurales (agregar/eliminar fila o columna) NO
// otorgan puntos.
const int PUNTOS_POR_FICHA_EN_COMBINACION = 10;

// Pone todos los contadores en 0 al iniciar una partida nueva.
void inicializarEstado(int* eliminacionesUsuario, int* fichasEliminadas,
                       int* combinacionesDetectadas, int* cascadasUltimaJugada,
                       int* puntuacion);

// Se llama cada vez que el usuario elimina una ficha manualmente.
// Incrementa el conteo de eliminaciones del usuario y el total de fichas
// eliminadas. NO otorga puntos (ver regla de puntuacion arriba).
void actualizarTrasEliminacionManual(int* eliminacionesUsuario, int* fichasEliminadas);

// Se llama despues de ejecutar el ciclo de cascadas (cascadas.h), tanto
// tras una eliminacion manual como tras una modificacion estructural.
// Actualiza fichas eliminadas, combinaciones detectadas, la cantidad de
// cascadas de la jugada actual, y la puntuacion (10 puntos por cada
// ficha eliminada mediante combinacion).
void actualizarTrasCascadas(int* fichasEliminadas, int* combinacionesDetectadas,
                            int* cascadasUltimaJugada, int* puntuacion,
                            int combinacionesEnEstaJugada, int fichasEliminadasEnEstaJugada,
                            int cascadasEnEstaJugada);

// Se llama despues de agregar/eliminar una fila o columna, para dejar
// registrada la cantidad de fichas que se hayan eliminado por el cambio
// estructural en si (no por combinacion). NO otorga puntos.
void actualizarTrasModificacionEstructural(int* fichasEliminadas, int fichasEliminadasPorEstructura);

// Muestra en consola el estado actual del juego.
void mostrarEstado(int filas, int columnas, int eliminacionesUsuario,
                   int fichasEliminadas, int combinacionesDetectadas,
                   int cascadasUltimaJugada, int puntuacion);

#endif