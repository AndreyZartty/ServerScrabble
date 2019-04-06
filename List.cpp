
#include <iostream>
#include <stdlib.h>

#include "List.h"
#include "Ficha.h"

using namespace std;


/**
 * Representa a un List.
 *
 * @author Ruben Salas
 * @since 26/03/19.
 */


/**
 * Constructor de List.
 */
List::List() {
    head = nullptr;
    len = 0;
}

/**
 * Getter del head de List.
 * @returns head - primera Ficha de List
 */
NodeFicha* List::getHead() {
    return head;
}

/**
 * Setter del head de List.
 * @param _head - Ficha
 */
void List::setHead(NodeFicha* _head) {
    head = _head;
}

/**
 * Getter del length de List.
 * @returns len - Cantidad de fichas en List
 */
int List::getLen() {
    return len;
}

/**
 * Setter del length de List.
 * @param _len - cantidad
 */
void List::setLen(int _len) {
    len = _len;
}

/**
 * Crea un nuevo Node con una Ficha para ingresarlo en List.
 * @param data - numero para la Ficha
 */
void List::newNode(Ficha* ficha){

    NodeFicha* nNode = new NodeFicha(ficha);


    if (head == nullptr) {
        head = nNode;
    } else {
        NodeFicha* temp = head;
        head = nNode;
        nNode->setNext(temp);
    }

    len+=1;

}

/**
 * Elimina un Node de List.
 * @param data
 */
void List::deleteNode(Ficha* ficha){
    NodeFicha* delNode = nullptr;
    NodeFicha* temp = head;
    NodeFicha* aux = head;
    while (aux != nullptr && aux->getFicha() != ficha) {
        temp = aux;
        aux = aux->getNext();
    }
    if (aux == nullptr) {
        cout << ficha << " no esta en la lista\n" << endl;
    } else {
        delNode = aux;
        if (head == delNode) {
            setHead(head->getNext());
        } else {
            temp->setNext(aux->getNext());
        }
    }
    delNode->setNext(nullptr);

    len-=1;

    //cout << "\n" << endl;
    //printList();

}


/**
 * Retorna un Node por su index
 */
NodeFicha* List::getNode(int index){
    NodeFicha* temp = nullptr;
    if (index <= len) {
        int i = 1;
        temp = head;
        while (i != index) {
            temp = temp->getNext();
            i++;
        }
    }
    return temp;
}

/**
 * Imprime los nodos en List.
 */
void List::printList() {
    cout << "length: " << len << "\n[ ";
    NodeFicha* temp = head;
    while (temp != nullptr) {
        ///Para que no imprima el ultimo con una coma
        if (temp->getNext() == nullptr) {
            cout << temp->getFicha()->getLetra() ;
            break;
        }
        cout << temp->getFicha()->getLetra() << ", ";
        temp = temp->getNext();
    }

    cout << " ]" << endl;
}
