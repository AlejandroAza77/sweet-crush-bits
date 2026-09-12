#include "bits.h"

int obtenerFicha(unsigned char* tablero, int columnas, int fila, int columna) {
    // Paso 1: posicion (fila, columna) -> indice lineal -> bit inicial
    int indiceLineal = fila * columnas + columna;
    int bitInicial = indiceLineal * 3;

    // Paso 2: bit inicial -> byte donde comienza + posicion dentro del byte
    int byteInicial = bitInicial / 8;
    int offsetEnByte = bitInicial % 8;

    int valor = 0;

    if (offsetEnByte <= 5) {
        // Caso simple: los 3 bits de la ficha caben completos en un solo byte.
        // 1) Se desplaza el byte a la derecha para traer los 3 bits deseados
        //    hasta las posiciones mas bajas.
        // 2) Se aislan esos 3 bits con una mascara AND (0b111 = 7).
        valor = (tablero[byteInicial] >> offsetEnByte) & 0b111;
    } else {
        // Caso especial: la ficha esta repartida entre byteInicial y byteInicial+1.
        // Solo pasa cuando offsetEnByte es 6 o 7 (quedan 1 o 2 bits libres
        // en el primer byte, no los 3 completos).
        int bitsEnPrimerByte = 8 - offsetEnByte;   // 1 o 2 bits
        int bitsEnSegundoByte = 3 - bitsEnPrimerByte;

        unsigned char mascaraPrimerByte = (unsigned char)((1 << bitsEnPrimerByte) - 1);
        unsigned char mascaraSegundoByte = (unsigned char)((1 << bitsEnSegundoByte) - 1);

        // Parte baja del valor: los bits que alcanzaron a caber en el primer byte.
        int parteBaja = (tablero[byteInicial] >> offsetEnByte) & mascaraPrimerByte;

        // Parte alta del valor: los bits restantes, al inicio del segundo byte.
        int parteAlta = tablero[byteInicial + 1] & mascaraSegundoByte;

        // Se combinan: la parte alta se desplaza para ubicarse "despues" de la parte baja.
        valor = parteBaja | (parteAlta << bitsEnPrimerByte);
    }

    return valor;
}

void asignarFicha(unsigned char* tablero, int columnas, int fila, int columna, int valor) {
    int indiceLineal = fila * columnas + columna;
    int bitInicial = indiceLineal * 3;

    int byteInicial = bitInicial / 8;
    int offsetEnByte = bitInicial % 8;

    if (offsetEnByte <= 5) {
        // Caso simple: la ficha cabe completa en un solo byte.
        unsigned char mascara = (unsigned char)(0b111 << offsetEnByte);

        // 1) Limpiar: se ponen en 0 SOLO los 3 bits que se van a reemplazar,
        //    usando AND con la mascara invertida (~mascara). Los demas bits
        //    del byte no se modifican.
        tablero[byteInicial] = (unsigned char)(tablero[byteInicial] & ~mascara);

        // 2) Insertar: se "encienden" los bits del nuevo valor con OR.
        //    Como esos bits ya estan en 0, el OR no afecta a los vecinos.
        tablero[byteInicial] = (unsigned char)(tablero[byteInicial] | (valor << offsetEnByte));
    } else {
        // Caso especial: la ficha se escribe repartida en dos bytes.
        int bitsEnPrimerByte = 8 - offsetEnByte;
        int bitsEnSegundoByte = 3 - bitsEnPrimerByte;

        unsigned char mascaraParteBaja = (unsigned char)((1 << bitsEnPrimerByte) - 1);
        unsigned char mascaraParteAlta = (unsigned char)((1 << bitsEnSegundoByte) - 1);

        // --- Primer byte: recibe los bits menos significativos del valor ---
        unsigned char mascaraPrimerByte = (unsigned char)(mascaraParteBaja << offsetEnByte);
        tablero[byteInicial] = (unsigned char)(tablero[byteInicial] & ~mascaraPrimerByte);
        unsigned char parteBaja = (unsigned char)(valor & mascaraParteBaja);
        tablero[byteInicial] = (unsigned char)(tablero[byteInicial] | (parteBaja << offsetEnByte));

        // --- Segundo byte: recibe los bits mas significativos del valor ---
        tablero[byteInicial + 1] = (unsigned char)(tablero[byteInicial + 1] & ~mascaraParteAlta);
        unsigned char parteAlta = (unsigned char)((valor >> bitsEnPrimerByte) & mascaraParteAlta);
        tablero[byteInicial + 1] = (unsigned char)(tablero[byteInicial + 1] | parteAlta);
    }
}