#include "Lexer.h"
#include "Transicion.h"
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;

Lexer::Lexer() {
    construirAutomata();
}

Lexer::~Lexer() {
    for (Estado* estado : estados) {
        delete estado;
    }
}

void Lexer::construirAutomata() {

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
    Estado *q12 = new Estado(true, Tipo::MENOS); //flecha1 / menos solo
    Estado *q13 = new Estado(true, Tipo::FLECHA); //flecha2
    Estado *q14 = new Estado(true, Tipo::MENOR);        //
    Estado *q15 = new Estado(true, Tipo::MENOR_IGUAL);  // <=
    Estado *q16 = new Estado(true, Tipo::MAYOR);        // >
    Estado *q17 = new Estado(true, Tipo::MAYOR_IGUAL);  // >=
    Estado *q18 = new Estado(true, Tipo::ASIGNACION);   // =
    Estado *q19 = new Estado(true, Tipo::IGUAL_IGUAL);  // ==
    Estado *q20 = new Estado(true, Tipo::NOT);          // !
    Estado *q21 = new Estado(true, Tipo::DISTINTO);     // !=
    Estado *q22 = new Estado(false, Tipo::NINGUNO);  // 3.
    Estado *q23 = new Estado(true,  Tipo::DECIMAL);  // 3.14
    Estado *q24 = new Estado(true,  Tipo::RANGO_FOR);    // 0..
    Estado *q25 = new Estado(false, Tipo::NINGUNO);  // .
    Estado *q26 = new Estado(true,  Tipo::RANGO_FOR);    // ..
    Estado *q27 = new Estado(false, Tipo::NINGUNO);  // '
    Estado *q28 = new Estado(false, Tipo::NINGUNO);  // 'a
    Estado *q29 = new Estado(true,  Tipo::CARACTER); // 'a'

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
    q12->setNombre("q12");
    q13->setNombre("q13");
    q14->setNombre("q14");
    q15->setNombre("q15");
    q16->setNombre("q16");
    q17->setNombre("q17");
    q18->setNombre("q18");
    q19->setNombre("q19");
    q20->setNombre("q20");
    q21->setNombre("q21");
    q22->setNombre("q22");
    q23->setNombre("q23");
    q24->setNombre("q24");
    q25->setNombre("q25");
    q26->setNombre("q26");
    q27->setNombre("q27");
    q28->setNombre("q28");
    q29->setNombre("q29");

    //transiciones q0 hacia ___
    Transicion letra(regex("[A-Za-z_]"), q1);
    q0->agregarTransicion(&letra);

    Transicion numero(regex("[0-9]"), q2);
    q0->agregarTransicion(&numero);

    Transicion simbolo(regex("[;+*(){}[\\]:,=]"), q3);
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

    Transicion flecha1(regex("-"), q12);
    q0->agregarTransicion(&flecha1);

    Transicion menor(regex("<"),q14);
    q0->agregarTransicion(&menor);

    Transicion mayor(regex(">"), q16);
    q0->agregarTransicion(&mayor);

    Transicion asignacion(regex("="), q18);
    q0->agregarTransicion(&asignacion);

    Transicion negacion(regex("!"), q20);
    q0->agregarTransicion(&negacion);

    Transicion punto1(regex("\\."), q25);
    q0->agregarTransicion(&punto1);

    Transicion comillaSola1(regex("'"), q27);
    q0->agregarTransicion(&comillaSola1);
    //transiciones q0 hacia ___

    //transiciones q1 hacia ___
    Transicion identificador(regex("[A-Za-z0-9_]"), q1);
    q1->agregarTransicion(&identificador);
    //transiciones q1 hacia ___

    //transiciones q2 hacia__
    Transicion digito(regex("[0-9]"), q2);
    q2->agregarTransicion(&digito);

    Transicion punto(regex("\\."), q22);
    q2->agregarTransicion(&punto);
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

    //trancisiones q12 hacia__
    Transicion flecha2(regex(">"), q13);
    q12->agregarTransicion(&flecha2);
    //trancisiones q12 hacia__

    //transiciones q14 hacia__
    Transicion menorIgual(regex("="),q15);
    q14->agregarTransicion(&menorIgual);
    //transiciones q14 hacia__

    //transiciones q16 hacia__
    Transicion mayorIgual(regex("="), q17);
    q16->agregarTransicion(&mayorIgual);
    //transiciones q16 hacia__

    //transiciones q18 hacia__
    Transicion igualIgual(regex("="), q19);
    q18->agregarTransicion(&igualIgual);
    //transiciones q18 hacia__

    //transiciones q20 hacia__
    Transicion distinto(regex("="), q21);
    q20->agregarTransicion(&distinto);
    //transiciones q20 hacia__

    //transiciones q22 hacia__
    Transicion decimal(regex("[0-9]"), q23);
    q22->agregarTransicion(&decimal);

    Transicion numRango(regex("\\."), q24);
    q22->agregarTransicion(&numRango);
    //transiciones q22 hacia__

    //transiciones q23 hacia__
    q23->agregarTransicion(&decimal);
    //transiciones q23 hacia__

    //transiciones q25 hacia__
    Transicion punto2(regex("\\."), q26);
    q25->agregarTransicion(&punto2);
    //transiciones q25 hacia__

    //transiciones q27 hacia__
    Transicion letraChar(regex(R"([^'\\\n])"), q28);
    q27->agregarTransicion(&letraChar);
    //transiciones q27 hacia__

    //transiciones q28 hacia__
    Transicion comillaSola2(regex("'"), q29);
    q28->agregarTransicion(&comillaSola2);
    //transiciones q28 hacia__

    estados = { q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14,
                q15, q16, q17, q18, q19, q20, q21, q22, q23, q24, q25, q26, q27, q28, q29 };

    automata = Automata(q0);
}

bool Lexer::cargarArchivo(string ruta, string &codigo) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    stringstream buffer;
    buffer << archivo.rdbuf();
    codigo = buffer.str();
    archivo.close();

    return true;
}

void Lexer::analizar(string codigo) {
    for (char caracter : codigo) {
        automata.avanzar(caracter);
    }
    automata.finalizar();
}

vector<Token> Lexer::getTokens() {
    return automata.getTokens();
}

vector<string> Lexer::getErrores() {
    return automata.getErrores();
}
