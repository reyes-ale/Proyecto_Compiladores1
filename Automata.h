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
    int linea=1;
    int columna=1;
    int lineaInicio=1;
    int colInicio=1;
    


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
    void moverPos(char caracter);
    

};