#pragma once

#include <iostream>
using namespace std;
#include "Transicion.h"

#include <vector>

class Estado {
    private:
        vector<Transicion> transiciones;
        bool aceptacion;
        bool todoLeido;
        string nombre; 

    public:
        Estado();
        Estado(bool aceptacion);
        Estado(bool aceptacion, bool todoLeido);
        void agregarTransicion(Transicion* transicion);
        bool isAceptacion();
        bool isTodoLeido();
        void setNombre(string nombre);
        string getNombre();
        vector<Transicion> getTransiciones();
        Estado* getSiguiente(char caracter);
        void setTodoLeido(bool todoLeido);
};
