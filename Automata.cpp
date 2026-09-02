#include "Automata.h"
#include "Transicion.h"
#include "Estado.h"
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
    if(estadoActual->isTodoLeido() && estadoActual!=nullptr){
        //Token nuevo = new Token (lexema, tipodeTokenquesevaasacardelamulelistadetiposdetokensquehayoesocreemospormientrasporloquedespueslopensaremosmejor)
        //tokensitos.add(nuevo);
        if(estadoActual->isAceptacion() && estadoActual!=nullptr){
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
    if(caracter==' ' || caracter=='\n' || caracter=='\t'){ //fin
       
        if(estadoActual->isAceptacion() && estadoActual!=nullptr){
            estadoActual->setTodoLeido(true); 
        }

        reiniciar();
        return;

    }  

    if(esSimbolo(caracter)){ //fin
       
        if(estadoActual->isAceptacion() && estadoActual!=nullptr){
            if(!(lexema.empty())){
                Token token(lexema, tipoToken(lexema));
                tokensitos.push_back(token);
            }
            lexema = "";
        }

        string str (1,caracter);
        Token token(str, tipoToken(str));
        tokensitos.push_back(token);

        reiniciar();
        return;

    }  


    lexema+=caracter;
    if(estadoActual!=nullptr){
            Estado* siguiente = estadoActual->getSiguiente(caracter);
            if(siguiente != nullptr){
                 estadoActual = siguiente;
            }

    }

    
    
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

    if(lexema == ";") return "punto_y_coma";
    if(lexema == ",") return "coma";
    if(lexema == ":") return "dos_puntos";
    if(lexema == "=") return "asignacion";
     if(lexema == "+") return "suma";
    if(lexema == "-") return "resta";
    if(lexema == "*") return "multiplicacion";
    if(lexema == "/") return "division";
    if(lexema == "(") return "paren_abre";
    if(lexema == ")") return "paren_cierra";
    if(lexema == "{") return "llave_abre";
    if(lexema == "}") return "llave_cierra";
    if(lexema == "[") return "corchete_abre";
    if(lexema == "]") return "corchete_cierra";
    if(lexema == "<") return "menor";
    if(lexema == ">") return "mayor";
    

    //simbolosnosesidividrunoporunooconunsoloregex
    return "ninguno";

}


string Automata::getLexema(){
        return lexema;
}

vector<Token> Automata::getTokens(){
    return tokensitos;
}

bool Automata::esSimbolo(char caracter){
   string str(1,caracter);
    return regex_match(str,regex("[;=+\\-*/(){}[\\]:,!<>&|]"));
}