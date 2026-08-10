#include "Estado.h"
using namespace std;

class Automata{
private:
    Estado* estadoInicial;
    Estado* estadoActual;

public:
    Automata();
    Automata(Estado* estadoInicial);
    void reiniciar();
    void avanzar(char caracter);
    Estado* getActual();
}