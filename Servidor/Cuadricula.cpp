//
// Created by cucho16 on 02/04/19.
//

#include "Cuadricula.h"
#include "Node.h"

int Cuadricula::gettamano(){
    return tamano;
}
Node Cuadricula::getCasillaOcu(int casilla){
    return casillasOcu[casilla];
}
Node Cuadricula::getCasillaEsp(int casilla){
    return casillasEsp[casilla];
}
void Cuadricula::setMatriz(int tam){
    matriz[tam][tam];
}
void Cuadricula::settamano(int tam){
    tamano = tam;
    setMatriz(gettamano());
}
void Cuadricula::setCasillaEsp(Node especial){
    casillasEsp[cEspeciales] = especial;
    cEspeciales++;
}
void Cuadricula::addCasillaOcu(Node ocupada){
    casillasOcu[cOcupadas]= ocupada;
    cOcupadas++;
}
