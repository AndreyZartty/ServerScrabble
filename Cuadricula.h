
#ifndef SCRABBLE_CUADRICULA_H
#define SCRABBLE_CUADRICULA_H

#include "NodeFicha.h"
#include "List.h"

class Cuadricula {

private:
    List* listaCuadricula;


public:
    Cuadricula();
    List* getListaCuadricula();
    void setListaCuadricula(List* _listaCuadricula);

};


#endif //SCRABBLE_CUADRICULA_H
