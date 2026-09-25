#include "Parser.h"
#include <iostream>
#include <cstdlib>

Parser::Parser(const vector<Token>& tokens) : tokens(tokens) {}

Token& Parser::actual() {
    return tokens[TokenActual];
}


Token& Parser::siguiente() {
    return tokens[TokenActual + 1];
}

void Parser::avanzar() {
    TokenActual++;
}

bool Parser::coincide(Tipo tipoEsperado) {
    return actual().getTipo() == tipoEsperado;
}

Token Parser::consumir(Tipo tipoEsperado) {
    if (coincide(tipoEsperado)) {
        Token t = actual();
        avanzar();
        return t;
    }
    return actual();
}

// Derivaciones

Nodo* Parser::parsear() {
    return parseCodigo();
}

Nodo* Parser::parseCodigo() {
    Nodo* programa = new Nodo("programa", TipoN::PROGRAMA);

    while (!coincide(Tipo::FIN_ARCHIVO)) {
        Nodo* elemento = parseElemento();
        programa->agregarHijito(elemento);
    }
 
    return programa;
}

Nodo* Parser::parseElemento() {
    if (coincide(Tipo::LET)) {
        return nullptr;
    } else if (coincide(Tipo::FN)) {
        return nullptr;
    } else {
        return nullptr; 

}
}