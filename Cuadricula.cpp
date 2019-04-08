
#include "Cuadricula.h"
#include "CNode.h"

/**
 * Representa a una Cuadricula.
 *
 * @author Andrey Sanchez
 * @since 26/03/19.
 */

/**
 * Constructor de la Cuadricula
 */
Cuadricula::Cuadricula(){
    buildMatriz();
    tamano = 0;
    cantOcupadas = 0;
    cantEspeciales = 0;
}

/**
 * Getter del tamaño de la cuadricula
 * @return tamaño
 */
int Cuadricula::getTamano(){
    return tamano;
}

/**
 * Setter del tamaño de la cuadricula
 * @param tamaño
 */
void Cuadricula::setTamano(int _tamano){
    tamano = _tamano;
    setMatriz(getTamano());
}

/**
 * Getter de casilla ocupada
 * @param casilla
 * @return
 */
CNode* Cuadricula::getCasillaOcupada(int _casilla){
    return casillasOcupadas[_casilla];
}

/**
 * Setter de casilla ocupada
 * @param ocupada
 */
void Cuadricula::setCasillaOcupada(CNode* _ocupada) {
    casillasOcupadas[cantOcupadas] = _ocupada;
    cantOcupadas++;
}

/**
 * Getter de casilla especial
 * @param casilla
 * @return
 */
CNode* Cuadricula::getCasillaEspecial(int _casilla){
    return casillasEspeciales[_casilla];
}

/**
 * Setter de casilla especial
 * @param especial
 */
void Cuadricula::setCasillaEspecial(CNode* _especial){
    casillasEspeciales[cantEspeciales] = _especial;
    cantEspeciales++;
}

/**
 * Setter del tamaño de la matriz
 * @param _tamano
 */
void Cuadricula::setMatriz(int _tamano){
    matriz[_tamano][_tamano];
}


/**
 * Ingresa la fila en la matriz
 * @param fila - donde se colocara
 * @param columna - donde se colocara
 * @param ficha
 */
void  Cuadricula::addFicha(int fila, int columna, Ficha* ficha) {
    matriz[fila][columna]->setFicha(ficha);
}

/**
 * Construye la matriz 15x15 con CNodes preestablecidos
 */
void Cuadricula::buildMatriz() {

    for (int i = 0 ; i < 15 ; i++) {
        for (int j = 0 ; j < 15 ; j++) {
            CNode* nCNode = new CNode();
            matriz[i][j] = nCNode;
            cout << "["<< i << "," << j <<"]" << endl;
        }
    }
    cout << "Matriz de cuadricula lista" << endl;
}
