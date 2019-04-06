
#include <iostream>
#include <stdlib.h>

#include "Ficha.h"

using namespace std;

/**
 * Representa a una Ficha.
 *
 * @author Ruben Salas
 * @since 26/03/19.
 */


/**
 * Constructor de Ficha.
 */
Ficha::Ficha(string _letra, int _puntaje){
    letra = _letra;
    puntaje = _puntaje;
    puedeMoverse = true;
    posicion = 0;
}

/**
 * Getter de la letra de Ficha.
 * @returns letra - letra guardada en ficha
 */
string Ficha::getLetra(){
    return letra;
}

/**
 * Setter de letra de Ficha.
 * @param letra - string
 */
void Ficha::setLetra(string _letra){
    letra = _letra;
}

/**
 * Getter del estado de Ficha.
 * @return estado
 */
bool Ficha::getPuedeMoverse(){
    return puedeMoverse;
}

/**
 * Setter del estado de Ficha,
 * @param _puedeMoverse - bool
 */
void Ficha::setPuedeMoverse(bool _puedeMoverse) {
    puedeMoverse = _puedeMoverse;
}

/**
 * Getter de la posicion.
 * @return direccipn
 */
int Ficha::getPosicion(){
    return posicion;
}

/**
 * Setter de la posicion.
 * @param _posicion
 */
void Ficha::setPosicion(int _posicion) {
    posicion = _posicion;
}
