#include <iostream>
#include "Estado.h"
#include "Transicion.h"

Estado::Estado() {
    this->aceptacion = false;
    this->todoLeido = false;
    this->nombre = "";
}

void Estado::agregarTransicion(Transicion* transicion) {
    transiciones.push_back(*transicion);
}

vector<Transicion> Estado::getTransiciones() {
    return transiciones;
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
    this->aceptacion = aceptacion;
    this->todoLeido = false;
    this->nombre = "";
}

void Estado::setTodoLeido(bool todoLeido) {
    this->todoLeido = todoLeido;
}
    
bool Estado::isTodoLeido() {
    return todoLeido;
}

bool Estado::isAceptacion() {
    return aceptacion;
}

void Estado::setNombre(string nombre) {
    this->nombre = nombre;
}

string Estado::getNombre() {
    return nombre;
}
