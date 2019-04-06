
#include "Cuadricula.h"
#include "NodeFicha.h"

Cuadricula::Cuadricula() {
    listaCuadricula = new List();
}

List *Cuadricula::getListaCuadricula() {
    return listaCuadricula;
}

void Cuadricula::setListaCuadricula(List* _listaCuadricula) {
    listaCuadricula = _listaCuadricula;
}
