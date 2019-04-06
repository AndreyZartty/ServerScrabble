
#ifndef FICHAS_JUGADOR_H
#define FICHAS_JUGADOR_H


#include <iostream>
#include "List.h"

/**
 * Header de Jugador.
 *
 * @author Ruben Salas
 * @since 26/03/19.
 */
class Jugador {

private:
    List* listaFichas;
    string nombre;
    int puntaje;
    int turnosPasados;

public:
    Jugador(string _nombre);
    List* getListaFichas();
    void setListaFichas(List* _listaFichas);
    string getNombre();
    void setNombre(string _nombre);
    int getPuntaje();
    void setPuntaje(int _puntaje);
    int getTurnosPasados();
    void setTurnosPasados(int _turnosPasados);
    void reponerFichas();
    Ficha* colocarFicha(Ficha* ficha);

};


#endif //FICHAS_JUGADOR_H
