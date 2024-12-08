
#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>

#include "Tablero.h"


class Sistema {
private:
    static Sistema* instancia; // instancia
    Tablero tablero;
    std::string tableroenString;
    char turnoActual;

    Sistema(); // constructor
public:
    ~Sistema(); // funcion de destructor
    void iniciarElJuego(char jugadorInicial);

    std::string & obtenerElTablero();

    char verificarSiHayGanador();

    bool hayMovimientos();

    char obtenerElTurnoActual() const;

    void cambiarTurno();

    bool movimientoJugador(int fila, int columna);

    int evaluarTablero();

    int minimax(int nivelArbol, bool turnoIA, int alfa, int beta);

    std::string turnoIA();

    char verificarGanador();


    static Sistema* obtenerInstancia(); // obtener la instancia

};



#endif //SISTEMA_H
