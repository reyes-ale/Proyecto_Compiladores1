#include "Estado.h"
#include "Token.h"
#include "Diccionario.h"
using namespace std;

class Automata{
private:
    Estado* estadoInicial;
    Estado* estadoActual;
    vector<Estado*> estados;
    vector<Token> tokensitos;
    Diccionario reservadas;
    string lexema=""; 
    vector<string> errores;

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
    Tipo tipoToken(string lexema, Estado* aceptacion);
    void finalizar();
    vector<string> getErrores();

};