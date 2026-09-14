#include <string>
#include <map>
#include "Diccionario.h"

Diccionario::Diccionario(){

    conjunto["let"]    = Tipo::LET;
    conjunto["fn"]     = Tipo::FN;
    conjunto["if"]     = Tipo::IF;
    conjunto["else"]   = Tipo::ELSE;
    conjunto["while"]  = Tipo::WHILE;
    conjunto["return"] = Tipo::RETURN;
    conjunto["for"]    = Tipo::FOR;

    conjunto["i32"]  = Tipo::TIPO;
    conjunto["f64"]  = Tipo::TIPO;
    conjunto["bool"] = Tipo::TIPO;
    conjunto["char"] = Tipo::TIPO;
    conjunto["str"]  = Tipo::TIPO;

    conjunto[";"] = Tipo::PUNTO_COMA;
    conjunto[","] = Tipo::COMA;
    conjunto[":"] = Tipo::DOS_PUNTOS;
    conjunto["("] = Tipo::PARENTESIS_ABRE;
    conjunto[")"] = Tipo::PARENTESIS_CIERRA;
    conjunto["{"] = Tipo::LLAVE_ABRE;
    conjunto["}"] = Tipo::LLAVE_CIERRA;
    conjunto["["] = Tipo::CORCHETE_ABRE;
    conjunto["]"] = Tipo::CORCHETE_CIERRA;

    conjunto["+"] = Tipo::MAS;
    conjunto["-"] = Tipo::MENOS;
    conjunto["*"] = Tipo::POR;
    conjunto["/"] = Tipo::ENTRE;
    conjunto["="]  = Tipo::ASIGNACION;
    conjunto["=="] = Tipo::IGUAL_IGUAL;
    conjunto["!"]  = Tipo::NOT;
    conjunto["!="] = Tipo::DISTINTO;
    conjunto["<"]  = Tipo::MENOR;
    conjunto["<="] = Tipo::MENOR_IGUAL;
    conjunto[">"]  = Tipo::MAYOR;
    conjunto[">="] = Tipo::MAYOR_IGUAL;
    conjunto["->"] = Tipo::FLECHA;

    conjunto["&&"] = Tipo::AND;
    conjunto["||"] = Tipo::OR;
    

}

Tipo Diccionario::buscar(string lexema){
        auto tipo = conjunto.find(lexema);
        if(tipo == conjunto.end()){
            return Tipo::NINGUNO;
        }
        else{
            return tipo->second;
        }
    
}

string nombreTipo(Tipo tipo){
    switch(tipo){
        case Tipo::NINGUNO:         return "NINGUNO";
        case Tipo::IDENTIFICADOR:   return "IDENTIFICADOR";
        case Tipo::ENTERO:          return "ENTERO";
        case Tipo::DECIMAL:         return "DECIMAL";
        case Tipo::CADENA:          return "CADENA";
        case Tipo::LET:             return "LET";
        case Tipo::FN:              return "FN";
        case Tipo::IF:              return "IF";
        case Tipo::ELSE:            return "ELSE";
        case Tipo::WHILE:           return "WHILE";
        case Tipo::FOR:             return "FOR";
        case Tipo::RETURN:          return "RETURN";
        case Tipo::TIPO:            return "TIPO";
        case Tipo::MAS:             return "MAS";
        case Tipo::MENOS:           return "MENOS";
        case Tipo::POR:             return "POR";
        case Tipo::ENTRE:           return "ENTRE";
        case Tipo::ASIGNACION:      return "ASIGNACION";
        case Tipo::IGUAL_IGUAL:     return "IGUAL_IGUAL";
        case Tipo::DISTINTO:       return "DIFERENTE";
        case Tipo::MENOR:           return "MENOR";
        case Tipo::MAYOR:           return "MAYOR";
        case Tipo::MENOR_IGUAL:     return "MENOR_IGUAL";
        case Tipo::MAYOR_IGUAL:     return "MAYOR_IGUAL";
        case Tipo::AND:             return "AND";
        case Tipo::OR:              return "OR";
        case Tipo::NOT:             return "NOT";
        case Tipo::PUNTO_COMA:    return "PUNTO_Y_COMA";
        case Tipo::COMA:            return "COMA";
        case Tipo::DOS_PUNTOS:      return "DOS_PUNTOS";
        case Tipo::FLECHA:          return "FLECHA";
        case Tipo::PARENTESIS_ABRE:      return "PAREN_ABRE";
        case Tipo::PARENTESIS_CIERRA:    return "PAREN_CIERRA";
        case Tipo::LLAVE_ABRE:      return "LLAVE_ABRE";
        case Tipo::LLAVE_CIERRA:    return "LLAVE_CIERRA";
        case Tipo::CORCHETE_ABRE:   return "CORCHETE_ABRE";
        case Tipo::CORCHETE_CIERRA: return "CORCHETE_CIERRA";
        case Tipo::COMENTARIO:      return "COMENTARIO";
    }
    return "NOIDEF";
}