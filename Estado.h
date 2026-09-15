#pragma once

#include <iostream>
using namespace std;
#include "Transicion.h"
#include "Diccionario.h"


#include <vector>

class Estado {
    private:
        vector<Transicion> transiciones;
        bool aceptacion;
        string nombre; 
        Tipo tipo;

    public:
        Estado();
        Estado(bool aceptacion);
         Estado(bool aceptacion, Tipo tipo);
        Estado(bool aceptacion, bool todoLeido);
        void agregarTransicion(Transicion* transicion);
        bool isAceptacion();
        void setNombre(string nombre);
        string getNombre();
        vector<Transicion> getTransiciones();
        Estado* getSiguiente(char caracter);
        void setTodoLeido(bool todoLeido);
        Tipo getTipo();
        Transicion* getTransicion(char caracter);
};
