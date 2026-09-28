#pragma once
#include <vector>
#include "Simbolo.h"
using namespace std;

class TablaSimbolos {
private:
    vector<Simbolo> simbolos;

public:
    TablaSimbolos();

    void insertar(string nombre, string tipo = "");
    void imprimir();
    int size();
};