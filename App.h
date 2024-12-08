
#ifndef APP_H
#define APP_H
#include <string>

#include "Sistema.h"


class App {
private:
    //Puntero al sistema
    Sistema* sistema;
    static std::string preguntar(const std::string& pregunta);
    static void print(const std::string& mensaje);
public:
    App();

    void menu();

    void opcion1();


    void opcion2();


    bool comprobarSiEsNumeroValido(const std::string & string);

    int convertirANumero(const std::string & string);

    void turnoJugador();



    void opcion3();

    void opcion4();

    void ejecutar();
};



#endif //APP_H
