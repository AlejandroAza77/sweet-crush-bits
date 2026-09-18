#include <iostream>
#include "bits.h"
#include "memoria.h"
#include "tablero.h"
#include "cascadas.h"
#include "estado.h"
#include "estructura.h"
#include "juego.h"

using namespace std;

// Opciones del menu (constantes simples, sin usar enum, para no
// introducir un tipo de dato adicional definido por el estudiante).
const int OPCION_ELIMINAR_FICHA = 1;
const int OPCION_AGREGAR_FILA = 2;
const int OPCION_ELIMINAR_FILA = 3;
const int OPCION_AGREGAR_COLUMNA = 4;
const int OPCION_ELIMINAR_COLUMNA = 5;
const int OPCION_VER_ESTADO = 6;
const int OPCION_SALIR = 7;

// Lee un numero entero desde la consola, validando que la entrada sea
// realmente un numero (si el usuario escribe texto, se le pide de nuevo
// en vez de dejar el programa en un estado inconsistente).
static int leerEntero(const char* mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;

        if (cin.fail()) {
            cin.clear();
            while (cin.get() != '\n') {
                if (cin.eof()) break;
            }
            cout << "Entrada invalida, por favor ingresa un numero entero.\n";
        } else {
            while (cin.peek() != '\n') {
                if (cin.eof()) break;
                cin.get();
            }
            if (!cin.eof()) cin.get();
            return valor;
        }
    }
}

static void mostrarMenu() {
    cout << "\n----- MENU -----\n";
    cout << OPCION_ELIMINAR_FICHA << ". Eliminar ficha\n";
    cout << OPCION_AGREGAR_FILA << ". Agregar fila\n";
    cout << OPCION_ELIMINAR_FILA << ". Eliminar fila\n";
    cout << OPCION_AGREGAR_COLUMNA << ". Agregar columna\n";
    cout << OPCION_ELIMINAR_COLUMNA << ". Eliminar columna\n";
    cout << OPCION_VER_ESTADO << ". Ver estado del juego\n";
    cout << OPCION_SALIR << ". Salir\n";
}

// Muestra ambos formatos del tablero, tal como lo pide el desafio: se
// muestran SIEMPRE los dos, sin hacerlos opcionales.
static void mostrarTableroCompleto(unsigned char* tablero, int filas, int columnas) {
    mostrarTableroFichas(tablero, filas, columnas);
    mostrarTableroBits(tablero, filas, columnas);
}

// Muestra un resumen corto de lo que produjo la ultima accion (cascadas,
// combinaciones y puntos ganados EN ESTA JUGADA), sin repetir todo el
// detalle completo del estado (para eso esta la opcion "Ver estado").
static void mostrarResumenJugada(int cascadas, int combinacionesEnEstaJugada,
                                 int fichasEliminadasEnEstaJugada, int puntosGanados) {
    cout << "\n[Resultado de la jugada] Cascadas: " << cascadas
         << " | Combinaciones: " << combinacionesEnEstaJugada
         << " | Fichas eliminadas por combinacion: " << fichasEliminadasEnEstaJugada
         << " | Puntos ganados: " << puntosGanados << "\n";
}

static void accionEliminarFicha(unsigned char* tablero, int filas, int columnas,
                                int* eliminacionesUsuario, int* fichasEliminadas,
                                int* combinacionesDetectadas, int* cascadasUltimaJugada,
                                int* puntuacion) {
    int fila = leerEntero("Ingresa fila a eliminar: ");
    int columna = leerEntero("Ingresa columna a eliminar: ");

    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        cout << "Posicion fuera de rango. No se realizo ninguna eliminacion.\n";
        return;
    }

    eliminarFichaManual(tablero, columnas, fila, columna);
    actualizarTrasEliminacionManual(eliminacionesUsuario, fichasEliminadas);

    cout << "\n[Paso 1] Ficha eliminada (se observa la casilla vacia):\n";
    mostrarTableroCompleto(tablero, filas, columnas);

    int combinacionesTotal = 0, fichasEliminadasTotal = 0;
    int cascadas = ejecutarCicloCascadas(tablero, filas, columnas,
                                         &combinacionesTotal, &fichasEliminadasTotal);
    int puntuacionAntes = *puntuacion;
    actualizarTrasCascadas(fichasEliminadas, combinacionesDetectadas, cascadasUltimaJugada,
                           puntuacion, combinacionesTotal, fichasEliminadasTotal, cascadas);

    cout << "\n[Paso 2] Tras aplicar gravedad y rellenar:\n";
    mostrarTableroCompleto(tablero, filas, columnas);
    mostrarResumenJugada(cascadas, combinacionesTotal, fichasEliminadasTotal,
                         *puntuacion - puntuacionAntes);
}

