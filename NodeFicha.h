
#ifndef FICHAS_NODE_H
#define FICHAS_NODE_H

#include "Ficha.h"


/**
 * Header de Node.
 *
 * @author Ruben Salas
 * @since 26/03/19.
 */
class NodeFicha {

private:
    ///Dato que guardara el nodo
    Ficha* ficha;
    ///Referencia al nodo que esta siguiente a este
    NodeFicha* next;

public:
    NodeFicha(Ficha* _ficha);
    Ficha* getFicha();
    void setFicha(Ficha* _ficha);
    NodeFicha* getNext();
    void setNext(NodeFicha* _next);
};


#endif //FICHAS_NODE_H
