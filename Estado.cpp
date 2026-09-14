#include <iostream>
#include "Estado.h"
#include "Transicion.h"

Estado::Estado() {
    this->aceptacion = false;
    this->nombre = "";
    this->tipo = Tipo::NINGUNO;
}

Estado::Estado(bool aceptacion, Tipo tipo) {
    this->aceptacion = aceptacion;
    this->nombre = "";
    this->tipo = tipo;
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


bool Estado::isAceptacion() {
    return aceptacion;
}

void Estado::setNombre(string nombre) {
    this->nombre = nombre;
}

string Estado::getNombre() {
    return nombre;
}

Tipo Estado::getTipo() {
    return tipo;
}
