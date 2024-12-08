
#include <vector>

class Tablero {
private:
    std::vector<std::vector<char>> estadoDelTablero;
public:
    Tablero();
    void iniciar();

    char obtenerPosicion(int i, int c);

    char verificarGanador();

    bool hayMovimientos();

    bool colocarMarca(int fila, int columna, char marca);

    void limpiarPosicion(int fila, int columna);
};


