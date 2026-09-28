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
        void error();

        //Métodos para ir derivadndo
        Nodo* parsear();
        Nodo* parseCodigo();
        Nodo* parseElemento();
        Nodo* parseFuncion();
        vector<Nodo*> parseParametros();
        Nodo* parseParametro();
        string parseTipo();
        Nodo* parseCuerpo();
        Nodo* parseSentencia();
        Nodo* parseDeclaracion();
        Nodo* parseAsignacion();
        Nodo* parseCondicion();
        Nodo* parseWhile();
        Nodo* parsePara();
        Nodo* parseRango();
        Nodo* parseRetorno();
        Nodo* parseExpresion();
        Nodo* parseLogica();
        Nodo* parseEXPand();
        Nodo* parseEXPnot();
        Nodo* parseRelacional();
        Nodo* parseMatematica();
        Nodo* parseTermino();    
        Nodo* parseUnario();
        Nodo* parseFactor();
        vector<Nodo*> parseArgumentos();
        
};
