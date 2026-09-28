#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Nodo.h"
#include "Error.h"
#include "TablaSimbolos.h"
using namespace std;

class Parser {
    private:
        vector<Token> tokens;
        int TokenActual = 0;
        vector<Error>& errores;
        TablaSimbolos tabla;

    public:
        Parser(const vector<Token>& tokens, vector<Error>& errores);
        int getActual();
        void avanzar();
        Token& actual();
        Token& siguiente();
        bool coincide(Tipo tipoEsperado);
        Token consumir(Tipo tipoEsperado);
        void error(string mensaje);

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
        void sincronizar();
        TablaSimbolos& getTabla();
};