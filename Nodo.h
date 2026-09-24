#include <cstdlib>
#include <vector>
#include <string>
#include "Token.h"
using namespace std;


enum class TipoN{
    PROGRAMA,
    FUNCION,
    PARAMETRO,
    DECLARACION,
    ASIGNACION,
    CONDICION,
    BUCLE_WHILE,
    BUCLE_FOR,
    RANGO,
    RETORNO,
    BINARIA,       
    UNARIA,        
    LLAMADA,       
 
    IDENTIFICADOR,
    ENTERO,
    DECIMAL,
    CADENA,
    CARACTER,
    BOOLEANO
};


class Nodo {
    
private:
    TipoN tipo;
    string valor;
    vector<Nodo*> hijitos;

public:
    Nodo(string valor, TipoN tipo);
    void agregarHijito(Nodo* hijito);
    TipoN getTipo();
    string getValor();
    vector<Nodo*> getHijitos();
    ~Nodo();

};