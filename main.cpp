#include <iostream>
#include <regex>
using namespace std;
#include "Automata.h"
#include "Estado.h"
#include "Transicion.h"


int main(){

    string codigo = "let temp = b;";
    Estado *q0 = new Estado(false);
    Estado *q1 = new Estado(true);//ide
    Estado *q2 = new Estado(true);//num

    q0->setNombre("q0");
    q1->setNombre("q1");
    q2->setNombre("q2");


    Transicion letra(regex("[A-Za-z]"), q1);
    q0->agregarTransicion(&letra);

   Transicion numero(regex("[0-9]"), q2);
   q0->agregarTransicion(&numero);

   Transicion letra2(regex("[A-Za-z0-9_]"), q1);
   q1->agregarTransicion(&letra2);

   cout<<"codigo: "<<codigo<<endl;
    Automata automata(q0); 
    automata.agregarEstados(q0);
    automata.agregarEstados(q1);



    for (char caracter : codigo) {
        automata.avanzar(caracter);
        cout<<caracter
        <<" estado actual: " << automata.getActual()->getNombre() << 
        " lexema: " << automata.getLexema() << endl;
    }

    automata.reiniciar();

    cout<<"Tokens:"<<endl;
    for (Token token : automata.getTokens()) {
        cout<<"Token: "<< token.getValor() << " Tipo: " << token.getTipo() << endl;
    }
    
     delete q0;
    delete q1;
    delete q2;

}
