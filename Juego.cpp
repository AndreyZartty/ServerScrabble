
#include <cstdlib>
#include <time.h>

#include "Juego.h"

/**
 * Representa al Juego.
 *
 * @author Ruben Salas
 * @since 27/03/19.
 */


/**
 * Constructor de Juego.
 */
Juego::Juego(int _cantJugadoresPermitidos){
    codigo = "0000";
    creator = new FichaCreator();
    poolFichas = nullptr;
    cantFichas = 0;
    cantJugadoresActuales = 0;
    cantJugadoresPermitidos = _cantJugadoresPermitidos;
    j1 = nullptr;
    j2 = nullptr;
    j3 = nullptr;
    j4 = nullptr;
    cuadricula = new Cuadricula();
    terminado = false;
    iniciado = false;
    enTurno = nullptr;
    ganador = nullptr;
}

/**
 *
 * @return
 */
string Juego::getCodigo() {
    return codigo;
}

/**
 *
 * @param _codigo
 */
void Juego::setCodigo(string _codigo) {
    codigo = _codigo;
}

/**
 * Getter del creador de fichas.
 * @return creator
 */
FichaCreator* Juego::getCreator() {
    return creator;
}

/**
 * Setter del creador de fichas
 * @param _creator
 */
void Juego::setCreator(FichaCreator* _creator) {
    creator = _creator;
}

/**
 * Getter del Jugador #1
 * @return j1
 */
Jugador* Juego::getJ1() {
    return j1;
}

/**
 * Setter del Jugador #1
 * @param _j1
 */
void Juego::setJ1(Jugador* _j1) {
    j1 = _j1;
}

/**
 * Setter del Jugador #2
 * @return j2
 */
Jugador* Juego::getJ2() {
    return j2;
}

/**
 *
 * @param _j2
 */
void Juego::setJ2(Jugador* _j2) {
    j2 = _j2;
}

/**
 *
 * @return
 */
Jugador* Juego::getJ3() {
    return j3;
}

/**
 *
 * @param _j3
 */
void Juego::setJ3(Jugador* _j3) {
    j3 = _j3;
}

/**
 *
 * @return
 */
Jugador* Juego::getJ4() {
    return j4;
}

/**
 *
 * @param _j4
 */
void Juego::setJ4(Jugador* _j4) {
    j4 = _j4;
}

/**
 *
 * @return
 */
int Juego::getCantJugadoresActuales() {
    return cantJugadoresActuales;
}

/**
 *
 * @param _cantJugadoresActuales
 */
void Juego::setCantJugadoresActuales(int _cantJugadoresActuales) {
    cantJugadoresActuales = _cantJugadoresActuales;
}

/**
 *
 * @return
 */
int Juego::getCantJugadoresPermitidos() {
    return cantJugadoresPermitidos;
}

/**
 *
 * @param _cantJugadoresPermitidos
 */
void Juego::setCantJugadoresPermitidos(int _cantJugadoresPermitidos) {
    cantJugadoresPermitidos = _cantJugadoresPermitidos;
}

/**
 *
 * @return
 */
Cuadricula* Juego::getCuadricula() {
    return cuadricula;
}

/**
 *
 * @param _cuadricula
 */
void Juego::setCuadricula(Cuadricula* _cuadricula) {
    cuadricula = _cuadricula;
}

/**
 *
 * @return
 */
List* Juego::getPoolFichas() {
    return poolFichas;
}

/**
 *
 * @param _poolFichas
 */
void Juego::setPoolFichas(List* _poolFichas) {
    poolFichas = _poolFichas;
}

/**
 *
 * @return
 */
int Juego::getCantFichas() {
    return cantFichas;
}

/**
 *
 * @param _cantFichas
 */
void Juego::setCantFichas(int _cantFichas) {
    cantFichas = _cantFichas;
}

/**
 *
 * @return
 */
bool Juego::isTerminado() {
    return terminado;
}

/**
 *
 * @param _terminado
 */
void Juego::setTerminado(bool _terminado) {
    terminado = _terminado;
}

/**
 *
 * @return
 */
bool Juego::isIniciado(){
    return iniciado;
}

/**
 *
 * @param _iniciado
 */
void Juego::setIniciado(bool _iniciado) {
    iniciado = _iniciado;
}

/**
 *
 */
Jugador* Juego::getEnTurno() {
    return enTurno;
}

/**
 *
 * @param enTurno
 */
void Juego::setEnTurno(Jugador *enTurno) {
    Juego::enTurno = enTurno;
}

/**
 *
 * @return
 */
Jugador* Juego::getGanador() {
    return ganador;
}

/**
 *
 * @param _ganador
 */
void Juego::setGanador(Jugador* _ganador) {
    ganador = _ganador;
}


//Funciones


void Juego::generarCodigo(int numJuego) {
    string numJuegoStr = to_string(numJuego);
    if (numJuego >= 10) {
        setCodigo("00" + numJuegoStr);
    } else {
        setCodigo("000" + numJuegoStr);
    }
    cout << "\nCodigo de Juego #" << numJuegoStr << ": " << codigo << endl;
}

