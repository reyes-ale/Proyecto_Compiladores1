#include "Estado.h"
#include "Token.h"
using namespace std;

class Automata{
private:
    Estado* estadoInicial;
    Estado* estadoActual;
    vector<Estado> estados;
    vector<Token> tokensitos;
    string lexema=""; 

public:
    Automata();
    void agregarEstados(Estado* estado);
    Automata(Estado* estadoInicial);
    void reiniciar();
    void avanzar(char caracter);
    Estado* getActual();
    vector<Token> getTokens();
    string tipoToken(string lexema);
    string getLexema();
};