
#include "Jugador.h"

/**
 * Representa a un Jugador.
 *
 * @author Ruben Salas
 * @since 27/03/19.
 */


/**
 * Constructor de Jugador.
 */
Jugador::Jugador(string _nombre){
    nombre = _nombre;
    listaFichas = nullptr;
}

/**
 *
 * @return
 */
List* Jugador::getListaFichas() {
    return listaFichas;
}

/**
 *
 * @param _listaFichas
 */
void Jugador::setListaFichas(List* _listaFichas) {
    listaFichas = _listaFichas;
}

/**
 *
 * @return
 */
string Jugador::getNombre() {
    return nombre;
}

/**
 *
 * @param _nombre
 */
void Jugador::setNombre(string _nombre) {
    nombre = _nombre;
}

/**
 *
 * @return
 */
int Jugador::getPuntaje() {
    return puntaje;
}

/**
 *
 * @param _puntaje
 */
void Jugador::setPuntaje(int _puntaje) {
    puntaje = _puntaje;
}

/**
 *
 * @return
 */
int Jugador::getTurnosPasados() {
    return turnosPasados;
}

/**
 *
 * @param _turnosPasados
 */
void Jugador::setTurnosPasados(int _turnosPasados) {
    turnosPasados = _turnosPasados;
}

/**
 *
 */
void Jugador::reponerFichas(){

}

/**
 *
 * @param letra
 */
Ficha* Jugador::colocarFicha(Ficha* ficha){
    Ficha* sendee = nullptr;
    NodeFicha* temp = listaFichas->getHead();

    while (temp != nullptr) {
        if (ficha == temp->getFicha()) {
            sendee = temp->getFicha();
            break;
        }
        temp = temp->getNext();
    }

    listaFichas->deleteNode(sendee);

    return sendee;


}
