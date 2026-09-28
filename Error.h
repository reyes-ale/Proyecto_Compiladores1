#pragma once
#include <string>
using namespace std;

enum class TipoError {
    LEXICO,
    SINTACTICO
};

class Error {
private:
    TipoError tipo;
    string mensaje;
    int linea;
    int columna;

public:
    Error();
    Error(TipoError tipo, string mensaje, int linea, int columna);

    TipoError getTipo();
    string getMensaje();
    int getLinea();
    int getColumna();
    string getTipoStr();
};