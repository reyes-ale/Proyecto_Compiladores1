#include <iostream>
using namespace std;

class Token {
    private:
        string valor;
        string tipo;

    public:
        Token();
        Token(string valor, string tipo);

        string getValor();
        string getTipo();

};