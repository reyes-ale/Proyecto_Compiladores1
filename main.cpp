#include <iostream>
#include <regex>
using namespace std;
#include "Automata.h"


int main(){

    string codigo = "let temp = b;";
    Estado *inicial = new Estado(false);
    Estado *letra = new Estado(true);
    Estado *espacioFinal = new Estado(true);
    Transicion letraLeida(regex("[A-Za-z]"), letra);
    Automata automata(inicial); 
    automata.agregarEstados(inicial);
    automata.agregarEstados(letra);
    automata.agregarEstados(espacioFinal);


    inicial->agregarTransicion(&letraLeida);

    for (char caracter : codigo) {
        automata.avanzar(caracter);
        cout<<caracter<<endl;
    }

    ///


}
