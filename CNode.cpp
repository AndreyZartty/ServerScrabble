
#include "CNode.h"


/**
 * Representa a un Nodo de la Cuadricula.
 *
 * @author Andrey Sanchez
 * @since 26/03/19.
 */

CNode::CNode() {
    ocupado = false;
    especial = false;
    ficha = nullptr;
    siguiente = nullptr;
}

bool CNode::isOcupado(){
    return ocupado;
}
bool CNode::isEspecial(){
    return especial;
}
Ficha* CNode::getFicha(){
    return ficha;
}
CNode* CNode::getSiguiente(){
    return siguiente;
}
void CNode::setOcupado(bool _ocupado){
    ocupado = _ocupado;
}
void CNode::setEspecial(bool _especial){
    especial = _especial;
}
void CNode::setFicha(Ficha* _ficha){
    ficha = _ficha;
}
void CNode::setSiguiente(CNode* _siguiente){
    siguiente = _siguiente;
}
