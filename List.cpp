
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
void List::newNode(Ficha* _ficha){

    NodeFicha* nNode = new NodeFicha(_ficha);


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
void List::deleteNode(Ficha* _ficha){
    NodeFicha* delNode = nullptr;
    NodeFicha* temp = head;
    NodeFicha* aux = head;
    while (aux != nullptr && aux->getFicha() != _ficha) {
        temp = aux;
        aux = aux->getNext();
    }
    if (aux == nullptr) {
        cout << _ficha << " no esta en la lista\n" << endl;
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

}


/**
 * Retorna un Node por su index.
 * @param posicion
 * @return Node
 */
NodeFicha* List::getNode(int _index){
    NodeFicha* temp = nullptr;
    if (_index <= len) {
        int i = 1;
        temp = head;
        while (i != _index) {
            temp = temp->getNext();
            i++;
        }
    }
    return temp;
}


/**
 * Retorna un node por su letra.
 * @param letra
 * @return Node
 */
NodeFicha* List::getNode(string _letra) {
    NodeFicha* temp = head;
    while (temp != nullptr) {
        if (temp->getFicha()->getLetra() == _letra) {
            return temp;
        }
        temp = temp->getNext();
    }
    return nullptr;
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
