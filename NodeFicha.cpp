
#include <iostream>
#include <stdlib.h>

#include "NodeFicha.h"

using namespace std;

/**
 * Representa a un Nodo.
 *
 * @author Ruben Salas
 * @since 26/03/19.
 */


/**
 * Constructor de Node.
 */
NodeFicha::NodeFicha(Ficha* _ficha){
    ficha = _ficha;
    next = nullptr;
}

/**
 * Getter del dato de Node.
 * @returns ficha - ficha almacenada en nodo
 */
Ficha* NodeFicha::getFicha(){
    return ficha;
}

/**
 * Setter de la ficha de Node.
 * @param _ficha - Ficha
 */
void NodeFicha::setFicha(Ficha* _ficha) {
    ficha = _ficha;
}

/**
 * Getter del next de Node.
 * @returns next - referencia al siguiente nodo
 */
NodeFicha* NodeFicha::getNext(){
    return next;
}

/**
 * Setter del next de Node.
 * @param _next - Node
 */
void NodeFicha::setNext(NodeFicha* _next){
    next = _next;
}
