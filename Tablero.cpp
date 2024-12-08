#include "Tablero.h"

#include <vector>

Tablero::Tablero() {
    estadoDelTablero = std::vector<std::vector<char>>(3, std::vector<char>(3, '_'));
}

void Tablero::iniciar() {
    for (int f = 0; f < 3; f++) {
        for (int c = 0; c < 3; c++) {
            estadoDelTablero[f][c] = '_';
        }
    }
}
char Tablero::obtenerPosicion(int i, int c) {
    return estadoDelTablero[i][c];
}
char Tablero::verificarGanador() {
    // Verificar filas
    for (int f = 0; f < 3; f++) {
        if (estadoDelTablero[f][0] == estadoDelTablero[f][1] && estadoDelTablero[f][1] == estadoDelTablero[f][2] && estadoDelTablero[f][0] != '_')
            return estadoDelTablero[f][0];
    }
    // Verificar columnas
    for (int c = 0; c < 3; c++) {
        if (estadoDelTablero[0][c] == estadoDelTablero[1][c] && estadoDelTablero[1][c] == estadoDelTablero[2][c] && estadoDelTablero[0][c] != '_')
            return estadoDelTablero[0][c];
    }
    // Verificar diagonales
    if (estadoDelTablero[0][0] == estadoDelTablero[1][1] && estadoDelTablero[1][1] == estadoDelTablero[2][2] && estadoDelTablero[0][0] != '_')
        return estadoDelTablero[0][0];
    if (estadoDelTablero[0][2] == estadoDelTablero[1][1] && estadoDelTablero[1][1] == estadoDelTablero[2][0] && estadoDelTablero[0][2] != '_')
        return estadoDelTablero[0][2];

    return '_';
}
bool Tablero::hayMovimientos() {
    for (int f = 0; f < 3; f++) {
        for (int c = 0; c < 3; c++) {
            if (estadoDelTablero[f][c] == '_') {
                return true;
            }
        }
    }
    return false;
}
bool Tablero::colocarMarca(int fila, int columna, char marca) {
    if (estadoDelTablero[fila][columna] == '_') {
        estadoDelTablero[fila][columna] = marca;
        return true;
    }
    return false;
}

void Tablero::limpiarPosicion(int fila, int columna) {
    if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3) {
        estadoDelTablero[fila][columna] = '_';
    }
}
