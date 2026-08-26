#include <iostream>
#include "Estado.h"
#include "Transicion.h"

Estado::Estado() {

}

void Estado::agregarTransicion(Transicion* transicion) {
    transiciones.push_back(*transicion);
}

vector<Transicion*> Estado::getTransiciones() {
    vector<Transicion*> transicionesPtr;

    for (Transicion& transicion : transiciones) {
        transicionesPtr.push_back(&transicion);
    }

    return transicionesPtr;
}

Estado* Estado::getSiguiente(char caracter) {

    for (Transicion& transicion : transiciones) {
        if (transicion.acepta(caracter)) {
            return transicion.getSiguiente();
        }
    }

    return nullptr;
}

Estado:: Estado(bool aceptacion) {
    
}

bool Estado::isTodoLeido() {
    return todoLeido;
}