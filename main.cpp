#include <iostream>
#include <regex>
using namespace std;
#include "Automata.h"
#include "Estado.h"
#include "Transicion.h"


int main(){

    string codigo = "peep_ if for else + - { } && & || | ppeper _2djvc \"peep\" ";
    Estado *q0 = new Estado(false);
    Estado *q1 = new Estado(true);//ide
    Estado *q2 = new Estado(true);//num
    Estado *q3 = new Estado(true);//simb
    Estado *q4 = new Estado(false);//and1
    Estado *q5 = new Estado(true);//and2
    Estado *q6 = new Estado(false);//or1
    Estado *q7 = new Estado(true);//or2
    Estado *q8 = new Estado(false);//comilla de string
    Estado *q9 = new Estado(true);//cierra string


    q0->setNombre("q0");
    q1->setNombre("q1");
    q2->setNombre("q2");
    q3->setNombre("q3");
    q4->setNombre("q4");
    q5->setNombre("q5");
    q6->setNombre("q6");
    q7->setNombre("q7");
    q8->setNombre("q8");
    q9->setNombre("q9");    

    //transiciones q0 hacia ___  
    Transicion letra(regex("[A-Za-z_]"), q1);
    q0->agregarTransicion(&letra);

    Transicion numero(regex("[0-9]"), q2);
    q0->agregarTransicion(&numero);

    Transicion simbolo(regex("[;=+\\-*/(){}[\\]:,!<>]"), q3);
    q0->agregarTransicion(&simbolo);

    Transicion and1(regex("\\&"), q4);
    q0->agregarTransicion(&and1);

    Transicion or1(regex("\\|"), q6);
    q0->agregarTransicion(&or1);

    Transicion comilla1(regex("\""), q8);
    q0->agregarTransicion(&comilla1);

    //transiciones q0 hacia ___  


    //transiciones q1 hacia ___  
    Transicion identificador(regex("[A-Za-z0-9_]"), q1);
    q1->agregarTransicion(&identificador);

    //transiciones q1 hacia ___  

    //transiciones q2 hacia__
    Transicion digito(regex("[0-9]"), q2);
    q2->agregarTransicion(&digito);

    //transiciones q2 hacia ___  


    //trancisiones q4 hacia __
    Transicion and2(regex("\\&"), q5);
    q4->agregarTransicion(&and2);
     //trancisiones q4 hacia __

    //trancisiones q6 hacia __
    Transicion or2(regex("\\|"), q7);
    q6->agregarTransicion(&or2);
    //trancisiones q6 hacia __

    //transiciones q8 hacia__
    Transicion contenido(regex("[A-Za-z0-9 &+\\-*/_=<>!{}()[\\]:,]"), q8);
    q8->agregarTransicion(&contenido);

    Transicion comilla2(regex("\""), q9);
    q8->agregarTransicion(&comilla2);

    //transiciones q8 hacia__

     



   cout<<"codigo: "<<codigo<<endl;
    Automata automata(q0); 


    for (char caracter : codigo) {
        automata.avanzar(caracter);
        cout<<caracter
        <<" estado actual: " << automata.getActual()->getNombre() << 
        " lexema: " << automata.getLexema() << endl;
    }

     if (!automata.getLexema().empty()) {
        automata.getActual()->setTodoLeido(true);
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
