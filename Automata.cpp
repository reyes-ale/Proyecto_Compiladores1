#include "Automata.h"
#include "Transicion.h"
#include "Estado.h"
#include <iostream>
#include <vector>
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
    if(estadoActual->isTodoLeido() && estadoActual!=nullptr){
        //Token nuevo = new Token (lexema, tipodeTokenquesevaasacardelamulelistadetiposdetokensquehayoesocreemospormientrasporloquedespueslopensaremosmejor)
        //tokensitos.add(nuevo);
        Token token (lexema,tipoToken(lexema));
        tokensitos.push_back(token);
        lexema="";
        estadoActual = estadoInicial;
    }else{
        lexema="";
        estadoActual = estadoInicial;
    }

    estadoActual->setTodoLeido(false);
}

void Automata::avanzar(char caracter){
    if(caracter==' ' || caracter=='\n' || caracter=='\t'){ //fin
       
        if(estadoActual->isAceptacion() && estadoActual!=nullptr){
            estadoActual->setTodoLeido(true); 
        }

        reiniciar();
        return;

    }  
    
    lexema+=caracter;
    Estado* siguiente = estadoActual->getSiguiente(caracter);

    if(siguiente != nullptr){
        estadoActual = siguiente;
    }

    /*if(isalpha(caracter)){
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

string Automata::tipoToken(string lexema){

    if(lexema =="let" || lexema=="fn" || lexema=="if" || lexema=="else" || lexema=="while" || lexema=="return"){
        return "reservada";
    }

    if(lexema=="i32"|| lexema=="f64" || lexema=="bool" || lexema=="char" || lexema=="str"){
        return "tipo";
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

    //simbolosnosesidividrunoporunooconunsoloregex
    return "ninguno";

}


string Automata::getLexema(){
        return lexema;
}

vector<Token> Automata::getTokens(){
    return tokensitos;
}