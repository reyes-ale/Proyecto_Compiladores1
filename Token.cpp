#include "Token.h"

Token::Token(){
    this->valor = "";
    this->tipo = "";
}

Token::Token(string valor, string tipo){
    this->valor = valor;
    this->tipo = tipo;
}