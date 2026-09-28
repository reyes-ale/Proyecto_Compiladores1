#include "Parser.h"
#include <iostream>
#include <cstdlib>

Parser::Parser(const vector<Token>& tokens, vector<Error>& errores)
    : tokens(tokens), errores(errores) {}

Token& Parser::actual() {
    return tokens[TokenActual];
}

Token& Parser::siguiente() {
    return tokens[TokenActual + 1];
}

void Parser::avanzar() {
    if (TokenActual < (int)tokens.size() - 1) {
        TokenActual++;
    }
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
    errores.push_back(Error(TipoError::SINTACTICO,
        "se esperaba " + nombreTipo(tipoEsperado) +
        " pero se encontro " + nombreTipo(actual().getTipo()),
        actual().getLinea(), actual().getColumna()));
    return Token("", Tipo::NINGUNO, actual().getLinea(), actual().getColumna());
}

// Derivaciones

Nodo* Parser::parsear() {
    return parseCodigo();
}

Nodo* Parser::parseCodigo() {
    Nodo* programa = new Nodo("programa", TipoN::PROGRAMA);

    while (!coincide(Tipo::FIN_ARCHIVO)) {
        Nodo* elemento = parseElemento();
        if (elemento != nullptr) {
            programa->agregarHijito(elemento);
        } else {
            sincronizar();
        }
    }
    return programa;
}

Nodo* Parser::parseElemento() {
    if (coincide(Tipo::LET)) {
        return parseDeclaracion();
    } else if (coincide(Tipo::FN)) {
        return parseFuncion();
    } else {
        error("Inicio de elemento no reconocido");
        return nullptr;
    }
}

Nodo* Parser::parseFuncion() {
    consumir(Tipo::FN);
    Token idToken = consumir(Tipo::IDENTIFICADOR);

    tabla.insertar(idToken.getValor(), "");

    if (!coincide(Tipo::PARENTESIS_ABRE)) {
        error("se esperaba ( despues del nombre de la funcion");
        sincronizar();
        return new Nodo(idToken.getValor(), TipoN::FUNCION);
    }
    consumir(Tipo::PARENTESIS_ABRE);
    vector<Nodo*> parametros = parseParametros();
    consumir(Tipo::PARENTESIS_CIERRA);

    string tipoRetorno = "";
    if (coincide(Tipo::FLECHA)) {
        consumir(Tipo::FLECHA);
        tipoRetorno = parseTipo();
    }

    tabla.actualizarTipo(idToken.getValor(), tipoRetorno);

    if (!coincide(Tipo::LLAVE_ABRE)) {
        error("se esperaba { para el cuerpo de la funcion");
        sincronizar();
        return new Nodo(idToken.getValor(), TipoN::FUNCION);
    }
    consumir(Tipo::LLAVE_ABRE);
    Nodo* cuerpo = parseCuerpo();
    consumir(Tipo::LLAVE_CIERRA);

    Nodo* funcionNodo = new Nodo(idToken.getValor(), TipoN::FUNCION);
    if (!tipoRetorno.empty()) {
        funcionNodo->agregarHijito(new Nodo(tipoRetorno, TipoN::IDENTIFICADOR));
    }
    for (Nodo* parametro : parametros) {
        funcionNodo->agregarHijito(parametro);
    }
    funcionNodo->agregarHijito(cuerpo);
    return funcionNodo;
}

vector<Nodo*> Parser::parseParametros() {
    vector<Nodo*> parametros;

    if (coincide(Tipo::PARENTESIS_CIERRA)) {
        return parametros;
    }

    Nodo* parametro = parseParametro();
    if (parametro != nullptr) parametros.push_back(parametro);

    while (coincide(Tipo::COMA)) {
        consumir(Tipo::COMA);
        parametro = parseParametro();
        if (parametro != nullptr) parametros.push_back(parametro);
    }

    return parametros;
}

Nodo* Parser::parseParametro() {
    Token idToken = consumir(Tipo::IDENTIFICADOR);
    consumir(Tipo::DOS_PUNTOS);
    string tipo = parseTipo();

    Nodo* parametroNodo = new Nodo(idToken.getValor(), TipoN::PARAMETRO);
    parametroNodo->agregarHijito(new Nodo(tipo, TipoN::IDENTIFICADOR));
    tabla.insertar(idToken.getValor(), tipo);
    return parametroNodo;
}

