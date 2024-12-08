
#include "Sistema.h"


// Instancia Estatica (singleton)
Sistema* Sistema::instancia = nullptr; 

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
//Funcion para iniciar el juego
void Sistema::iniciarElJuego(char jugadorInicial) {
    tablero.iniciar();

    turnoActual = jugadorInicial;
}
//Funcion para obtener el tablero
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
//Funcion para verificar si hay ganador
char Sistema::verificarSiHayGanador() {
    return tablero.verificarGanador();
}
//Funcion para verificar si quedan movimientos
bool Sistema::hayMovimientos() {
    return tablero.hayMovimientos();
}
// Funcion para obtener el turno del jugador actual
char Sistema::obtenerElTurnoActual() const{
    return turnoActual;
}
//Funcion para realizar el movimiento del jugador humano
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
//Funcion para cambiar el turno
void Sistema::cambiarTurno() {
    if (turnoActual == 'X') {
        turnoActual = 'O';

    } else {
        turnoActual = 'X';
    }
}
//Funcion para el turno de la IA
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

//Funcion para el Minimax
int Sistema::minimax(int nivelArbol, bool turnoIA, int alfa, int beta) {
    int evaluacion = evaluarTablero();

    
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
//Funcion para evaluar el tablero
int Sistema::evaluarTablero()  {
    
    char ganador = tablero.verificarGanador();

    if (ganador == 'O') {
        return 10;
    }

 
    if (ganador == 'X') {
        return -10;
    }

    return 0;
}
//Funcion para verificar el ganador
char Sistema::verificarGanador()  {
    return tablero.verificarGanador();
}