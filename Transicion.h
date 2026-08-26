#pragma once

#include <iostream>
#include <regex>
using namespace std;
class Estado;


class Transicion {
    private:
        Estado* siguiente;
        regex patron; 

    public:
        Transicion(regex patron, Estado* siguiente);
        Estado* getSiguiente();
        bool acepta (char caracter);
}; 