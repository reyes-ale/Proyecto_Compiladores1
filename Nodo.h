#include <cstdlib>
#include <vector>
#include <string>
#include "Token.h"
using namespace std;

//Mismos datos que el diccionario

enum class Tipo{
    NINGUNO,
    IDENTIFICADOR,ENTERO,DECIMAL,CADENA,
    LET,FN,IF,ELSE,WHILE,FOR,RETURN,TIPO,
    MAS,MENOS,POR,ENTRE,ASIGNACION,IGUAL_IGUAL,DISTINTO,MENOR,MAYOR,MENOR_IGUAL,MAYOR_IGUAL,AND,OR,NOT,
    PUNTO_COMA,COMA,PARENTESIS_ABRE,PARENTESIS_CIERRA,LLAVE_ABRE,LLAVE_CIERRA,CORCHETE_ABRE,CORCHETE_CIERRA,
    COMENTARIO,FLECHA,DOS_PUNTOS,FIN_ARCHIVO,IN,VERDADERO,FALSO,RANGO_FOR, CARACTER
};


class Nodo {
    
private:
    Tipo tipo;
    string valor;
    vector<Nodo*> hijos;

public:
    Nodo(string val, Tipo tipo);

        
};