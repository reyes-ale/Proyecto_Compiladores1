#include "Error.h"

Error::Error() {
    this->tipo = TipoError::LEXICO;
    this->mensaje = "";
    this->linea = 0;
    this->columna = 0;
}

Error::Error(TipoError tipo, string mensaje, int linea, int columna) {
    this->tipo = tipo;
    this->mensaje = mensaje;
    this->linea = linea;
    this->columna = columna;
}

TipoError Error::getTipo() {
    return tipo;
}

string Error::getMensaje() {
    return mensaje;
}

int Error::getLinea() {
    return linea;
}

int Error::getColumna() {
    return columna;
}

string Error::getTipoStr() {
    if(tipo == TipoError::LEXICO){
        return "LEXICO";
    }
    return "SINTACTICO";
}