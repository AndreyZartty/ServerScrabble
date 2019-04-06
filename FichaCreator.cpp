
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "FichaCreator.h"


/**
 * Representa al FichaCreator.
 *
 * @author Ruben Salas
 * @since 26/03/19.
 */

/**
 * Constructor de FichaCreator.
 */
FichaCreator::FichaCreator() {
    pool = new List();
    cantBlanco = 2;
    cantA = 12;
    cantE = 12;
    cantO = 9;
    cantI = 6;
    cantS = 6;
    cantN = 5;
    cantL = 4;
    cantR = 5;
    cantU = 5;
    cantT = 4;
    cantD = 5;
    cantG = 2;
    cantC = 4;
    cantB = 2;
    cantM = 2;
    cantP = 2;
    cantH = 2;
    cantF = 1;
    cantV = 1;
    cantY = 1;
    cantCH = 1;
    cantQ = 1;
    cantJ = 1;
    cantLL = 1;
    cantNN = 1;
    cantRR = 1;
    cantX = 1;
    cantZ = 1;
}

/**
 * Crea las 100 fichas y las ingresa a un pool.
 */
void FichaCreator::initialCreate() {
    bool flag = true;
    int i = 0;
    while(flag) {
        if (cantBlanco != 0) {
            Ficha* nFicha = new Ficha("[]",0);
            pool->newNode(nFicha);
            cantBlanco -= 1;
        } else if(cantA != 0) {
            Ficha* nFicha = new Ficha("A",1);
            pool->newNode(nFicha);
            cantA -= 1;
        } else if (cantE != 0) {
            Ficha* nFicha = new Ficha("E",1);
            pool->newNode(nFicha);
            cantE -= 1;
        } else if (cantO != 0) {
            Ficha* nFicha = new Ficha("O",1);
            pool->newNode(nFicha);
            cantO -= 1;
        } else if (cantI != 0) {
            Ficha* nFicha = new Ficha("I",1);
            pool->newNode(nFicha);
            cantI -= 1;
        } else if (cantS != 0) {
            Ficha* nFicha = new Ficha("S",1);
            pool->newNode(nFicha);
            cantS -= 1;
        } else if (cantN != 0) {
            Ficha* nFicha = new Ficha("N",1);
            pool->newNode(nFicha);
            cantN -= 1;
        } else if (cantL != 0) {
            Ficha* nFicha = new Ficha("L",1);
            pool->newNode(nFicha);
            cantL -= 1;
        } else if (cantR != 0) {
            Ficha* nFicha = new Ficha("R",1);
            pool->newNode(nFicha);
            cantR -= 1;
        } else if (cantU != 0) {
            Ficha* nFicha = new Ficha("U",1);
            pool->newNode(nFicha);
            cantU -= 1;
        } else if (cantT != 0) {
            Ficha* nFicha = new Ficha("T",1);
            pool->newNode(nFicha);
            cantT -= 1;
        } else if (cantD != 0) {
            Ficha* nFicha = new Ficha("D",2);
            pool->newNode(nFicha);
            cantD -= 1;
        } else if (cantG != 0) {
            Ficha* nFicha = new Ficha("G",2);
            pool->newNode(nFicha);
            cantG -= 1;
        } else if (cantC != 0) {
            Ficha* nFicha = new Ficha("C",3);
            pool->newNode(nFicha);
            cantC -= 1;
        } else if (cantB != 0) {
            Ficha* nFicha = new Ficha("B",3);
            pool->newNode(nFicha);
            cantB -= 1;
        } else if (cantM != 0) {
            Ficha* nFicha = new Ficha("M",3);
            pool->newNode(nFicha);
            cantM -= 1;
        } else if (cantP != 0) {
            Ficha* nFicha = new Ficha("P",3);
            pool->newNode(nFicha);
            cantP -= 1;
        } else if (cantH != 0) {
            Ficha* nFicha = new Ficha("H",4);
            pool->newNode(nFicha);
            cantH -= 1;
        } else if (cantF != 0) {
            Ficha* nFicha = new Ficha("F",4);
            pool->newNode(nFicha);
            cantF -= 1;
        } else if (cantV != 0) {
            Ficha* nFicha = new Ficha("V",4);
            pool->newNode(nFicha);
            cantV -= 1;
        } else if (cantY != 0) {
            Ficha* nFicha = new Ficha("Y",4);
            pool->newNode(nFicha);
            cantY -= 1;
        } else if (cantCH != 0) {
            Ficha* nFicha = new Ficha("CH",5);
            pool->newNode(nFicha);
            cantCH -= 1;
        } else if (cantQ != 0) {
            Ficha* nFicha = new Ficha("Q",5);
            pool->newNode(nFicha);
            cantQ -= 1;
        } else if (cantJ != 0) {
            Ficha* nFicha = new Ficha("J",8);
            pool->newNode(nFicha);
            cantJ -= 1;
        } else if (cantLL != 0) {
            Ficha* nFicha = new Ficha("LL",8);
            pool->newNode(nFicha);
            cantLL -= 1;
        } else if (cantNN != 0) {
            Ficha* nFicha = new Ficha("Ñ",8);
            pool->newNode(nFicha);
            cantNN -= 1;
        } else if (cantRR != 0) {
            Ficha* nFicha = new Ficha("RR",8);
            pool->newNode(nFicha);
            cantRR -= 1;
        } else if (cantX != 0) {
            Ficha* nFicha = new Ficha("X",8);
            pool->newNode(nFicha);
            cantX -= 1;
        } else if (cantZ != 0) {
            Ficha* nFicha = new Ficha("Z",10);
            pool->newNode(nFicha);
            cantZ -= 1;
        } else {
            cout << "Fichas Listas" << endl;
            flag=false;
        }
    }
}

/**
 * Getter del pool
 * @return pool
 */
List* FichaCreator::getPool(){
    return pool;
}

/**
 * Setter del pool
 * @param _pool - List
 */
void FichaCreator::setPool(List* _pool){
    pool = _pool;
}
