//
// Created by cucho16 on 02/04/19.
//

#include "Node.h"

bool Node::isOcupado(){
    return ocupado;
}
bool Node::isEspecial(){
    return especial;
}
//Ficha Node::getFicha(){
//    return ficha;
//}
Node* Node::getSiguiente(){
    return siguiente;
}
void Node::setOcupado(bool ocup){
    ocupado=ocup;
}
void Node::setEspecial(bool esp){
    especial=esp;
}
//void Node::setFicha(Ficha fich){
//    ficha=fich;
//}
void Node::setSiguiente(Node* sig){
    siguiente=sig;
}