/**
 * Añade un jugador y verifica si hay campo en el juego.
 * @param nJugador
 */
void Juego::addJugador(string nombre) {
    if (j4 == nullptr) {
        Jugador* nJugador = new Jugador(nombre);
        if (j3 == nullptr) {
            if (j2 == nullptr) {
                if (j1 == nullptr) {
                    j1 = nJugador;
                } else {
                    j2 = nJugador;
                }
            } else {
                j3 = nJugador;
            }
        } else {
            j4 = nJugador;
        }
        cantJugadoresActuales++;

    } else {
        cout << "Todos los espacios disponibles estan ocupados." << endl;
    }
}


/**
 * Crea las fichas por medio del FichaCreator. Asigna el pool de fichas como atributo.
 */
void Juego::crearFichas(){
    ///FichaCreator crea todas las fichas y las ingresa al pool guardado en esa clase.
    creator->initialCreate();
    ///El pool de las fichas es pasado al atributo pool del juego para que sea accesado ahi.
    setPoolFichas(creator->getPool());
    ///Agrega el valor de la cantidad de fichas que hayan en el pool
    setCantFichas(poolFichas->getLen());

    cout << "Fichas Creadas.\n" << endl;

}

/**
 * Reparte las fichas entre los Jugadores existentes dando 7 a cada uno.
 */
void Juego::repartirFichas(){
    ///Genera un valor diferente cada vez que se llame a la funcion dependiendo de la hora y fecha.
    srand (time(NULL));

    if (j1 != nullptr) {
        cout << "\nRepartiendo fichas Jugador 1" << endl;

        ///Lista del jugador 1
        List* lF1 = new List();
        ///Contador jugador 1
        int i1 = 7;
        while (i1 > 0) {
            ///Obtiene un int aleatorio
            int random1 = rand() % cantFichas + 1;
            ///Obtiene la ficha del pool
            Ficha* randomFicha1 = poolFichas->getNode(random1)->getFicha();
            ///Elimina la ficha del pool
            poolFichas->deleteNode(randomFicha1);
            ///Actualiza la cantidad de Fichas en el pool
            setCantFichas(poolFichas->getLen());
            ///Agrega la ficha a la lista del jugador1
            lF1->newNode(randomFicha1);
            ///Disminuye el contador del jugador 1
            i1--;
        }
        j1->setListaFichas(lF1);
        j1->getListaFichas()->printList();

    }
    if (j2 != nullptr) {
        cout << "\nRepartiendo fichas Jugador 2" << endl;

        ///Lista del jugador 2
        List* lF2 = new List();
        ///Contador jugador 2
        int i2 = 7;
        while (i2 > 0) {
            ///Obtiene un int aleatorio
            int random2 = rand() % cantFichas + 1;
            ///Obtiene la ficha del pool
            Ficha* randomFicha2 = poolFichas->getNode(random2)->getFicha();
            ///Elimina la ficha del pool
            poolFichas->deleteNode(randomFicha2);
            ///Actualiza la cantidad de Fichas en el pool
            setCantFichas(poolFichas->getLen());
            ///Agrega la ficha a la lista del jugador1
            lF2->newNode(randomFicha2);
            ///Disminuye el contador del jugador 1
            i2--;
        }
        j2->setListaFichas(lF2);
        j2->getListaFichas()->printList();
    }
    if (j3 != nullptr) {
        cout << "\nRepartiendo fichas Jugador 3" << endl;

        ///Lista del jugador 3
        List* lF3 = new List();
        ///Contador jugador 3
        int i3 = 7;
        while (i3 > 0) {
            ///Obtiene un int aleatorio
            int random3 = rand() % cantFichas + 1;
            ///Obtiene la ficha del pool
            Ficha* randomFicha3 = poolFichas->getNode(random3)->getFicha();
            ///Elimina la ficha del pool
            poolFichas->deleteNode(randomFicha3);
            ///Actualiza la cantidad de Fichas en el pool
            setCantFichas(poolFichas->getLen());
            ///Agrega la ficha a la lista del jugador1
            lF3->newNode(randomFicha3);
            ///Disminuye el contador del jugador 1
            i3--;
        }
        j3->setListaFichas(lF3);
        j3->getListaFichas()->printList();
    }
    if (j4 != nullptr) {
        cout << "\nRepartiendo fichas Jugador 4" << endl;

        ///Lista del jugador 4
        List* lF4 = new List();
        ///Contador jugador 4
        int i4 = 7;
        while (i4 > 0) {
            ///Obtiene un int aleatorio
            int random4 = rand() % cantFichas + 1;
            ///Obtiene la ficha del pool
            Ficha* randomFicha4 = poolFichas->getNode(random4)->getFicha();
            ///Elimina la ficha del pool
            poolFichas->deleteNode(randomFicha4);
            ///Actualiza la cantidad de Fichas en el pool
            setCantFichas(poolFichas->getLen());
            ///Agrega la ficha a la lista del jugador1
            lF4->newNode(randomFicha4);
            ///Disminuye el contador del jugador 1
            i4--;
        }
        j4->setListaFichas(lF4);
        j4->getListaFichas()->printList();
    }

    if (cantJugadoresActuales == 0) {
        cout << "No hay jugadores disponibles para repartir fichas." << endl;
    }

}

