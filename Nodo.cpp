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

string nombreTipo(TipoN tipo){
    switch(tipo){
        case TipoN::PROGRAMA: return "PROGRAMA";
        case TipoN::FUNCION: return "FUNCION";
        case TipoN::PARAMETRO: return "PARAMETRO";
        case TipoN::DECLARACION: return "DECLARACION";
        case TipoN::ASIGNACION: return "ASIGNACION";
        case TipoN::CONDICION: return "CONDICION";
        case TipoN::BUCLE_WHILE: return "BUCLE_WHILE";
        case TipoN::BUCLE_FOR: return "BUCLE_FOR";
        case TipoN::RANGO: return "RANGO";
        case TipoN::RETORNO: return "RETORNO";
        case TipoN::BINARIA: return "BINARIA";
        case TipoN::UNARIA: return "UNARIA";
        case TipoN::LLAMADA: return "LLAMADA";
        case TipoN::IDENTIFICADOR: return "IDENTIFICADOR";
        case TipoN::ENTERO: return "ENTERO";
        case TipoN::DECIMAL: return "DECIMAL";
        case TipoN::CADENA: return "CADENA";
        case TipoN::CARACTER: return "CARACTER";
        case TipoN::BOOLEANO: return "BOOLEANO";
        case TipoN::FIN_ARCHIVO: return "FIN_ARCHIVO";
    }
    return "NOIDEF";
}