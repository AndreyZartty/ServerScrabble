
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
    void setTamano(int tam);

    CNode* getCasillasOcupadas(int casilla);

    CNode* getCasillasEspeciales(int casilla);
    void setMatriz(int tam);

    void setCasillaEsp(CNode* especial);
    void addCasillaOcu(CNode* ocupada);

    void addFicha(int fila, int columna, Ficha* ficha);

    void buildMatriz();

};


#endif //SCRABBLE_CUADRICULA_H

