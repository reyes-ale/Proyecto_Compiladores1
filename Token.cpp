#include "Token.h"
#include "Estado.h"

Token::Token(){
    this->valor = "";
    this->tipo = Tipo::NINGUNO;
}

Token::Token(string valor, Tipo tipo){
    this->valor = valor;
    this->tipo = tipo;
}

Token::Token(string valor, Tipo tipo, int linea, int columna){
    this->valor = valor;
    this->tipo = tipo;
    this->linea = linea;
    this->columna = columna;
}


string Token::getValor(){
    return valor;
}

Tipo Token::getTipo(){
    return tipo;
}

int Token::getLinea(){
    return linea;
}

int Token::getColumna(){
    return columna;
}