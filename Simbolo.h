#pragma once
#include <string>
using namespace std;

class Simbolo {
private:
    string nombre;
    string tipo;
    int posicion;

public:
    Simbolo();
    Simbolo(string nombre, string tipo, int posicion);

    string getNombre();
    string getTipo();
    int getPosicion();

    void setTipo(string tipo);
};