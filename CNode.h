
#ifndef SERVERSCRABBLE_CNODE_H
#define SERVERSCRABBLE_CNODE_H

#include "Ficha.h"

/**
 * Header de Node de Cuadricula.
 *
 * @author Andrey Sanchez
 * @since 26/03/19.
 */

class CNode {
private:
    bool ocupado;
    bool especial;
    Ficha* ficha;
    CNode* siguiente;

public:
    CNode();
    bool isOcupado();
    bool isEspecial();
    Ficha* getFicha();
    CNode* getSiguiente();
    void setOcupado(bool _ocupado);
    void setEspecial(bool _especial);
    void setFicha(Ficha* _ficha);
    void setSiguiente(CNode* sig);
};

#endif //SERVERSCRABBLE_CNODE_H

