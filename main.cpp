#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Error.h"
using namespace std;

void traverse(Nodo* node, int depth = 0) {
    if (node == nullptr) return;
    for (int i = 0; i < depth; ++i) {
        cout << "  ";
    }
    cout << node->getValor() << " (" << nombreTipo(node->getTipo()) << ")" << endl;
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

    vector<Error> errores = lexer.getErrores();

    cout << "Tokens:" << endl;
    for (Token token : lexer.getTokens()) {
        cout << "Token: " << token.getValor() << " Tipo: " << nombreTipo(token.getTipo())
             << " (" << token.getLinea() << ":" << token.getColumna() << ")" << endl;
    }

    bool hayLexicos = false;
    for (Error& e : errores) {
        if (e.getTipo() == TipoError::LEXICO) hayLexicos = true;
    }

    if (hayLexicos) {
        cout << "\nErrores:" << endl;
        for (Error& e : errores) {
            cout << "[" << e.getTipoStr() << "] " << e.getMensaje()
                 << " (linea " << e.getLinea() << ", col " << e.getColumna() << ")" << endl;
        }
        cout << "Se encontraron errores lexicos, no se puede continuar con el analisis sintactico" << endl;
        return 1;
    }

    Parser parser(lexer.getTokens(), errores);
    Nodo* arbol = parser.parsear();

    if (!errores.empty()) {
        cout << "\nErrores:" << endl;
        for (Error& e : errores) {
            cout << "[" << e.getTipoStr() << "] " << e.getMensaje()
                 << " (linea " << e.getLinea() << ", col " << e.getColumna() << ")" << endl;
        }
    } else {
        cout << "\nNo se encontraron errores." << endl;
    }

    cout << "\nArbol sintactico:" << endl;
    traverse(arbol);

    delete arbol;
    return 0;
}