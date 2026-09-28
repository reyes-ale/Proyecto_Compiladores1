#include "TablaSimbolos.h"
#include <iostream>
using namespace std;

TablaSimbolos::TablaSimbolos() {}

void TablaSimbolos::insertar(string nombre, string tipo) {
    int pos = simbolos.size();
    simbolos.push_back(Simbolo(nombre, tipo, pos));
}

void TablaSimbolos::imprimir() {
    cout << "\n Tabla de Simbolos:" << endl;
    cout << "Id\tLexema\t\tTipo" << endl;
    cout << "---\t------\t\t----" << endl;
    for (Simbolo& s : simbolos) {
        cout << s.getPosicion() << "\t" << s.getNombre() << "\t\t";
        if (s.getTipo().empty()) {
            cout << " ";
        } else {
            cout << s.getTipo();
        }
        cout << endl;
    }
}

int TablaSimbolos::size() {
    return simbolos.size();
}