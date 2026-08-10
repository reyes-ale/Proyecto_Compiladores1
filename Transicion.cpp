#include "Transicion.h"
#include <iostream>
using namespace std;

Transicion::Transicion(regex patron, Estado* siguiente) {
    this->patron = patron;
    this->siguiente = siguiente;
}

bool Transicion::acepta(char caracter) {
    string str(1, caracter);
    bool match = regex_match(str, patron);
    
    return match;
}

Estado* Transicion::getSiguiente() {
    return siguiente;
}