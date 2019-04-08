
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

/**
 *
 * @return
 */
bool CNode::isOcupado(){
    return ocupado;
}

/**
 *
 * @return
 */
bool CNode::isEspecial(){
    return especial;
}

/**
 *
 * @return
 */
Ficha* CNode::getFicha(){
    return ficha;
}

/**
 *
 * @return
 */
CNode* CNode::getSiguiente(){
    return siguiente;
}

/**
 *
 * @param _ocupado
 */
void CNode::setOcupado(bool _ocupado){
    ocupado = _ocupado;
}

/**
 *
 * @param _especial
 */
void CNode::setEspecial(bool _especial){
    especial = _especial;
}

/**
 *
 * @param _ficha
 */
void CNode::setFicha(Ficha* _ficha){
    ficha = _ficha;
}

/**
 *
 * @param _siguiente
 */
void CNode::setSiguiente(CNode* _siguiente){
    siguiente = _siguiente;
}
