#include "Automata.h"
#include "Transicion.h"
#include "Estado.h"
#include <iostream>
using namespace std;

Automata::Automata() {
    estadoInicial = nullptr;
    estadoActual = nullptr;
}

Automata::Automata(Estado* estadoInicial) {
    estadoActual = estadoInicial;
}

void Automata::agregarEstados(Estado* estado){
    estados.push_back(estado);
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

    if(isalpha(caracter)){
        cout <<"escarac"<<endl;


    }
    else if(isdigit(caracter)){
        cout<<"esnum"<<endl;
    }
    /*else if(caracter.match(regex("[+\-=!(),{}\[\];"))){

    }
    */

}

Estado* Automata::getActual(){
    return estadoActual;
}
