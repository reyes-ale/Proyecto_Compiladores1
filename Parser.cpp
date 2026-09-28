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
    cerr << "Error sintactico: se esperaba "
         << nombreTipo(tipoEsperado)
         << " pero se encontro "
         << nombreTipo(actual().getTipo())
         << " en línea: "
         << actual().getLinea()
         << endl;
    exit(1);
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
        error("Inicio de elemento no reconocido en línea: " + to_string(actual().getLinea())
                + "\nSe encontró: " + actual().getValor());
        return nullptr; 

}
}

Nodo* Parser::parseFuncion() {
    Token fnToken = consumir(Tipo::FN);
    Token idToken = consumir(Tipo::IDENTIFICADOR);
    consumir(Tipo::PARENTESIS_ABRE);
    vector<Nodo*> parametros = parseParametros();
    consumir(Tipo::PARENTESIS_CIERRA);
    consumir(Tipo::FLECHA);
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
        error("Sentencia no reconocida en línea: " + to_string(actual().getLinea())
                + "\nSe encontró: " + actual().getValor());
        
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

Nodo* Parser::parseCondicion() {
    consumir(Tipo::IF);
    Nodo* expresionNodo = parseExpresion();
    consumir(Tipo::LLAVE_ABRE);
    Nodo* cuerpoNodo = parseCuerpo();
    consumir(Tipo::LLAVE_CIERRA);

    Nodo* condicionNodo = new Nodo("if", TipoN::CONDICION);
    condicionNodo->agregarHijito(expresionNodo);
    condicionNodo->agregarHijito(cuerpoNodo);

    if (coincide(Tipo::ELSE)) {
        consumir(Tipo::ELSE);
        consumir(Tipo::LLAVE_ABRE);
        Nodo* cuerpoElseNodo = parseCuerpo();
        consumir(Tipo::LLAVE_CIERRA);
        condicionNodo->agregarHijito(cuerpoElseNodo);
    }

    return condicionNodo;
}

Nodo* Parser::parseWhile() {
    consumir(Tipo::WHILE);
    Nodo* expresionNodo = parseExpresion();
    consumir(Tipo::LLAVE_ABRE);
    Nodo* cuerpoNodo = parseCuerpo();
    consumir(Tipo::LLAVE_CIERRA);

    Nodo* whileNodo = new Nodo("while", TipoN::BUCLE_WHILE);
    whileNodo->agregarHijito(expresionNodo);
    whileNodo->agregarHijito(cuerpoNodo);

    return whileNodo;
}

Nodo* Parser::parsePara() {
    consumir(Tipo::FOR);
    Token idToken = consumir(Tipo::IDENTIFICADOR);
    consumir(Tipo::IN);
    Nodo* rangoNodo = parseRango();
    consumir(Tipo::LLAVE_ABRE);
    Nodo* cuerpoNodo = parseCuerpo();
    consumir(Tipo::LLAVE_CIERRA);

    Nodo* forNodo = new Nodo(idToken.getValor(), TipoN::BUCLE_FOR);
    forNodo->agregarHijito(rangoNodo);
    forNodo->agregarHijito(cuerpoNodo);

    return forNodo;
}

Nodo* Parser::parseRango() {
    Nodo* rangoNodo = new Nodo("rango", TipoN::RANGO);
    Token inicioToken = consumir(Tipo::ENTERO);
    consumir(Tipo::RANGO_FOR);
    Token finToken = consumir(Tipo::ENTERO);

    rangoNodo->agregarHijito(new Nodo(inicioToken.getValor(), TipoN::ENTERO));
    rangoNodo->agregarHijito(new Nodo(finToken.getValor(), TipoN::ENTERO));

    return rangoNodo;
}

Nodo* Parser::parseRetorno() {
    consumir(Tipo::RETURN);
    Nodo* expresionNodo = parseExpresion();
    consumir(Tipo::PUNTO_COMA);

    Nodo* retornoNodo = new Nodo("return", TipoN::RETORNO);
    retornoNodo->agregarHijito(expresionNodo);

    return retornoNodo;
}

Nodo* Parser::parseExpresion() {
    return parseLogica();
}

Nodo* Parser::parseLogica() {
    Nodo* nodoIzquierdo = parseEXPand();

    while (coincide(Tipo::OR)) {
        Token operadorToken = consumir(Tipo::OR);
        Nodo* nodoDerecho = parseEXPand();

        Nodo* operadorNodo = new Nodo(operadorToken.getValor(), TipoN::BINARIA);
        operadorNodo->agregarHijito(nodoIzquierdo);
        operadorNodo->agregarHijito(nodoDerecho);

        nodoIzquierdo = operadorNodo;
    }

    return nodoIzquierdo;
}

Nodo* Parser::parseEXPand() {
    Nodo* nodoIzquierdo = parseEXPnot();

    while (coincide(Tipo::AND)) {
        Token operadorToken = consumir(Tipo::AND);
        Nodo* nodoDerecho = parseEXPnot();

        Nodo* operadorNodo = new Nodo(operadorToken.getValor(), TipoN::BINARIA);
        operadorNodo->agregarHijito(nodoIzquierdo);
        operadorNodo->agregarHijito(nodoDerecho);

        nodoIzquierdo = operadorNodo;
    }

    return nodoIzquierdo;
}

Nodo* Parser::parseEXPnot() {
    if (coincide(Tipo::NOT)) {
        Token operadorToken = consumir(Tipo::NOT);
        Nodo* nodoDerecho = parseRelacional();

        Nodo* operadorNodo = new Nodo(operadorToken.getValor(), TipoN::UNARIA);
        operadorNodo->agregarHijito(nodoDerecho);

        return operadorNodo;
    } else {
        return parseRelacional();
    }
}

Nodo* Parser::parseRelacional() {
    Nodo* nodoIzquierdo = parseMatematica();

    while (coincide(Tipo::IGUAL_IGUAL) || coincide(Tipo::DISTINTO) ||
           coincide(Tipo::MENOR) || coincide(Tipo::MAYOR) ||
           coincide(Tipo::MENOR_IGUAL) || coincide(Tipo::MAYOR_IGUAL)) {
        Token operadorToken = actual();
        avanzar();
        Nodo* nodoDerecho = parseMatematica();

        Nodo* operadorNodo = new Nodo(operadorToken.getValor(), TipoN::BINARIA);
        operadorNodo->agregarHijito(nodoIzquierdo);
        operadorNodo->agregarHijito(nodoDerecho);

        nodoIzquierdo = operadorNodo;
    }

    return nodoIzquierdo;
}

Nodo* Parser::parseMatematica() {
    Nodo* nodoIzquierdo = parseTermino();

    while (coincide(Tipo::MAS) || coincide(Tipo::MENOS)) {
        Token operadorToken = actual();
        avanzar();
        Nodo* nodoDerecho = parseTermino();

        Nodo* operadorNodo = new Nodo(operadorToken.getValor(), TipoN::BINARIA);
        operadorNodo->agregarHijito(nodoIzquierdo);
        operadorNodo->agregarHijito(nodoDerecho);

        nodoIzquierdo = operadorNodo;
    }

    return nodoIzquierdo;
}

Nodo* Parser::parseTermino() {
    Nodo* nodoIzquierdo = parseUnario();

    while (coincide(Tipo::POR) || coincide(Tipo::ENTRE)) {
        Token operadorToken = actual();
        avanzar();
        Nodo* nodoDerecho = parseUnario();

        Nodo* operadorNodo = new Nodo(operadorToken.getValor(), TipoN::BINARIA);
        operadorNodo->agregarHijito(nodoIzquierdo);
        operadorNodo->agregarHijito(nodoDerecho);

        nodoIzquierdo = operadorNodo;
    }

    return nodoIzquierdo;
}

Nodo* Parser::parseUnario() {
    if (coincide(Tipo::MAS) || coincide(Tipo::MENOS) || coincide(Tipo::NOT)) {
        Token operadorToken = actual();
        avanzar();
        Nodo* nodoDerecho = parseFactor();

        Nodo* operadorNodo = new Nodo(operadorToken.getValor(), TipoN::UNARIA);
        operadorNodo->agregarHijito(nodoDerecho);

        return operadorNodo;
    } else {
        return parseFactor();
    }
}

Nodo* Parser::parseFactor() {
    if (coincide(Tipo::IDENTIFICADOR)) {
        Token idToken = consumir(Tipo::IDENTIFICADOR);
        if (coincide(Tipo::PARENTESIS_ABRE)) {
            consumir(Tipo::PARENTESIS_ABRE);
            vector<Nodo*> argumentos = parseArgumentos();
            consumir(Tipo::PARENTESIS_CIERRA);

            Nodo* llamadaNodo = new Nodo(idToken.getValor(), TipoN::LLAMADA);
            for (Nodo* argumento : argumentos) {
                llamadaNodo->agregarHijito(argumento);
            }
            return llamadaNodo;
        } else {
            return new Nodo(idToken.getValor(), TipoN::IDENTIFICADOR);
        }
    } else if (coincide(Tipo::ENTERO)) {
        Token enteroToken = consumir(Tipo::ENTERO);
        return new Nodo(enteroToken.getValor(), TipoN::ENTERO);
    } else if (coincide(Tipo::DECIMAL)) {
        Token decimalToken = consumir(Tipo::DECIMAL);
        return new Nodo(decimalToken.getValor(), TipoN::DECIMAL);
    } else if (coincide(Tipo::CADENA)) {
        Token cadenaToken = consumir(Tipo::CADENA);
        return new Nodo(cadenaToken.getValor(), TipoN::CADENA);
    } else if (coincide(Tipo::CARACTER)) {
        Token caracterToken = consumir(Tipo::CARACTER);
        return new Nodo(caracterToken.getValor(), TipoN::CARACTER);
    } else if (coincide(Tipo::VERDADERO) || coincide(Tipo::FALSO)) {
        Token booleanoToken = actual();
        avanzar();
        return new Nodo(booleanoToken.getValor(), TipoN::BOOLEANO);
    } else if (coincide(Tipo::PARENTESIS_ABRE)) {
        consumir(Tipo::PARENTESIS_ABRE);
        Nodo* expresionNodo = parseExpresion();
        consumir(Tipo::PARENTESIS_CIERRA);
        return expresionNodo;
    } else {
        // Manejar error o caso no reconocido
        error("Factor no reconocido en línea: " + to_string(actual().getLinea())
                + "\nSe encontró: " + actual().getValor());
        return nullptr;
    }
}

vector<Nodo*> Parser::parseArgumentos() {
    vector<Nodo*> argumentos;

    if (coincide(Tipo::PARENTESIS_CIERRA)) {
        return argumentos; // eps
    }

    Nodo* argumento = parseExpresion();
    argumentos.push_back(argumento);

    while (coincide(Tipo::COMA)) {
        consumir(Tipo::COMA);
        argumento = parseExpresion();
        argumentos.push_back(argumento);
    }

    return argumentos;
}

void Parser::error(string mensaje) {
    cerr << "Error sintactico: " << mensaje << endl;
    exit(1);
}