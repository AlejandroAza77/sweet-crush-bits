# Sweet Crush — Desafío 1 (Informática II)

Juego de tablero tipo match-3 en consola, desarrollado en C++ con Qt Creator, donde toda la información del tablero se almacena a nivel de bits: cada ficha ocupa exactamente 3 bits, sobre un único bloque continuo de memoria dinámica.

## Integrantes

- Melany Sierra Torres
- Daniel Alejandro Aza Calpa

## Restricciones técnicas del proyecto

- Sin `struct`, `class`, `template`, STL ni `string`.
- Toda la manipulación del tablero se hace con operadores a nivel de bits (`&`, `|`, `~`, `<<`, `>>`).
- Memoria dinámica administrada manualmente con `new` / `delete[]`.
- Entrada/salida exclusivamente con `cin`/`cout`.
- Generación aleatoria con `<random>` (`std::mt19937`).

## Arquitectura del proyecto

El código está organizado en 8 módulos (`.h` / `.cpp`) más el punto de entrada:

| Módulo | Responsabilidad |
|---|---|
| `bits` | Lectura y escritura de una ficha de 3 bits, incluyendo el caso en que una ficha cruza dos bytes. |
| `memoria` | Cálculo de bytes necesarios, reserva/liberación del bloque físico, y regla del 65% de ocupación para decidir cuándo reducirlo. |
| `tablero` | Creación del tablero inicial, visualización (formato de fichas y formato de bits), y eliminación manual de una ficha. |
| `combinaciones` | Detección y marcado de combinaciones horizontales y verticales de 3 o más fichas iguales. |
| `cascadas` | Conversión de marcas a vacío, gravedad, relleno con fichas nuevas, y el ciclo completo de cascadas. |
| `estructura` | Inserción y eliminación de filas o columnas en cualquier posición del tablero. |
| `estado` | Contadores del juego (eliminaciones, fichas eliminadas, combinaciones, cascadas, puntuación). |
| `juego` | Menú de opciones y bucle principal; coordina todos los demás módulos. |
| `main.cpp` | Punto de entrada del programa. |

## Cómo compilar y ejecutar

### Desde Qt Creator
Abrir el archivo `CMakeLists.txt` del proyecto con Qt Creator y ejecutar (Ctrl+R).

### Desde consola (g++)
```
g++ -Wall -Wextra -std=c++17 bits.cpp memoria.cpp tablero.cpp combinaciones.cpp cascadas.cpp estructura.cpp estado.cpp juego.cpp main.cpp -o sweet_crush
./sweet_crush
```

## Informe

El informe preliminar de análisis y diseño se encuentra en este mismo repositorio: [`Informe_Preliminar_SweetCrush.pdf`](./Informe_Preliminar_SweetCrush.pdf).
