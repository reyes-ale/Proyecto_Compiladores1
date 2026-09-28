#include <iostream>
#include "Lexer.h"
#include "Parser.h"
using namespace std;

void traverse(Nodo* node, int depth = 0) {
    for (int i = 0; i < depth; ++i) {
        cout << "  "; // Indentación
    }
    cout << node->getValor() << " (" << static_cast<int>(node->getTipo()) << ")" << endl;
    for (Nodo* child : node->getHijitos()) {
        traverse(child, depth + 1);
    }
}

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
    if (errores.size()>0){
        cout << "Se encontraron errores lexicos, no se puede continuar con el analisis sintactico" << endl;
        return 1;
    }

    Parser parser(lexer.getTokens());
    Nodo* arbol = parser.parsear();
    traverse(arbol);
    return 0;
}


