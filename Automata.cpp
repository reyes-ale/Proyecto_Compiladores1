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
    if(!lexema.empty()){
        //Token nuevo = new Token (lexema, tipodeTokenquesevaasacardelamulelistadetiposdetokensquehayoesocreemospormientrasporloquedespueslopensaremosmejor)
        //tokensitos.add(nuevo);
        if(estadoActual != nullptr && estadoActual->isAceptacion()){
            Token token (lexema,tipoToken(lexema,estadoActual));
            tokensitos.push_back(token);
        }
        lexema="";
        estadoActual = estadoInicial;
        
    }
}

void Automata::avanzar(char caracter){
    if(caracter==' ' || caracter=='\n' || caracter=='\t') { //fin
        reiniciar();
        return;
    }  

    Estado* siguiente = estadoActual->getSiguiente(caracter);

    if(siguiente == nullptr){
       
            reiniciar();

            siguiente = estadoActual->getSiguiente(caracter);
            if(siguiente == nullptr){
                errores.push_back("desconocido: " + caracter);
                return;
            }
    }

    estadoActual = siguiente;
    lexema+=caracter;

}

Estado* Automata::getActual(){
    return estadoActual;
}

void Automata:: finalizar(){
    reiniciar();
    tokensitos.push_back(Token("EOF", Tipo::NINGUNO));// fin si es archv
}


string Automata::getLexema(){
        return lexema;
}

vector<Token> Automata::getTokens(){
    return tokensitos;
}

vector<string> Automata::getErrores(){
    return errores;
}

Tipo Automata::tipoToken(string lexema, Estado* aceptacion){
    Tipo enTabla = reservadas.buscar(lexema);
    if(enTabla != Tipo::NINGUNO){
        return enTabla;
    } 
    return aceptacion->getTipo();
}


