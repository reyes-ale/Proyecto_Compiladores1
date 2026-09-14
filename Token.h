#include <iostream>
#include "Diccionario.h" 
using namespace std;

class Token {
    private:
        string valor;
        Tipo tipo;

    public:
        Token();
        Token(string valor, Tipo tipo);

        string getValor();
        Tipo getTipo();

};