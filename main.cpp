#include <iostream>
#include <regex>
using namespace std;
#include "Automata.h"
#include "Estado.h"
#include "Transicion.h"


int main(){

    string codigo = "let temp = boli;";
    Estado *q0 = new Estado(false);
    Estado *q1 = new Estado(true);//ide
    Estado *q2 = new Estado(true);//num
    Estado *q3 = new Estado(true);//simb


    q0->setNombre("q0");
    q1->setNombre("q1");
    q2->setNombre("q2");
    q3->setNombre("q3");

    //transiciones q0 hacia ___ 
    Transicion letra(regex("[A-Za-z]"), q1);
    q0->agregarTransicion(&letra);

   Transicion numero(regex("[0-9]"), q2);
   q0->agregarTransicion(&numero);

    Transicion simbolo(regex("[;=+\\-*/(){}[\\]:,!<>&|]"), q3);
    q0->agregarTransicion(&simbolo);


    //transiciones q1 hacia ___ 

   Transicion identificador(regex("[A-Za-z0-9_]"), q1);
   q1->agregarTransicion(&identificador);

    //transiciones q2 hacia__
    Transicion digito(regex("[0-9]"), q2);
    q2->agregarTransicion(&digito);

   cout<<"codigo: "<<codigo<<endl;
    Automata automata(q0); 


    for (char caracter : codigo) {
        automata.avanzar(caracter);
        cout<<caracter
        <<" estado actual: " << automata.getActual()->getNombre() << 
        " lexema: " << automata.getLexema() << endl;
    }

     if (!automata.getLexema().empty()) {
        automata.reiniciar();
    }

    cout<<"Tokens:"<<endl;
    for (Token token : automata.getTokens()) {
        cout<<"Token: "<< token.getValor() << " Tipo: " << token.getTipo() << endl;
    }
    
     delete q0;
    delete q1;
    delete q2;
    delete q3;

}
