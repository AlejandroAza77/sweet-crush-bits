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

int ejecutarCicloCascadas(unsigned char* tablero, int filas, int columnas);

#endif