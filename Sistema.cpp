//
// Created by Cuello on 06-12-2024.
//

#include "Sistema.h"

#include <bits/ctype_base.h>

// Instancia Estatica (singleton
Sistema* Sistema::instancia = nullptr; // PUNTERO TIPO SISTEMA , que crea variable instancia que pertenece a la clase sistema y es estatica

// Constructor privado
Sistema::Sistema() {
}


//Destructor
Sistema::~Sistema() {

    }

// Metodo para obtener la instancia
Sistema* Sistema::obtenerInstancia() {
    if (instancia == nullptr) {
        instancia = new Sistema();
    }
    return instancia;
}

void Sistema::iniciarElJuego(char jugadorInicial) {
    tablero.iniciar();

    turnoActual = jugadorInicial;
}

std::string& Sistema::obtenerElTablero() {
    tableroenString.clear();
    for (int f = 0; f < 3; f++) {
        for (int c = 0; c < 3; c++) {
            char celda = tablero.obtenerPosicion(f,c);
            tableroenString += "|";
            if (celda == '_') {
                tableroenString += "-";
            } else {
                tableroenString += celda;
            }
            tableroenString += "|";
            if (c < 2) {
                tableroenString += " ";
            }
        }
        tableroenString += '\n';
    }
    return tableroenString;
}
char Sistema::verificarSiHayGanador() {
    return tablero.verificarGanador();
}
bool Sistema::hayMovimientos() {
    return tablero.hayMovimientos();
}
char Sistema::obtenerElTurnoActual() const{
    return turnoActual;
}
bool Sistema::movimientoJugador(int fila, int columna) {
    if (turnoActual != 'X') {
        return false;
    }
    bool realizado = tablero.colocarMarca(fila, columna, 'X');
    if (realizado) {
        cambiarTurno();
    }
    return realizado;
}
void Sistema::cambiarTurno() {
    if (turnoActual == 'X') {
        turnoActual = 'O';

    } else {
        turnoActual = 'X';
    }
}
std::string Sistema::turnoIA() {
    std::string resultado = "";
    int mejorValor = -1000;
    int mejorFila = -1;
    int mejorColumna = -1;

    for (int fila = 0; fila < 3; fila++) {
        for (int columna = 0; columna < 3; columna++) {
            if (tablero.obtenerPosicion(fila, columna) == '_') {
                tablero.colocarMarca(fila, columna, 'O');
                int valorMovimiento = minimax(0, false, -1000, 1000);
                tablero.limpiarPosicion(fila, columna);

                if (valorMovimiento > mejorValor) {
                    mejorValor = valorMovimiento;
                    mejorFila = fila;
                    mejorColumna = columna;
                }
            }
        }
    }

    if (mejorFila != -1 && mejorColumna != -1) {
        tablero.colocarMarca(mejorFila, mejorColumna, 'O');
        resultado = "La IA ha realizado su movimiento en la posicion: "
                    + std::to_string(mejorFila) + " " + std::to_string(mejorColumna);
        cambiarTurno();
    } else {
        resultado = "La IA no pudo encontrar un movimiento valido.";
    }

    return resultado;
}


int Sistema::minimax(int nivelArbol, bool turnoIA, int alfa, int beta) {
    int evaluacion = evaluarTablero();

    // Si hay un ganador o no hay movimientos posibles, retornar la evaluación
    if (evaluacion == 10 || evaluacion == -10 || !hayMovimientos()) {
        return evaluacion;
    }

    if (turnoIA) {

        int mejorPuntuacion = -1000;

        for (int fila = 0; fila < 3; fila++) {
            for (int columna = 0; columna < 3; columna++) {
                if (tablero.obtenerPosicion(fila, columna) == '_') {
                    tablero.colocarMarca(fila, columna, 'O');
                    int puntuacionActual = minimax(nivelArbol + 1, false, alfa, beta);
                    tablero.limpiarPosicion(fila, columna);

                    if (puntuacionActual > mejorPuntuacion) {
                        mejorPuntuacion = puntuacionActual;
                    }

                    if (puntuacionActual > alfa) {
                        alfa = puntuacionActual;
                    }

                    if (beta <= alfa) {
                        return mejorPuntuacion;
                    }
                }
            }
        }
        return mejorPuntuacion;
    } else {

        int peorPuntuacion = 1000;

        for (int fila = 0; fila < 3; fila++) {
            for (int columna = 0; columna < 3; columna++) {
                if (tablero.obtenerPosicion(fila, columna) == '_') {
                    tablero.colocarMarca(fila, columna, 'X');
                    int puntuacionActual = minimax(nivelArbol + 1, true, alfa, beta);
                    tablero.limpiarPosicion(fila, columna);

                    if (puntuacionActual < peorPuntuacion) {
                        peorPuntuacion = puntuacionActual;
                    }

                    if (puntuacionActual < beta) {
                        beta = puntuacionActual;
                    }

                    if (beta <= alfa) {
                        return peorPuntuacion;
                    }
                }
            }
        }
        return peorPuntuacion;
    }
}

int Sistema::evaluarTablero()  {
    // Verificar si hay un ganador
    char ganador = tablero.verificarGanador();

    // Si la IA gano
    if (ganador == 'O') {
        return 10;
    }

    // Si el jugador gano
    if (ganador == 'X') {
        return -10;
    }

    // Si no hay ganador, devolver 0
    return 0;
}
char Sistema::verificarGanador()  {
    return tablero.verificarGanador();
}