#include "Simbolo.h"

Simbolo::Simbolo() {
    this->nombre = "";
    this->tipo = "";
    this->posicion = 0;
}

Simbolo::Simbolo(string nombre, string tipo, int posicion) {
    this->nombre = nombre;
    this->tipo = tipo;
    this->posicion = posicion;
}

string Simbolo::getNombre() {
    return nombre;
}

string Simbolo::getTipo() {
    return tipo;
}

int Simbolo::getPosicion() {
    return posicion;
}

void Simbolo::setTipo(string tipo) {
    this->tipo = tipo;
}