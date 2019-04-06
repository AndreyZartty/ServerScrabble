
#ifndef FICHAS_JUEGO_H
#define FICHAS_JUEGO_H


#include "Jugador.h"
#include "FichaCreator.h"
#include "Cuadricula.h"


/**
 * Header de Juego.
 *
 * @author Ruben Salas
 * @since 27/03/19
 */
class Juego {

private:
    string codigo;
    int cantJugadoresPermitidos;
    int cantJugadoresActuales;
    Jugador* j1;
    Jugador* j2;
    Jugador* j3;
    Jugador* j4;
    Cuadricula* cuadricula;
    FichaCreator* creator;
    List* poolFichas;
    int cantFichas;
    bool terminado;
    bool iniciado;
    Jugador* enTurno;
    Jugador* ganador;

public:
    Juego(int _cantJugadoresPermitidos);

    //Getters & Setters
    string getCodigo();
    void setCodigo(string _codigo);
    int getCantJugadoresPermitidos();
    void setCantJugadoresPermitidos(int _cantJugadoresPermitidos);
    int getCantJugadoresActuales();
    void setCantJugadoresActuales(int _cantJugadoresActuales);
    Jugador* getJ1();
    void setJ1(Jugador* _j1);
    Jugador* getJ2();
    void setJ2(Jugador* _j2);
    Jugador* getJ3();
    void setJ3(Jugador* _j3);
    Jugador* getJ4();
    void setJ4(Jugador* _j4);
    Cuadricula* getCuadricula();
    void setCuadricula(Cuadricula* _cuadricula);
    FichaCreator* getCreator();
    void setCreator(FichaCreator* _creator);
    List* getPoolFichas();
    void setPoolFichas(List* _poolFichas);
    int getCantFichas();
    void setCantFichas(int _cantFichas);
    Jugador* getEnTurno();
    void setEnTurno(Jugador* _jugador);
    bool isTerminado();
    void setTerminado(bool _terminado);
    bool isIniciado();
    void setIniciado(bool _iniciado);

    Jugador* getGanador();
    void setGanador(Jugador *ganador);

    //Funciones
    void generarCodigo();
    void generarCodigo(int numJuego);
    void addJugador(string nombre);
    void crearFichas();
    void repartirFichas();
    void completarFichas(Jugador* jugador);
    void checkTurnosPasados();
    void checkTerminado();
    void siguienteTurno();


};


#endif //FICHAS_JUEGO_H
