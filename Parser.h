#include <iostream>
#include <cstdlib>
#include <vector>
#include "Nodo.h"
using namespace std;

class Parser {
    private:
        vector<Token> tokens;
        int TokenActual = 0;

    public:
        Parser();
        Parser(const vector<Token>& tokens);
        int getActual();
        void avanzar();
        Token& actual();
        Token& siguiente();
        bool coincide(Tipo tipoEsperado);
        Token consumir(Tipo tipoEsperado);

        //Métodos para ir derivadndo
        Nodo* parsear();
        Nodo* parseCodigo();
        Nodo* parseElemento();
        
};
