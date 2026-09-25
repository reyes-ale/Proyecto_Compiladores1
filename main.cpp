#include <iostream>
#include "Lexer.h"
using namespace std;

int main(int argc, char* argv[]){

    string ruta;

    if(argc>1){
        ruta = argv[1];
    } else {
        cout << "=== Analizador Lexico ===" << endl;
        cout << "Ingrese la ruta del archivo .rs a analizar: ";
        getline(cin, ruta);
    }

    if(ruta.size() < 3 || ruta.substr(ruta.size()-3) != ".rs"){
        cout << "Advertencia: el archivo indicado no tiene extension .rs" << endl;
    }

    Lexer lexer;
    string codigo;
    if(!lexer.cargarArchivo(ruta, codigo)){
        cout << "No se pudo abrir el archivo: " << ruta << endl;
        return 1;
    }

    cout << "analisis de: " << ruta << endl;
    lexer.analizar(codigo);

    cout << "Tokens:" << endl;
    for (Token token : lexer.getTokens()) {
        cout << "Token: " << token.getValor() << " Tipo: " << nombreTipo(token.getTipo())
             << " (" << token.getLinea() << ":" << token.getColumna() << ")" << endl;
    }

    vector<string> errores = lexer.getErrores();
    if(!errores.empty()){
        cout << "Errores:" << endl;
        for (string error : errores) {
            cout << error << endl;
        }
    }

    return 0;
}
