#include <iostream>
#include <regex>
using namespace std;
#include "Automata.h"
#include "Estado.h"
#include "Transicion.h"
#include <fstream>
#include <sstream>


int main(int argc, char* argv[]){

    string ruta = "prueba.rs";
    if(argc>1){
        ruta = argv[1];
    }

    ifstream archivo(ruta);
    if(!archivo.is_open()){
        cout<<"No se pudo abrir el archivo: "<<ruta<<endl;
        return 1;
    }

    stringstream buffer;
    buffer << archivo.rdbuf();
    string codigo = buffer.str();
    archivo.close();

    Estado *q0 = new Estado(false, Tipo::NINGUNO);
    Estado *q1 = new Estado(true,  Tipo::IDENTIFICADOR);//ide
    Estado *q2 = new Estado(true,  Tipo::ENTERO);//num
    Estado *q3 = new Estado(true,  Tipo::NINGUNO);//simb
    Estado *q4 = new Estado(false, Tipo::NINGUNO);//and1
    Estado *q5 = new Estado(true,  Tipo::NINGUNO);//and2
    Estado *q6 = new Estado(false, Tipo::NINGUNO);//or1
    Estado *q7 = new Estado(true,  Tipo::NINGUNO);//or2
    Estado *q8 = new Estado(false, Tipo::NINGUNO);//comilla de string
    Estado *q9 = new Estado(true,  Tipo::CADENA);//cierra string
    Estado *q10 = new Estado(true, Tipo::NINGUNO); //1 pleca 
    Estado *q11 = new Estado(true, Tipo::COMENTARIO); //2 pleca comment


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
    q10->setNombre("q10");
    q11->setNombre("q11");

    //transiciones q0 hacia ___  
    Transicion letra(regex("[A-Za-z_]"), q1);
    q0->agregarTransicion(&letra);

    Transicion numero(regex("[0-9]"), q2);
    q0->agregarTransicion(&numero);

    Transicion simbolo(regex("[;=+\\-*(){}[\\]:,!<>]"), q3);
    q0->agregarTransicion(&simbolo);

    Transicion and1(regex("\\&"), q4);
    q0->agregarTransicion(&and1);

    Transicion or1(regex("\\|"), q6);
    q0->agregarTransicion(&or1);

    Transicion comilla1(regex("\""), q8);
    q0->agregarTransicion(&comilla1);

    Transicion espacio(regex("\\s"), q0, true); 
    q0->agregarTransicion(&espacio);

    Transicion barra(regex("/"), q10);
    q0->agregarTransicion(&barra);

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
    Transicion contenido(regex("[^\"\\n]"), q8);
    q8->agregarTransicion(&contenido);

    Transicion comilla2(regex("\""), q9);
    q8->agregarTransicion(&comilla2);

    //transiciones q8 hacia__



     //transiciones q10 hacia__

    Transicion barra2(regex("/"), q11);
    q10->agregarTransicion(&barra2);

    //transiciones q10 hacia__


    //transiciones q11 hacia__
    Transicion textoComentario(regex("[^\\n]"), q11);
    q11->agregarTransicion(&textoComentario);

    //transiciones q11 hacia__




    Automata automata(q0); 
    bool residuo = false;

    cout << "analisis de: " << ruta << endl;

    for (char caracter : codigo) {
        automata.avanzar(caracter);
        if(residuo){
              cout<<caracter
            <<" estado actual: " << automata.getActual()->getNombre() << 
            " lexema: " << automata.getLexema() << endl;
        }

    }

    automata.finalizar();

    cout<<"Tokens:"<<endl;
    for (Token token : automata.getTokens()) {
        cout<<"Token: "<< token.getValor() << " Tipo: " << nombreTipo(token.getTipo()) << endl;  
  }
    
    delete q0;
    delete q1;
    delete q2;
    delete q3;
    delete q4;
    delete q5;
    delete q6;
    delete q7;
    delete q8;
    delete q9;
    delete q10;
    delete q11;

}
