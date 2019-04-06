
#ifndef FICHAS_NODE_H
#define FICHAS_NODE_H

#include "Ficha.h"


/**
 * Header de Node.
 *
 * @author Ruben Salas
 * @since 26/03/19.
 */
class Node {

private:
    ///Dato que guardara el nodo
    Ficha* ficha;
    ///Referencia al nodo que esta siguiente a este
    Node* next;

public:
    Node(Ficha* _ficha);
    Ficha* getFicha();
    void setFicha(Ficha* _ficha);
    Node* getNext();
    void setNext(Node* _next);
};


#endif //FICHAS_NODE_H
