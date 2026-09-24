#include "Nodo.h"

Nodo::Nodo(string valor, TipoN tipo) : tipo(tipo) , valor(valor){}

TipoN Nodo::getTipo() {
    return tipo;
}

string Nodo::getValor() {
    return valor;
}

vector<Nodo*> Nodo::getHijitos() {
    return hijitos;
}

void Nodo::agregarHijito(Nodo* hijito){
    hijitos.push_back(hijito);  
}

Nodo::~Nodo() {
    for (Nodo* hijo : hijitos) {
        delete hijo;
    }
}