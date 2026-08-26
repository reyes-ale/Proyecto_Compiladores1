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

    ///


}