string Parser::parseTipo() {
    if (!coincide(Tipo::TIPO)) {
        error("se esperaba un tipo");
        return "desconocido";
    }
    Token tipoToken = consumir(Tipo::TIPO);
    return tipoToken.getValor();
}

Nodo* Parser::parseCuerpo() {
    Nodo* cuerpoNodo = new Nodo("cuerpo", TipoN::BLOQUE);

    while (!coincide(Tipo::LLAVE_CIERRA) && !coincide(Tipo::FIN_ARCHIVO)) {
        Nodo* sentencia = parseSentencia();
        if (sentencia != nullptr) {
            cuerpoNodo->agregarHijito(sentencia);
        } else {
            sincronizar();
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
        error("Sentencia no reconocida");
        return nullptr;
    }
}

Nodo* Parser::parseDeclaracion() {
    consumir(Tipo::LET);
    Token idToken = consumir(Tipo::IDENTIFICADOR);
    consumir(Tipo::ASIGNACION);
    Nodo* expresionNodo = parseExpresion();

    if (!coincide(Tipo::PUNTO_COMA)) {
        error("se esperaba ; al final de la declaracion");
        sincronizar();
    } else {
        consumir(Tipo::PUNTO_COMA);
    }

    Nodo* declaracionNodo = new Nodo(idToken.getValor(), TipoN::DECLARACION);
    if (expresionNodo != nullptr) {
        declaracionNodo->agregarHijito(expresionNodo);
    } else {
        declaracionNodo->agregarHijito(new Nodo("error", TipoN::IDENTIFICADOR));
    }
    tabla.insertar(idToken.getValor(), "");
    return declaracionNodo;
}

Nodo* Parser::parseAsignacion() {
    Token idToken = consumir(Tipo::IDENTIFICADOR);
    consumir(Tipo::ASIGNACION);
    Nodo* expresionNodo = parseExpresion();

    if (!coincide(Tipo::PUNTO_COMA)) {
        error("se esperaba ; al final de la asignacion");
        sincronizar();
    } else {
        consumir(Tipo::PUNTO_COMA);
    }

    Nodo* asignacionNodo = new Nodo(idToken.getValor(), TipoN::ASIGNACION);
    if (expresionNodo != nullptr) {
        asignacionNodo->agregarHijito(expresionNodo);
    } else {
        asignacionNodo->agregarHijito(new Nodo("error", TipoN::IDENTIFICADOR));
    }
    return asignacionNodo;
}

Nodo* Parser::parseCondicion() {
    consumir(Tipo::IF);
    Nodo* expresionNodo = parseExpresion();

    if (!coincide(Tipo::LLAVE_ABRE)) {
        error("se esperaba { despues de la condicion");
        sincronizar();
        return new Nodo("if", TipoN::CONDICION);
    }
    consumir(Tipo::LLAVE_ABRE);
    Nodo* cuerpoNodo = parseCuerpo();

    if (!coincide(Tipo::LLAVE_CIERRA)) {
        error("se esperaba } al final del bloque if");
        sincronizar();
    } else {
        consumir(Tipo::LLAVE_CIERRA);
    }

    Nodo* condicionNodo = new Nodo("if", TipoN::CONDICION);
    if (expresionNodo != nullptr) condicionNodo->agregarHijito(expresionNodo);
    condicionNodo->agregarHijito(cuerpoNodo);

    if (coincide(Tipo::ELSE)) {
        consumir(Tipo::ELSE);
        if (!coincide(Tipo::LLAVE_ABRE)) {
            error("se esperaba { despues de else");
            sincronizar();
            return condicionNodo;
        }
        consumir(Tipo::LLAVE_ABRE);
        Nodo* cuerpoElseNodo = parseCuerpo();
        if (!coincide(Tipo::LLAVE_CIERRA)) {
            error("se esperaba } al final del bloque else");
            sincronizar();
        } else {
            consumir(Tipo::LLAVE_CIERRA);
        }
        condicionNodo->agregarHijito(cuerpoElseNodo);
    }

    return condicionNodo;
}

Nodo* Parser::parseWhile() {
    consumir(Tipo::WHILE);
    Nodo* expresionNodo = parseExpresion();

    if (!coincide(Tipo::LLAVE_ABRE)) {
        error("se esperaba { despues de la condicion del while");
        sincronizar();
        return new Nodo("while", TipoN::BUCLE_WHILE);
    }
    consumir(Tipo::LLAVE_ABRE);
    Nodo* cuerpoNodo = parseCuerpo();

    if (!coincide(Tipo::LLAVE_CIERRA)) {
        error("se esperaba } al final del bloque while");
        sincronizar();
    } else {
        consumir(Tipo::LLAVE_CIERRA);
    }

    Nodo* whileNodo = new Nodo("while", TipoN::BUCLE_WHILE);
    if (expresionNodo != nullptr) whileNodo->agregarHijito(expresionNodo);
    whileNodo->agregarHijito(cuerpoNodo);
    return whileNodo;
}

Nodo* Parser::parsePara() {
    consumir(Tipo::FOR);
    Token idToken = consumir(Tipo::IDENTIFICADOR);
    consumir(Tipo::IN);
    Nodo* rangoNodo = parseRango();

    if (!coincide(Tipo::LLAVE_ABRE)) {
        error("se esperaba { despues del rango del for");
        sincronizar();
        return new Nodo(idToken.getValor(), TipoN::BUCLE_FOR);
    }
    consumir(Tipo::LLAVE_ABRE);
    Nodo* cuerpoNodo = parseCuerpo();

    if (!coincide(Tipo::LLAVE_CIERRA)) {
        error("se esperaba } al final del bloque for");
        sincronizar();
    } else {
        consumir(Tipo::LLAVE_CIERRA);
    }

    Nodo* forNodo = new Nodo(idToken.getValor(), TipoN::BUCLE_FOR);
    if (rangoNodo != nullptr) forNodo->agregarHijito(rangoNodo);
    forNodo->agregarHijito(cuerpoNodo);
    tabla.insertar(idToken.getValor(), "");
    return forNodo;
}

Nodo* Parser::parseRango() {
    Nodo* rangoNodo = new Nodo("rango", TipoN::RANGO);
    Nodo* inicioToken = parseMatematica();
    consumir(Tipo::RANGO_FOR);
    Nodo* finToken = parseMatematica();

    if (inicioToken != nullptr) rangoNodo->agregarHijito(inicioToken);
    if (finToken != nullptr) rangoNodo->agregarHijito(finToken);
    return rangoNodo;
}

Nodo* Parser::parseRetorno() {
    consumir(Tipo::RETURN);
    Nodo* retornoNodo = new Nodo("return", TipoN::RETORNO);
    if (!coincide(Tipo::PUNTO_COMA)) {
        Nodo* expr = parseExpresion();
        if (expr != nullptr) {
            retornoNodo->agregarHijito(expr);
        }
    }
    if (!coincide(Tipo::PUNTO_COMA)) {
        error("se esperaba ; al final del return");
        sincronizar();
    } else {
        consumir(Tipo::PUNTO_COMA);
    }
    return retornoNodo;
}

Nodo* Parser::parseExpresion() {
    return parseLogica();
}

Nodo* Parser::parseLogica() {
    Nodo* nodoIzquierdo = parseEXPand();
    if (nodoIzquierdo == nullptr) return nullptr;

    while (coincide(Tipo::OR)) {
        Token operadorToken = consumir(Tipo::OR);
        Nodo* nodoDerecho = parseEXPand();
        if (nodoDerecho == nullptr) {
            error("operando derecho faltante en ||");
            return nodoIzquierdo;
        }

        Nodo* operadorNodo = new Nodo(operadorToken.getValor(), TipoN::BINARIA);
        operadorNodo->agregarHijito(nodoIzquierdo);
        operadorNodo->agregarHijito(nodoDerecho);
        nodoIzquierdo = operadorNodo;
    }
    return nodoIzquierdo;
}

Nodo* Parser::parseEXPand() {
    Nodo* nodoIzquierdo = parseEXPnot();
    if (nodoIzquierdo == nullptr) return nullptr;

    while (coincide(Tipo::AND)) {
        Token operadorToken = consumir(Tipo::AND);
        Nodo* nodoDerecho = parseEXPnot();
        if (nodoDerecho == nullptr) {
            error("operando derecho faltante en &&");
            return nodoIzquierdo;
        }

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
        if (nodoDerecho == nullptr) {
            error("operando faltante despues de !");
            return nullptr;
        }
        Nodo* operadorNodo = new Nodo(operadorToken.getValor(), TipoN::UNARIA);
        operadorNodo->agregarHijito(nodoDerecho);
        return operadorNodo;
    } else {
        return parseRelacional();
    }
}

Nodo* Parser::parseRelacional() {
    Nodo* nodoIzquierdo = parseMatematica();
    if (nodoIzquierdo == nullptr) return nullptr;

    while (coincide(Tipo::IGUAL_IGUAL) || coincide(Tipo::DISTINTO) ||
           coincide(Tipo::MENOR) || coincide(Tipo::MAYOR) ||
           coincide(Tipo::MENOR_IGUAL) || coincide(Tipo::MAYOR_IGUAL)) {
        Token operadorToken = actual();
        avanzar();
        Nodo* nodoDerecho = parseMatematica();
        if (nodoDerecho == nullptr) {
            error("operando derecho faltante en operador relacional");
            return nodoIzquierdo;
        }

        Nodo* operadorNodo = new Nodo(operadorToken.getValor(), TipoN::BINARIA);
        operadorNodo->agregarHijito(nodoIzquierdo);
        operadorNodo->agregarHijito(nodoDerecho);
        nodoIzquierdo = operadorNodo;
    }
    return nodoIzquierdo;
}

Nodo* Parser::parseMatematica() {
    Nodo* nodoIzquierdo = parseTermino();
    if (nodoIzquierdo == nullptr) return nullptr;

    while (coincide(Tipo::MAS) || coincide(Tipo::MENOS)) {
        Token operadorToken = actual();
        avanzar();
        Nodo* nodoDerecho = parseTermino();
        if (nodoDerecho == nullptr) {
            error("operando derecho faltante en operador aritmetico");
            return nodoIzquierdo;
        }

        Nodo* operadorNodo = new Nodo(operadorToken.getValor(), TipoN::BINARIA);
        operadorNodo->agregarHijito(nodoIzquierdo);
        operadorNodo->agregarHijito(nodoDerecho);
        nodoIzquierdo = operadorNodo;
    }
    return nodoIzquierdo;
}

Nodo* Parser::parseTermino() {
    Nodo* nodoIzquierdo = parseUnario();
    if (nodoIzquierdo == nullptr) return nullptr;

    while (coincide(Tipo::POR) || coincide(Tipo::ENTRE)) {
        Token operadorToken = actual();
        avanzar();
        Nodo* nodoDerecho = parseUnario();
        if (nodoDerecho == nullptr) {
            error("operando derecho faltante en * o /");
            return nodoIzquierdo;
        }

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
        Nodo* nodoDerecho = parseUnario();
        if (nodoDerecho == nullptr) {
            error("operando faltante despues de operador unario");
            return nullptr;
        }
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
        if (!coincide(Tipo::PARENTESIS_CIERRA)) {
            error("se esperaba ) para cerrar la expresion");
            sincronizar();
        } else {
            consumir(Tipo::PARENTESIS_CIERRA);
        }
        return expresionNodo;
    } else {
        error("Factor no reconocido");
        return nullptr;
    }
}

vector<Nodo*> Parser::parseArgumentos() {
    vector<Nodo*> argumentos;//eps

    if (coincide(Tipo::PARENTESIS_CIERRA)) {
        return argumentos;
    }

    Nodo* argumento = parseExpresion();
    if (argumento != nullptr) argumentos.push_back(argumento);

    while (coincide(Tipo::COMA)) {
        consumir(Tipo::COMA);
        argumento = parseExpresion();
        if (argumento != nullptr) argumentos.push_back(argumento);
    }

    return argumentos;
}

void Parser::error(string mensaje) {
    errores.push_back(Error(TipoError::SINTACTICO,
        mensaje,
        actual().getLinea(), actual().getColumna()));
}

void Parser::sincronizar(){
    while(!coincide(Tipo::FIN_ARCHIVO)){
        if(coincide (Tipo::PUNTO_COMA)){
            avanzar();
            return;
        }
        if(coincide(Tipo::LLAVE_CIERRA)){
            return;
        }
        if (coincide(Tipo::FN) || coincide(Tipo::LET) || coincide(Tipo::IF) ||
            coincide(Tipo::WHILE) || coincide(Tipo::FOR) || coincide(Tipo::RETURN)) {
            return;
        }
        avanzar();

    }
}

TablaSimbolos& Parser::getTabla() {
    return tabla;
}