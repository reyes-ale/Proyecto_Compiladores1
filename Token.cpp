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

string Token::getValor(){
    return valor;
}

Tipo Token::getTipo(){
    return tipo;
}