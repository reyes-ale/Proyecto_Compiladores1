#pragma once
#include <string>
#include <map>
using namespace std;

enum class Tipo{
    NINGUNO,
    IDENTIFICADOR,ENTERO,DECIMAL,CADENA,
    LET,FN,IF,ELSE,WHILE,FOR,RETURN,TIPO,
    MAS,MENOS,POR,ENTRE,ASIGNACION,IGUAL_IGUAL,DISTINTO,MENOR,MAYOR,MENOR_IGUAL,MAYOR_IGUAL,AND,OR,NOT,
    PUNTO_COMA,COMA,PARENTESIS_ABRE,PARENTESIS_CIERRA,LLAVE_ABRE,LLAVE_CIERRA,CORCHETE_ABRE,CORCHETE_CIERRA,
    COMENTARIO,FLECHA,DOS_PUNTOS,FIN_ARCHIVO
};
string nombreTipo (Tipo tipo);

class Diccionario{
    private:
    map<string, Tipo> conjunto;

    public:
    Diccionario();
    Tipo buscar(string lexema);

};