
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
 * Getter de la lista de Fichas
 * @return List
 */
List* Jugador::getListaFichas() {
    return listaFichas;
}

/**
 * Setter de la lista de Fichas
 * @param _listaFichas
 */
void Jugador::setListaFichas(List* _listaFichas) {
    listaFichas = _listaFichas;
}

/**
 * Getter del Nombre
 * @return string con el nombre
 */
string Jugador::getNombre() {
    return nombre;
}

/**
 * Setter del Nombre
 * @param _nombre
 */
void Jugador::setNombre(string _nombre) {
    nombre = _nombre;
}

/**
 * Getter del puntaje del jugador
 * @return int
 */
int Jugador::getPuntaje() {
    return puntaje;
}

/**
 * Setter del puntaje del jugador
 * @param _puntaje
 */
void Jugador::setPuntaje(int _puntaje) {
    puntaje = _puntaje;
}

/**
 * Getter de la cantidad de turnos pasados
 * @return cantidad
 */
int Jugador::getTurnosPasados() {
    return turnosPasados;
}

/**
 * Setter de la cantidad de turnos pasados
 * @param _turnosPasados
 */
void Jugador::setTurnosPasados(int _turnosPasados) {
    turnosPasados = _turnosPasados;
}

/**
 * Repone las fichas del jugador cuando tiene menos de la cantidad minima
 */
void Jugador::reponerFichas(){

}

/**
 * Envia la ficha fuera de la lista para ser ingresada en la cuadricula
 * @param ficha
 * @return ficha por enviar
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
