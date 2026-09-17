#include <iostream>
#include "estado.h"

void inicializarEstado(int* eliminacionesUsuario, int* fichasEliminadas,
                       int* combinacionesDetectadas, int* cascadasUltimaJugada,
                       int* puntuacion) {
    *eliminacionesUsuario = 0;
    *fichasEliminadas = 0;
    *combinacionesDetectadas = 0;
    *cascadasUltimaJugada = 0;
    *puntuacion = 0;
}

void actualizarTrasEliminacionManual(int* eliminacionesUsuario, int* fichasEliminadas) {
    // Cuenta como una eliminacion hecha por el usuario, y suma 1 al total
    // de fichas eliminadas (el contador general del PDF incluye TODAS las
    // fichas eliminadas, sea manual o por combinacion). No se otorgan
    // puntos aqui: la regla de puntuacion solo premia combinaciones.
    (*eliminacionesUsuario)++;
    (*fichasEliminadas)++;
}

void actualizarTrasCascadas(int* fichasEliminadas, int* combinacionesDetectadas,
                            int* cascadasUltimaJugada, int* puntuacion,
                            int combinacionesEnEstaJugada, int fichasEliminadasEnEstaJugada,
                            int cascadasEnEstaJugada) {
    // fichasEliminadas y combinacionesDetectadas son contadores
    // ACUMULADOS desde el inicio de la partida, por eso se les suma.
    *fichasEliminadas += fichasEliminadasEnEstaJugada;
    *combinacionesDetectadas += combinacionesEnEstaJugada;

    // cascadasUltimaJugada es especifico de la jugada actual (asi lo pide
    // el PDF: "cascadas producidas por la eliminacion actual"), por eso
    // se REEMPLAZA en vez de acumularse.
    *cascadasUltimaJugada = cascadasEnEstaJugada;

    // Puntuacion: 10 puntos por cada ficha eliminada mediante combinacion.
    *puntuacion += fichasEliminadasEnEstaJugada * PUNTOS_POR_FICHA_EN_COMBINACION;
}

void actualizarTrasModificacionEstructural(int* fichasEliminadas, int fichasEliminadasPorEstructura) {
    // Las fichas que desaparecen al eliminar una fila/columna cuentan
    // para el total general de fichas eliminadas, pero no otorgan puntos
    // (regla de puntuacion: solo las eliminadas por combinacion puntuan).
    *fichasEliminadas += fichasEliminadasPorEstructura;
}

void mostrarEstado(int filas, int columnas, int eliminacionesUsuario,
                   int fichasEliminadas, int combinacionesDetectadas,
                   int cascadasUltimaJugada, int puntuacion) {
    std::cout << "----- Estado del juego -----\n";
    std::cout << "Dimensiones actuales: " << filas << " x " << columnas << "\n";
    std::cout << "Eliminaciones del usuario: " << eliminacionesUsuario << "\n";
    std::cout << "Fichas eliminadas (total): " << fichasEliminadas << "\n";
    std::cout << "Combinaciones detectadas (total): " << combinacionesDetectadas << "\n";
    std::cout << "Cascadas de la ultima jugada: " << cascadasUltimaJugada << "\n";
    std::cout << "Puntuacion: " << puntuacion << "\n";
    std::cout << "-----------------------------\n";
}