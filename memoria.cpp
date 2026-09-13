#include "memoria.h"

int bytesNecesarios(int filas, int columnas) {
    int totalBits = filas * columnas * 3;
    return (totalBits + 7) / 8;
}

unsigned char* reservarTablero(int filas, int columnas) {
    int bytes = bytesNecesarios(filas, columnas);
    if (bytes <= 0) return nullptr;

    // Con () al final se inicializan todos los bytes en 0
    unsigned char* tablero = new unsigned char[bytes]();
    return tablero;
}

void liberarTablero(unsigned char* tablero) {
    if (tablero != nullptr) {
        delete[] tablero;
    }
}

bool debeReducirse(int bytesUsados, int bytesReservados) {
    if (bytesReservados <= 0) return false;
    // Para evitar decimales/floats, multiplicamos por 100 primero:
    return ((bytesUsados * 100) / bytesReservados) < 65;
}