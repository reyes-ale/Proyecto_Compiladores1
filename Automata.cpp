#include "Automata.h"
#include "Transicion.h"
#include "Estado.h"
#include <iostream>
using namespace std;

Automata::Automata(){
    
}

Automata::Automata() {
    estadoInicial = nullptr;
    estadoActual = nullptr;
}

Automata::Automata(Estado* estadoInicial) {
    estadoActual = estadoInicial;
}

void Automata::agregarEstados(Estado* estado){
    estados.add(estado);
}

void Automata::reiniciar(){
    if(estadoActual->isTodoLeido()){
        //Token nuevo = new Token (lexema, tipodeTokenquesevaasacardelamulelistadetiposdetokensquehayoesocreemospormientrasporloquedespueslopensaremosmejor)
        //tokensitos.add(nuevo);
        lexema="";
        estadoActual = estadoInicial;
    }
}

void Automata::avanzar(char caracter){
    lexema+=caracter;

    if(caracter.match(regex("[A-Za-z]"))){

    }
    else if(caracter.match(regex("[0-9]"))){

    }
    else if(caracter.match(regex("[+\-*/=!(),{}\[\];"))){

    }

}

Estado* Automata::getActual(){
    return estadoActual;
}