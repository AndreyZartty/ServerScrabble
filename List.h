
#ifndef CODE_LIST_H
#define CODE_LIST_H

#include <stdlib.h>

#include "NodeFicha.h"

/**
 * Header de List.
 *
 * @author Ruben Salas
 * @since 26/03/19.
 */
class List {

private:
    ///Primer node de List
    NodeFicha* head;
    ///Cantidad de nodos en List
    int len;

public:
    List();
    NodeFicha* getHead();
    void setHead(NodeFicha* _head);
    int getLen();
    void setLen(int _len);
    void newNode(Ficha* ficha);
    void deleteNode(Ficha* ficha);
    NodeFicha* getNode(int index);
    void printList();


};

#endif //CODE_LIST_H
