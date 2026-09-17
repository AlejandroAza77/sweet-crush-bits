#ifndef CASCADAS_H
#define CASCADAS_H

// Recorre el tablero y convierte toda posicion marcada (MARCA_ELIMINAR)
// a vacio (FICHA_VACIA). Devuelve cuantas posiciones se convirtieron,
// util para el conteo de "fichas eliminadas" del modulo estado.
int convertirMarcasAVacio(unsigned char* tablero, int filas, int columnas);

// Para cada columna: compacta las fichas no vacias hacia abajo, y rellena
// los huecos que queden en la parte superior con fichas nuevas aleatorias
// (0 a 5).
void aplicarGravedadYRelleno(unsigned char* tablero, int filas, int columnas);

// Devuelve la cantidad de cascadas producidas (no cuenta el relleno
// inicial obligatorio). Ademas, si los punteros no son nulos, reporta:
//   - *combinacionesTotal: cuantas combinaciones se marcaron en total
//     durante todo el ciclo (puede ser mayor que la cantidad de cascadas,
//     ya que una sola cascada puede incluir varias combinaciones a la vez).
//   - *fichasEliminadasTotal: cuantas fichas se convirtieron de marca a
//     vacio en total durante todo el ciclo.
int ejecutarCicloCascadas(unsigned char* tablero, int filas, int columnas,
                          int* combinacionesTotal = nullptr,
                          int* fichasEliminadasTotal = nullptr);

#endif