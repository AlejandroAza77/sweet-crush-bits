#ifndef MEMORIA_H
#define MEMORIA_H

// Calcula los bytes mínimos requeridos para guardar filas x columnas fichas
int bytesNecesarios(int filas, int columnas);

// Reserva en el Heap el bloque exacto de bytes inicializado en cero
unsigned char* reservarTablero(int filas, int columnas);

// Libera la memoria dinámica del tablero
void liberarTablero(unsigned char* tablero);

// Verifica si la ocupación real cayó por debajo del 65% de lo reservado
bool debeReducirse(int bytesUsados, int bytesReservados);

#endif // MEMORIA_H