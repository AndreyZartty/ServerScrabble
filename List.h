
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
    NodeFicha* head;
    int len;

public:
    List();
    NodeFicha* getHead();
    void setHead(NodeFicha* _head);
    int getLen();
    void setLen(int _len);
    void newNode(Ficha* _ficha);
    void deleteNode(Ficha* _ficha);
    NodeFicha* getNode(int _index);
    NodeFicha* getNode(string _letra);
    void printList();

};


#endif //CODE_LIST_H
