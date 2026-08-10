#include <iostream>
using namespace std;
#include "Transicion.h"

#include <vector>

class Estado {
    private:
        vector<Transicion> transiciones; 

    public:
        Estado();
        void agregarTransicion(Transicion* transicion);
        vector<Transicion*> getTransiciones();
        Estado* getSiguiente(char caracter);
};
