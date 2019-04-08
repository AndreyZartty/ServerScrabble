
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
            Ficha* nFicha = new Ficha("a",1);
            pool->newNode(nFicha);
            cantA -= 1;
        } else if (cantE != 0) {
            Ficha* nFicha = new Ficha("e",1);
            pool->newNode(nFicha);
            cantE -= 1;
        } else if (cantO != 0) {
            Ficha* nFicha = new Ficha("o",1);
            pool->newNode(nFicha);
            cantO -= 1;
        } else if (cantI != 0) {
            Ficha* nFicha = new Ficha("i",1);
            pool->newNode(nFicha);
            cantI -= 1;
        } else if (cantS != 0) {
            Ficha* nFicha = new Ficha("s",1);
            pool->newNode(nFicha);
            cantS -= 1;
        } else if (cantN != 0) {
            Ficha* nFicha = new Ficha("n",1);
            pool->newNode(nFicha);
            cantN -= 1;
        } else if (cantL != 0) {
            Ficha* nFicha = new Ficha("l",1);
            pool->newNode(nFicha);
            cantL -= 1;
        } else if (cantR != 0) {
            Ficha* nFicha = new Ficha("r",1);
            pool->newNode(nFicha);
            cantR -= 1;
        } else if (cantU != 0) {
            Ficha* nFicha = new Ficha("u",1);
            pool->newNode(nFicha);
            cantU -= 1;
        } else if (cantT != 0) {
            Ficha* nFicha = new Ficha("t",1);
            pool->newNode(nFicha);
            cantT -= 1;
        } else if (cantD != 0) {
            Ficha* nFicha = new Ficha("d",2);
            pool->newNode(nFicha);
            cantD -= 1;
        } else if (cantG != 0) {
            Ficha* nFicha = new Ficha("g",2);
            pool->newNode(nFicha);
            cantG -= 1;
        } else if (cantC != 0) {
            Ficha* nFicha = new Ficha("c",3);
            pool->newNode(nFicha);
            cantC -= 1;
        } else if (cantB != 0) {
            Ficha* nFicha = new Ficha("b",3);
            pool->newNode(nFicha);
            cantB -= 1;
        } else if (cantM != 0) {
            Ficha* nFicha = new Ficha("m",3);
            pool->newNode(nFicha);
            cantM -= 1;
        } else if (cantP != 0) {
            Ficha* nFicha = new Ficha("p",3);
            pool->newNode(nFicha);
            cantP -= 1;
        } else if (cantH != 0) {
            Ficha* nFicha = new Ficha("h",4);
            pool->newNode(nFicha);
            cantH -= 1;
        } else if (cantF != 0) {
            Ficha* nFicha = new Ficha("f",4);
            pool->newNode(nFicha);
            cantF -= 1;
        } else if (cantV != 0) {
            Ficha* nFicha = new Ficha("v",4);
            pool->newNode(nFicha);
            cantV -= 1;
        } else if (cantY != 0) {
            Ficha* nFicha = new Ficha("y",4);
            pool->newNode(nFicha);
            cantY -= 1;
        } else if (cantCH != 0) {
            Ficha* nFicha = new Ficha("ch",5);
            pool->newNode(nFicha);
            cantCH -= 1;
        } else if (cantQ != 0) {
            Ficha* nFicha = new Ficha("q",5);
            pool->newNode(nFicha);
            cantQ -= 1;
        } else if (cantJ != 0) {
            Ficha* nFicha = new Ficha("j",8);
            pool->newNode(nFicha);
            cantJ -= 1;
        } else if (cantLL != 0) {
            Ficha* nFicha = new Ficha("ll",8);
            pool->newNode(nFicha);
            cantLL -= 1;
        } else if (cantNN != 0) {
            Ficha* nFicha = new Ficha("ñ",8);
            pool->newNode(nFicha);
            cantNN -= 1;
        } else if (cantRR != 0) {
            Ficha* nFicha = new Ficha("rr",8);
            pool->newNode(nFicha);
            cantRR -= 1;
        } else if (cantX != 0) {
            Ficha* nFicha = new Ficha("x",8);
            pool->newNode(nFicha);
            cantX -= 1;
        } else if (cantZ != 0) {
            Ficha* nFicha = new Ficha("z",10);
            pool->newNode(nFicha);
            cantZ -= 1;
        } else {
            cout << "Fichas Listas" << endl;
            flag=false;
        }
    }
}



int getPoints() {

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