/**
 * Completa la cantidad de fichas de cada jugador, a 7, luego de su turno.
 */
void Juego::completarFichas(Jugador* jugador) {
    ///Genera un valor diferente cada vez que se llame a la funcion dependiendo de la hora y fecha.
    srand (time(NULL));

    int cantFichas = jugador->getListaFichas()->getLen();

    if (cantFichas > 7) {
        for (cantFichas; cantFichas == 7; cantFichas++) {
            ///Obtiene un int aleatorio
            int random = rand() % cantFichas + 1;
            ///Obtiene la ficha del pool
            Ficha* randomFicha = poolFichas->getNode(random)->getFicha();
            ///Elimina la ficha del pool
            poolFichas->deleteNode(randomFicha);
            ///Actualiza la cantidad de Fichas en el pool
            setCantFichas(poolFichas->getLen());
            ///Agrega la ficha a la lista del jugador1
            jugador->getListaFichas()->newNode(randomFicha);
        }
    } else {
        cout << "Ya posee 7 fichas" << endl;
    }

}

/**
 * Verifica la cantidad de turnos pasados de todos los jugadores
 */
void Juego::checkTurnosPasados(){
    int cantJ1;
    int cantJ2;
    int cantJ3;
    int cantJ4;
    if (cantJugadoresActuales == 2) {
        cantJ1 = j1->getTurnosPasados();
        cantJ2 = j2->getTurnosPasados();
        if (cantJ1 == cantJ2 == 2) {
            terminado = true;
        }
    } else if (cantJugadoresActuales == 3) {
        cantJ1 = j1->getTurnosPasados();
        cantJ2 = j2->getTurnosPasados();
        cantJ3 = j3->getTurnosPasados();
        if (cantJ1 == cantJ2 == cantJ3 == 2) {
            terminado = true;
        }
    } else { //cantJugadores == 4
        cantJ1 = j1->getTurnosPasados();
        cantJ2 = j2->getTurnosPasados();
        cantJ3 = j3->getTurnosPasados();
        cantJ4 = j4->getTurnosPasados();
        if (cantJ1 == cantJ2 == cantJ3 == cantJ4 == 2) {
            terminado = true;
        }
    }
}

/**
 *
 */
void Juego::checkTerminado() {
    if (terminado == true) {
        cout << "El juego ha terminado!" << endl;
        int puntajeJ1;
        int puntajeJ2;
        int puntajeJ3;
        int puntajeJ4;

        if (cantJugadoresActuales == 2) {

            puntajeJ1 = j1->getPuntaje();
            puntajeJ2 = j2->getPuntaje();

            if ((puntajeJ1 > puntajeJ2)) {
                setGanador(j1);
            } else if ((puntajeJ2 > puntajeJ1)) {
                setGanador(j2);
            }

        } else if (cantJugadoresActuales == 3) {

            puntajeJ1 = j1->getPuntaje();
            puntajeJ2 = j2->getPuntaje();
            puntajeJ3 = j3->getPuntaje();

            if ((puntajeJ1 > puntajeJ2) && (puntajeJ1 > puntajeJ3)) {
                setGanador(j1);
            } else if ((puntajeJ2 > puntajeJ1) && (puntajeJ2 > puntajeJ3)) {
                setGanador(j2);
            } else if ((puntajeJ3 > puntajeJ2) && (puntajeJ3 > puntajeJ1)) {
                setGanador(j3);
            }

        } else if (cantJugadoresActuales == 4) {

            puntajeJ1 = j1->getPuntaje();
            puntajeJ2 = j2->getPuntaje();
            puntajeJ3 = j3->getPuntaje();
            puntajeJ4 = j4->getPuntaje();

            if ((puntajeJ1 > puntajeJ2) && (puntajeJ1 > puntajeJ3) && (puntajeJ1 > puntajeJ4)) {
                setGanador(j1);
            } else if ((puntajeJ2 > puntajeJ1) && (puntajeJ2 > puntajeJ3) && (puntajeJ2 > puntajeJ4)) {
                setGanador(j2);
            } else if ((puntajeJ3 > puntajeJ2) && (puntajeJ3 > puntajeJ1) && (puntajeJ3 > puntajeJ4)) {
                setGanador(j3);
            } else if((puntajeJ4>puntajeJ2) && (puntajeJ4>puntajeJ3) && (puntajeJ4>puntajeJ1)) {
                setGanador(j4);
            }

        }

        cout << "Ganador: " << ganador->getNombre();

    }

}

/**
 * Define quien es el jugador que continua en turno.
 */
void Juego::siguienteTurno() {
    if (enTurno == j1) {
        setEnTurno(j2);
    } else if (enTurno == j2) {
        setEnTurno(j3);
    } else if (enTurno == j3) {
        setEnTurno(j4);
    } else {
        setEnTurno(j1);
    }
}


