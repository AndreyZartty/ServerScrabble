
#ifndef SCRABBLE_CUADRICULA_H
#define SCRABBLE_CUADRICULA_H

#include "CNode.h"

/**
 * Header de Cuadricula.
 *
 * @author Andrey Sanchez
 * @since 26/03/19.
 */

class Cuadricula {

private:
    int tamano;
    CNode* casillasOcupadas[0];
    CNode* casillasEspeciales[0];
    CNode* matriz [15][15];
    int cantOcupadas;
    int cantEspeciales;
public:
    Cuadricula();

    int getTamano();
    void setTamano(int _tamano);
    CNode* getCasillaOcupada(int _casilla);
    void setCasillaEspecial(CNode* _especial);
    CNode* getCasillaEspecial(int _casilla);
    void setCasillaOcupada(CNode* _ocupada);

    void setMatriz(int _tamano);

    void addFicha(int fila, int columna, Ficha* ficha);

    void buildMatriz();

};


#endif //SCRABBLE_CUADRICULA_H

