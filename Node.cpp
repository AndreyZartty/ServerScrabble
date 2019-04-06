
#include <iostream>
#include <stdlib.h>

#include "Node.h"

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
Node::Node(Ficha* _ficha){
    ficha = _ficha;
    next = nullptr;
}

/**
 * Getter del dato de Node.
 * @returns ficha - ficha almacenada en nodo
 */
Ficha* Node::getFicha(){
    return ficha;
}

/**
 * Setter de la ficha de Node.
 * @param _ficha - Ficha
 */
void Node::setFicha(Ficha* _ficha) {
    ficha = _ficha;
}

/**
 * Getter del next de Node.
 * @returns next - referencia al siguiente nodo
 */
Node* Node::getNext(){
    return next;
}

/**
 * Setter del next de Node.
 * @param _next - Node
 */
void Node::setNext(Node* _next){
    next = _next;
}
