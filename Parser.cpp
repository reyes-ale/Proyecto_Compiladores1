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
        return parseDeclaracion();
    } else if (coincide(Tipo::FN)) {
        return parseFuncion();
    } else {
        return nullptr; 

}
}

Nodo* Parser::parseFuncion() {
    Token fnToken = consumir(Tipo::FN);
    Token idToken = consumir(Tipo::IDENTIFICADOR);
    consumir(Tipo::PARENTESIS_ABRE);
    vector<Nodo*> parametros = parseParametros();
    consumir(Tipo::PARENTESIS_CIERRA);
    consumir(Tipo::DOS_PUNTOS);
    string tipoRetorno = parseTipo();
    Nodo* cuerpo = parseCuerpo();

    Nodo* funcionNodo = new Nodo(idToken.getValor(), TipoN::FUNCION);
    for (Nodo* parametro : parametros) {
        funcionNodo->agregarHijito(parametro);
    }
    funcionNodo->agregarHijito(cuerpo);

    return funcionNodo;
}

vector<Nodo*> Parser::parseParametros() {
    vector<Nodo*> parametros;

    if (coincide(Tipo::PARENTESIS_CIERRA)) {
        return parametros; // eps
    }

    Nodo* parametro = parseParametro();
    parametros.push_back(parametro);

    while (coincide(Tipo::COMA)) {
        consumir(Tipo::COMA);
        parametro = parseParametro();
        parametros.push_back(parametro);
    }

    return parametros;
}

Nodo* Parser::parseParametro() {
    Token idToken = consumir(Tipo::IDENTIFICADOR);
    consumir(Tipo::DOS_PUNTOS);
    string tipo = parseTipo();

    Nodo* parametroNodo = new Nodo(idToken.getValor(), TipoN::PARAMETRO);
    parametroNodo->agregarHijito(new Nodo(tipo, TipoN::IDENTIFICADOR));
    return parametroNodo;
}

string Parser::parseTipo() {
    if (coincide(Tipo::TIPO)) {
        Token tipoToken = consumir(Tipo::TIPO);
        return tipoToken.getValor();
    } else {
        return "void"; // Tipo por defecto si no se especifica
    }
}

Nodo* Parser::parseCuerpo() {
    Nodo* cuerpoNodo = new Nodo("cuerpo", TipoN::PROGRAMA);

    while (!coincide(Tipo::LLAVE_CIERRA) && !coincide(Tipo::FIN_ARCHIVO)) {
        Nodo* sentencia = parseSentencia();
        if (sentencia != nullptr) {
            cuerpoNodo->agregarHijito(sentencia);
        }
    }

    return cuerpoNodo;
}

Nodo* Parser::parseSentencia() {
    if (coincide(Tipo::LET)) {
        return parseDeclaracion();
    } else if (coincide(Tipo::IDENTIFICADOR)) {
        return parseAsignacion();
    } else if (coincide(Tipo::IF)) {
        return parseCondicion();
    } else if (coincide(Tipo::WHILE)) {
        return parseWhile();
    } else if (coincide(Tipo::FOR)) {
        return parsePara();
    } else if (coincide(Tipo::RETURN)) {
        return parseRetorno();
    } else {
        return nullptr; // Manejar error o sentencia no reconocida
    }
}

Nodo* Parser::parseDeclaracion() {
    consumir(Tipo::LET);
    Token idToken = consumir(Tipo::IDENTIFICADOR);
    consumir(Tipo::ASIGNACION);
    Nodo* expresionNodo = parseExpresion();
    consumir(Tipo::PUNTO_COMA);

    Nodo* declaracionNodo = new Nodo(idToken.getValor(), TipoN::DECLARACION);
    declaracionNodo->agregarHijito(expresionNodo);
    return declaracionNodo;
}

Nodo* Parser::parseAsignacion() {
    Token idToken = consumir(Tipo::IDENTIFICADOR);
    consumir(Tipo::ASIGNACION);
    Nodo* expresionNodo = parseExpresion();
    consumir(Tipo::PUNTO_COMA);

    Nodo* asignacionNodo = new Nodo(idToken.getValor(), TipoN::ASIGNACION);
    asignacionNodo->agregarHijito(expresionNodo);
    return asignacionNodo;
}