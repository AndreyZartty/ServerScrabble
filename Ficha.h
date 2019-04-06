
#ifndef FICHAS_FICHA_H
#define FICHAS_FICHA_H

#include <stdlib.h>
#include <iostream>

using namespace std;

/**
 * Header de Ficha.
 *
 * @author Ruben Salas
 * @since 26/03/19.
 */
class Ficha {

private:
    ///Letra que guardara la ficha
    string letra;
    ///Puntaje asignado por letra
    int puntaje;
    ///Flag para verificar movilidad
    bool puedeMoverse;
    ///Coordenadas con posicion en tablero
    int posicion;

public:
    Ficha(string _letra, int _puntaje);
    string getLetra();
    void setLetra(string _letra);
    int getPuntaje();
    void setPuntaje(int _puntaje);
    bool getPuedeMoverse();
    void setPuedeMoverse(bool _puedeMoverse);
    int getPosicion();
    void setPosicion(int _posicion);

};


#endif //FICHAS_FICHA_H
