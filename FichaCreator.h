
#ifndef FICHAS_FICHACREATOR_H
#define FICHAS_FICHACREATOR_H


#include "List.h"


/**
 * Header de FichaCreator.
 *
 * @author Ruben Salas
 * @since 26/03/19.
 */
class FichaCreator {

private:
    List* pool;
    int cantBlanco;
    int cantA;
    int cantE;
    int cantO;
    int cantI;
    int cantS;
    int cantN;
    int cantL;
    int cantR;
    int cantU;
    int cantT;
    int cantD;
    int cantG;
    int cantC;
    int cantB;
    int cantM;
    int cantP;
    int cantH;
    int cantF;
    int cantV;
    int cantY;
    int cantCH;
    int cantQ;
    int cantJ;
    int cantLL;
    int cantNN;
    int cantRR;
    int cantX;
    int cantZ;

public:

    FichaCreator();
    void initialCreate();
    List* getPool();
    void setPool(List* _pool);

};


#endif //FICHAS_FICHACREATOR_H
