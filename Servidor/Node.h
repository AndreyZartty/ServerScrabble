//
// Created by cucho16 on 02/04/19.
//

#ifndef SERVERSCRABBLE_NODE_H
#define SERVERSCRABBLE_NODE_H


class Node {

private:
    bool ocupado;
    bool especial;
    //Ficha ficha;
    Node* siguiente;

public:
    bool isOcupado();
    bool isEspecial();
    //Ficha getFicha();
    Node* getSiguiente();
    void setOcupado(bool ocup);
    void setEspecial(bool esp);
    //void setFicha(Ficha fich);
    void setSiguiente(Node* sig);
};



#endif //SERVERSCRABBLE_NODE_H
