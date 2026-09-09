#include "Automata.h"
#include "Transicion.h"
#include "Estado.h"
#include "Diccionario.h"
#include <iostream>
#include <vector>
#include <regex>
using namespace std;

Automata::Automata() {
    estadoInicial = nullptr;
    estadoActual = nullptr;
}

Automata::Automata(Estado* estadoInicial) {
    this->estadoActual = estadoInicial;
    this->estadoInicial = estadoInicial;

}

void Automata::agregarEstados(Estado* estado){
    estados.push_back(estado);
}

void Automata::reiniciar(){//volver a q0
    if(estadoActual != nullptr && estadoActual->isTodoLeido()){
        //Token nuevo = new Token (lexema, tipodeTokenquesevaasacardelamulelistadetiposdetokensquehayoesocreemospormientrasporloquedespueslopensaremosmejor)
        //tokensitos.add(nuevo);
        if(estadoActual->isAceptacion()){
            Token token (lexema,tipoToken(lexema));
            tokensitos.push_back(token);
        }
        lexema="";
        estadoActual = estadoInicial;
        
    }
    else{
        if(estadoActual!=nullptr){
            estadoActual->setTodoLeido(true);
        }
        lexema="";
        estadoActual = estadoInicial;
    }
    if(estadoActual!=nullptr){
        estadoActual->setTodoLeido(false);
    }
}

void Automata::avanzar(char caracter){
    if(caracter==' ' || caracter=='\n' || caracter=='\t') { //fin
        if(estadoActual != nullptr && estadoActual->isAceptacion()){
            estadoActual->setTodoLeido(true); 
        }
        reiniciar();
        return;
    }  

    Estado* siguiente = estadoActual->getSiguiente(caracter);

    if(siguiente == nullptr){
        if (estadoActual != nullptr && estadoActual->isAceptacion()){
            estadoActual->setTodoLeido(true);
            reiniciar();

            siguiente = estadoActual->getSiguiente(caracter);
            if(siguiente != nullptr){
                estadoActual = siguiente;
                lexema+=caracter;
            }
            return;
        }
    }

    if(siguiente != nullptr){
            estadoActual = siguiente;
            lexema+=caracter;

    }

    
    
}

Estado* Automata::getActual(){
    return estadoActual;
}

string Automata::tipoToken(string lexema){

    Diccionario reservadas;
    string tipo_reservadas = reservadas.buscar(lexema);

    if(!tipo_reservadas.empty()){
        return tipo_reservadas; 
    }

    if(regex_match(lexema, regex("[a-zA-Z_][a-zA-Z0-9_]*"))){
        return "identificador";
    }

    if(regex_match(lexema, regex("[0-9]+"))){
        return "numero";
    }

    if(regex_match(lexema, regex("[0-9]+\\.[0-9]+"))){
        return "decimal";
    }

    if(regex_match(lexema, regex("\"[^\"]*\""))){
        return "cadena";
    }

    return "ninguno";

}


string Automata::getLexema(){
        return lexema;
}

vector<Token> Automata::getTokens(){
    return tokensitos;
}