// tipo: 1=agregar fila, 2=eliminar fila, 3=agregar columna, 4=eliminar columna
static void accionEstructural(int tipo, unsigned char** tablero, int* filas, int* columnas,
                              int* capacidadReservada,
                              int* fichasEliminadas, int* combinacionesDetectadas,
                              int* cascadasUltimaJugada, int* puntuacion) {
    int posicion;
    int cascadas = 0;
    int combinacionesTotal = 0, fichasEliminadasTotal = 0;
    int puntuacionAntes = *puntuacion;

    if (tipo == 1) {
        posicion = leerEntero("Ingresa la posicion donde insertar la fila (0 a filas): ");
        if (posicion < 0 || posicion > *filas) {
            cout << "Posicion fuera de rango. No se realizo ningun cambio.\n";
            return;
        }
        cascadas = agregarFila(tablero, filas, *columnas, posicion, capacidadReservada,
                               &combinacionesTotal, &fichasEliminadasTotal);
    } else if (tipo == 2) {
        if (*filas <= 1) {
            cout << "No se puede eliminar la unica fila que queda.\n";
            return;
        }
        posicion = leerEntero("Ingresa la fila a eliminar (0 a filas-1): ");
        if (posicion < 0 || posicion >= *filas) {
            cout << "Posicion fuera de rango. No se realizo ningun cambio.\n";
            return;
        }
        cascadas = eliminarFila(tablero, filas, *columnas, posicion, capacidadReservada,
                                &combinacionesTotal, &fichasEliminadasTotal);
    } else if (tipo == 3) {
        posicion = leerEntero("Ingresa la posicion donde insertar la columna (0 a columnas): ");
        if (posicion < 0 || posicion > *columnas) {
            cout << "Posicion fuera de rango. No se realizo ningun cambio.\n";
            return;
        }
        cascadas = agregarColumna(tablero, *filas, columnas, posicion, capacidadReservada,
                                  &combinacionesTotal, &fichasEliminadasTotal);
    } else {
        if (*columnas <= 1) {
            cout << "No se puede eliminar la unica columna que queda.\n";
            return;
        }
        posicion = leerEntero("Ingresa la columna a eliminar (0 a columnas-1): ");
        if (posicion < 0 || posicion >= *columnas) {
            cout << "Posicion fuera de rango. No se realizo ningun cambio.\n";
            return;
        }
        cascadas = eliminarColumna(tablero, *filas, columnas, posicion, capacidadReservada,
                                   &combinacionesTotal, &fichasEliminadasTotal);
    }

    actualizarTrasCascadas(fichasEliminadas, combinacionesDetectadas, cascadasUltimaJugada,
                           puntuacion, combinacionesTotal, fichasEliminadasTotal, cascadas);

    cout << "\nTablero tras el cambio estructural:\n";
    mostrarTableroCompleto(*tablero, *filas, *columnas);
    mostrarResumenJugada(cascadas, combinacionesTotal, fichasEliminadasTotal,
                         *puntuacion - puntuacionAntes);
}

static void bucleJuego(unsigned char** tablero, int* filas, int* columnas, int* capacidadReservada) {
    int eliminacionesUsuario, fichasEliminadas, combinacionesDetectadas;
    int cascadasUltimaJugada, puntuacion;
    inicializarEstado(&eliminacionesUsuario, &fichasEliminadas, &combinacionesDetectadas,
                      &cascadasUltimaJugada, &puntuacion);

    cout << "\nTablero inicial:\n";
    mostrarTableroCompleto(*tablero, *filas, *columnas);

    bool jugando = true;
    while (jugando) {
        mostrarMenu();
        int opcion = leerEntero("Elige una opcion: ");

        if (opcion == OPCION_ELIMINAR_FICHA) {
            accionEliminarFicha(*tablero, *filas, *columnas,
                                &eliminacionesUsuario, &fichasEliminadas,
                                &combinacionesDetectadas, &cascadasUltimaJugada, &puntuacion);
        } else if (opcion == OPCION_AGREGAR_FILA) {
            accionEstructural(1, tablero, filas, columnas, capacidadReservada, &fichasEliminadas,
                              &combinacionesDetectadas, &cascadasUltimaJugada, &puntuacion);
        } else if (opcion == OPCION_ELIMINAR_FILA) {
            accionEstructural(2, tablero, filas, columnas, capacidadReservada, &fichasEliminadas,
                              &combinacionesDetectadas, &cascadasUltimaJugada, &puntuacion);
        } else if (opcion == OPCION_AGREGAR_COLUMNA) {
            accionEstructural(3, tablero, filas, columnas, capacidadReservada, &fichasEliminadas,
                              &combinacionesDetectadas, &cascadasUltimaJugada, &puntuacion);
        } else if (opcion == OPCION_ELIMINAR_COLUMNA) {
            accionEstructural(4, tablero, filas, columnas, capacidadReservada, &fichasEliminadas,
                              &combinacionesDetectadas, &cascadasUltimaJugada, &puntuacion);
        } else if (opcion == OPCION_VER_ESTADO) {
            mostrarEstado(*filas, *columnas, eliminacionesUsuario, fichasEliminadas,
                          combinacionesDetectadas, cascadasUltimaJugada, puntuacion);
        } else if (opcion == OPCION_SALIR) {
            cout << "\nGracias por jugar. Estado final:\n";
            mostrarEstado(*filas, *columnas, eliminacionesUsuario, fichasEliminadas,
                          combinacionesDetectadas, cascadasUltimaJugada, puntuacion);
            jugando = false;
        } else {
            cout << "Opcion invalida, intenta de nuevo.\n";
        }
    }
}

void iniciarJuego() {
    int filas = leerEntero("Ingresa la cantidad de filas del tablero: ");
    int columnas = leerEntero("Ingresa la cantidad de columnas del tablero: ");

    while (filas < 3 || columnas < 3) {
        cout << "El tablero debe tener al menos 3 filas y 3 columnas.\n";
        filas = leerEntero("Ingresa la cantidad de filas del tablero: ");
        columnas = leerEntero("Ingresa la cantidad de columnas del tablero: ");
    }

    unsigned char* tablero = crearTableroInicial(filas, columnas);
    if (tablero == nullptr) {
        cout << "No se pudo crear el tablero.\n";
        return;
    }

    // La capacidad reservada arranca exactamente en lo que necesitan las
    // dimensiones iniciales (crearTableroInicial siempre reserva exacto).
    // A partir de aqui, estructura.cpp es quien la mantiene actualizada.
    int capacidadReservada = bytesNecesarios(filas, columnas);

    bucleJuego(&tablero, &filas, &columnas, &capacidadReservada);

    liberarTablero(tablero);
}