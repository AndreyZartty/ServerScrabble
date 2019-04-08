
#include "Cuadricula.h"
#include "CNode.h"

/**
 * Representa a una Cuadricula.
 *
 * @author Andrey Sanchez
 * @since 26/03/19.
 */

Cuadricula::Cuadricula(){
    buildMatriz();
    tamano = 0;

    cantOcupadas = 0;
    cantEspeciales = 0;

}

int Cuadricula::getTamano(){
    return tamano;
}
CNode* Cuadricula::getCasillasOcupadas(int casilla){
    return casillasOcupadas[casilla];
}
CNode* Cuadricula::getCasillasEspeciales(int casilla){
    return casillasEspeciales[casilla];
}
void Cuadricula::setMatriz(int tam){
    matriz[tam][tam];
}
void Cuadricula::setTamano(int tam){
    tamano = tam;
    setMatriz(getTamano());
}
void Cuadricula::setCasillaEsp(CNode* especial){
    casillasEspeciales[cantEspeciales] = especial;
    cantEspeciales++;
}
void Cuadricula::addCasillaOcu(CNode* ocupada) {
    casillasOcupadas[cantOcupadas] = ocupada;
    cantOcupadas++;
}

void  Cuadricula::addFicha(int fila, int columna, Ficha* ficha) {
    matriz[fila][columna]->setFicha(ficha);
}

void Cuadricula::buildMatriz() {

    int i = 15;
    int j = 15;
    for (i;i>0;i--) {
        for (j;j>0;j--) {
            CNode* nCNode = new CNode();
            matriz[i][j] = nCNode;
            //cout << "["<< i << "," << j <<"]" << endl;
        }
        j=15;
    }
    cout << "Matriz cuadricula lista" << endl;
}