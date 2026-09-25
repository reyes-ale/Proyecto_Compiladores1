#pragma once

#include <iostream>
#include "Diccionario.h"
using namespace std;

class Token {
    private:
        string valor;
        Tipo tipo;
        int linea;
        int columna;

    public:
        Token();
        Token(string valor, Tipo tipo);
        Token (string valor, Tipo tipo , int linea=0, int columna=0);
        string getValor();
        Tipo getTipo();
        int getLinea();
        int getColumna();

};