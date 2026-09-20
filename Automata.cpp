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
            Tipo tipo = tipoToken(lexema, estadoActual);
            if(tipo==Tipo::RANGO_FOR && lexema.size()>2){
                tokensitos.push_back(Token(lexema.substr(0, lexema.size()-2), Tipo::ENTERO, lineaInicio, colInicio));
                tokensitos.push_back(Token("..", Tipo::RANGO_FOR, lineaInicio, colInicio + (int)lexema.size() - 2));

            }
            else if(tipo != Tipo::COMENTARIO){
                Token token (lexema,tipo,lineaInicio, colInicio);
                tokensitos.push_back(token);
            }
            else{
                errores.push_back("error " + lexema);
            }
        }
        lexema="";
        estadoActual = estadoInicial;
        
    }

   
}

void Automata::avanzar(char caracter){
    Transicion* transicion = estadoActual->getTransicion(caracter);

    if(transicion == nullptr){
       
            reiniciar();

            transicion = estadoActual->getTransicion(caracter);
            if(transicion == nullptr){
                errores.push_back("desconocido: " + caracter);
                moverPos(caracter);
                return;
            }
    }

    estadoActual = transicion->getSiguiente();
    if(!transicion->isDescarta()) {
        if(lexema.empty()){
            lineaInicio = linea;
            colInicio = columna;
        }
         lexema+=caracter;
    }
    moverPos(caracter);
   
}

Estado* Automata::getActual(){
    return estadoActual;
}

void Automata:: finalizar(){
    reiniciar();
        tokensitos.push_back(Token("$", Tipo::FIN_ARCHIVO,linea, columna));// fin de archv
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

void Automata::moverPos(char caracter){
    if(caracter == '\n'){
        linea++;
        columna=1;
    }
    else{
        columna++;
    }
}


