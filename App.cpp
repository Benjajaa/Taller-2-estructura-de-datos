
#include "App.h"

#include <iostream>
// constructor
App::App() {
    sistema = Sistema::obtenerInstancia();

}
//Metodo para imprimir mas facil
void App::print(const std::string& mensaje) {
    std::cout << mensaje << std::endl;
}
//Metodo para preguntar
std::string App::preguntar(const std::string& pregunta) {
    std::string respuesta;
    print(pregunta);
    std::cout << "> ";
    std::getline(std::cin, respuesta);
    return respuesta;
}
//Imprimir menu
void App::menu() {
    print("Opciones: ");
    print("1. Iniciar nueva partida");
    print("2. Mostrar el tablero");
    print("3. Continuar con el siguiente turno");
    print("4. Verificar estado del juego");
    print("5. Salir");
}


void App::opcion1() {
    bool valido = false;
    std::string respuesta = preguntar("¿Quien inicia la partida? (X para el jugador, O para IA): ");
    do {
        if (respuesta == "x" || respuesta == "X") {
            respuesta = "X";
            valido = true;
        }
        else if (respuesta == "o" || respuesta == "O") {
            respuesta = "O";
            valido = true;
        }
        else {
            respuesta = preguntar("Respuesta invalida. Por favor ingrese X para el jugador, O para IA");
        }
    } while (valido == false);
    sistema->iniciarElJuego(respuesta[0]); // es asi pa pasar un char y no un string
    print("Una nueva partida se ha iniciado :o ");
}

void App::opcion2() {
    print("\nTablero:");
    print(sistema->obtenerElTablero());
}

void App::opcion3() {
    char ganador = sistema->verificarSiHayGanador();
    if (ganador != '_') {
        if (ganador == 'X') {
            print(" El ganador es: X (Jugador), no se puede continuar la partida, inicie una nueva");
        } else if (ganador == 'O') {
            print("El ganador es: O (IA), no se puede continuar la partida, inicie una nueva");
        }
        return;
    }
    if (!sistema->hayMovimientos()) {
        print("No hay mas movimientos disponibles, no se puede continuar la partida, inicie una nueva ");
        return;
    }
    if (sistema->obtenerElTurnoActual() == 'X' ) {
        turnoJugador();
    }
    else if (sistema->obtenerElTurnoActual() == 'O' ) {
        print(sistema->turnoIA());
        print(sistema->obtenerElTablero());
    }
}


void App::ejecutar() {
    print("Bienvenido al juego del gato");
    print("-----------");
    print("Tu, como jugador seras la X , y la IA sera el O ");
    print("-----------");
    std::string opcion = "";
    opcion1();
    do {
        menu();
        opcion = preguntar("Ingrese la opcion que desea realizar");
        if (opcion == "1") {
            opcion1();
        }
        else if (opcion == "2") {
            opcion2();
        }
        else if (opcion == "3") {
            opcion3();
        }
        else if (opcion == "4") {
            opcion4();
        }
        else if (opcion == "5") {
            print("Cerando el programa, gracias por jugar :D");
        }
    } while (opcion != "5");
}
void App::turnoJugador() {
    print("Tu turno jugador (X)");
    bool valido = false;
    int fila, columna;
    std::string filaIngresada, columnaIngresada;
    do {
        print(sistema->obtenerElTablero());
        filaIngresada = preguntar("Ingrese la fila en la que pondra una X (1,2,3)");
        if (comprobarSiEsNumeroValido(filaIngresada) == false) {
            print("La fila es invalida, recuerde solo numeros dentro del rango del tablero (1,2,3)");
        }
        else {
            fila = convertirANumero(filaIngresada);
            columnaIngresada = preguntar("Ingrese la columna en la que pondra una X (1,2,3)");
            if (comprobarSiEsNumeroValido(columnaIngresada) == false) {
                print("La Columna es invalida, recuerde solo numeros dentro del rango del tablero (1,2,3)");
            }
            else {
                columna = convertirANumero(columnaIngresada);
                if (!sistema->movimientoJugador(fila,columna)) {
                    print("Movimiento no valido, la posicion esta fuera de rango o ya esta ocupada");
                }
                else{
                    print("Posicion valida, y registrada");
                    valido = true;
                }
            }
        }
    } while (!valido);
    print(sistema->obtenerElTablero());
}

bool App::comprobarSiEsNumeroValido(const std::string &string) {
    if (string == "1" || string == "2" || string == "3") {
        return true;
    }
    return false;
}

int App::convertirANumero(const std::string &string) {
    if (string == "1") {
        return 0;
    }
    else if (string == "2") {
        return 1;
    }
    else if (string == "3") {
        return 2;
    }
    else {
        return -1;
    }
}
void App::opcion4() {
    char ganador = sistema->verificarGanador();

    if (ganador == '_') {
        if (sistema->hayMovimientos()) {
            print("Sin ganador hasta ahora, la partida puede seguir :o");
        } else {
            print("Empate, no hay mas movimientos posibles, inicie una nueva partida .");
        }
    } else if (ganador == 'X') {
        print("El ganador es: X (Jugador)");
    } else if (ganador == 'O') {
        print("El ganador es: O (IA)");
    }
}