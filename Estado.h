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

    public:
        Estado();
        Estado(bool aceptacion);
        Estado(bool aceptacion, bool todoLeido);
        void agregarTransicion(Transicion* transicion);
        bool isAceptacion();
        bool isTodoLeido();
        vector<Transicion*> getTransiciones();
        Estado* getSiguiente(char caracter);
};
