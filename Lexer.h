#pragma once

#include <string>
#include <vector>
#include "Automata.h"
#include "Estado.h"
#include "Token.h"
using namespace std;

class Lexer {
    private:
        vector<Estado*> estados;
        Automata automata;

        void construirAutomata();

    public:
        Lexer();
        ~Lexer();

        bool cargarArchivo(string ruta, string &codigo);
        void analizar(string codigo);

        vector<Token> getTokens();
        vector<string> getErrores();
};
