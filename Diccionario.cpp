#include <string>
#include <map>
#include "Diccionario.h"

Diccionario::Diccionario(){
    
        conjunto["let"] = "reservada";
        conjunto["fn"] = "reservada";
        conjunto["if"] = "reservada";
        conjunto["else"] = "reservada";
        conjunto["while"] = "reservada";
        conjunto["return"] = "reservada";
        conjunto["for"] = "reservada";
    
        conjunto["i32"] = "tipo";
        conjunto["f64"] = "tipo";
        conjunto["bool"] = "tipo";
        conjunto["char"] = "tipo";
        conjunto["str"] = "tipo";
    
        conjunto[";"] = "punto_y_coma";
        conjunto[","] = "coma";
        conjunto[":"] = "dos_puntos";
        conjunto["="] = "asignacion";
        conjunto["+"] = "suma";
        conjunto["-"] = "resta";
        conjunto["*"] = "multiplicacion";
        conjunto["/"] = "division";
        conjunto["("] = "paren_abre";
        conjunto[")"] = "paren_cierra";
        conjunto["{"] = "llave_abre";
        conjunto["}"] = "llave_cierra";
        conjunto["["] = "corchete_abre";
        conjunto["]"] = "corchete_cierra";
        conjunto["<"] = "menor";
        conjunto[">"] = "mayor";
    

}

string Diccionario::buscar(string lexema){
        auto tipo = conjunto.find(lexema);
        if(tipo == conjunto.end()){
            return "";
        }
        else{
            return tipo->second;
        }
    
}