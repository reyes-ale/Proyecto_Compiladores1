#pragma once

#include <iostream>
#include <regex>
using namespace std;
class Estado;


class Transicion {
    private:
        Estado* siguiente;
        regex patron; 
        bool descarta;

    public:
        Transicion(regex patron, Estado* siguiente);
        Transicion(regex patron, Estado* siguiente, bool descarta);
        Estado* getSiguiente();
        bool acepta (char caracter);
        bool isDescarta();
}; 