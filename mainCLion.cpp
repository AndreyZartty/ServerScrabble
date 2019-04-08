#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <typeinfo>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <json-c/json.h>
#include <string>
#include <arpa/inet.h>

#include "Juego.h"

#define PORT 3550
#define BACKLOG 20
#define MAXDATASIZE 1000

using namespace std;


///Variable estática: cantidad máxima de Juegos
static int cantMaximaJuegos = 25;
///Variable estática: cantidad de Juegos activos en el servidor
static int cantJuegosActuales = 0;
///Variable estática: Array con los juegos activos (Cantidad máxima de juegos será predefinida)
static Juego* juegosActuales[10];


/**
 * Crea una instancia de la clase juego y la ingresa en el array de juegos actuales.
 * @param cantJugadores - cantidad de jugadores permitidos en la partida [2-4]
 * @returns numero del juego (utilizado para saber que juego iniciar)
 */
int juegoNuevo(int cantJugadores) {
    if (cantJuegosActuales < cantMaximaJuegos ) {
        ///Instancia el objeto Juego
        Juego* nJuego = new Juego(cantJugadores);
        ///Lo agrega en la siguiente posicion sin juego guardado
        juegosActuales[cantJuegosActuales] = nJuego;
        ///Manda a generar el codigo del juego
        // (PRUEBAS: Esta utilizando la cantidad de Juegos Actuales para generar un codigo mientras)
        //juegosActuales[cantJuegosActuales]->generarCodigo(cantJuegosActuales+1);

        juegosActuales[cantJuegosActuales]->generarCodigo();
        ///Actualiza la cantidad de juegos actuales con el recien creado
        cantJuegosActuales++;


        //*************************************Consola*********************************************************

        cout << "\nJuego nuevo creado!" << endl;
        cout << "Juegos activos: " << cantJuegosActuales << endl;

        //*************************************Consola*********************************************************

        return cantJuegosActuales - 1;

    } else {

        cout << "\nLimite de juegos activos alcanzado." << endl;

        return -1;
    }

}


/**
 * Buscará un juego por medio de su codigo
 * @param codigo - para encontrarlo
 * @returns numero del juego que se necesita
 */
int getJuego(string codigo){

    int i = 0;
    while (i < cantJuegosActuales) {

        if (codigo == juegosActuales[i]->getCodigo()) {

            cout << "Se modificará el Juego #" << i+1 << " con codigo: " << juegosActuales[i]->getCodigo() << endl;
            return i;
        }
        i++;
    }

    return -1;

}


/**
 * Funcion inicial del juego.
 * Crea un nuevo juego y comienza con las preparaciones para que el juego comience.
 * @param cantJugadoresPermitidos - cantidad de jugadores maximos en el juego
 * @param nombreJugador - string del nombre del jugador
 */
string iniciar(string cantJugadoresPermitidos, string nombreJugador) {
    //Crea un nuevo juego y retorna que numero de juego es
    int numJuego = juegoNuevo(stoi(cantJugadoresPermitidos));

    if (numJuego >= 0 && numJuego <= cantMaximaJuegos) {
        ///Guarda el juego actual, recien creado, en una variable
        Juego* juegoActual = juegosActuales[numJuego];

        ///Crea las fichas del juego
        juegoActual->crearFichas();

        ///Ingresa al jugador que manda a crear el juego como Jugador1
        juegoActual->addJugador(nombreJugador);


        //*************************************Consola*********************************************************

        //Cantidad de jugadores
        cout << "\nCantidad de Jugadores Actuales en Juego(" << juegoActual->getCodigo()
                                    << ") : " << juegoActual->getCantJugadoresActuales() << "\n" << endl;

        //Cantidad inicial de fichas
        cout<<"\nPool de fichas"<<endl;
        juegoActual->getPoolFichas()->printList();

        //*****************************************************************************************************


        json_object *jobjSendCodigo = json_object_new_object();


        json_object *jstringCodigo = json_object_new_string(juegoActual->getCodigo().c_str());


        json_object_object_add(jobjSendCodigo,"CODIGO", jstringCodigo);


        return json_object_to_json_string(jobjSendCodigo);


    }
    ///Cuando ya no se pueden crear mas juegos
    else {
        cout << "\nPor favor intente ingresar luego." << endl;
        ///Servidor deberia devolver un mensaje en pantalla diciendo que espere a que termine un juego


        json_object *jobjSendErrorCodigo = json_object_new_object();


        json_object *jstringErrorCodigo = json_object_new_string("Máxima cantidad de juegos activos alcanzada."
                                          "\nPor favor intente ingresar luego.");


        json_object_object_add(jobjSendErrorCodigo,"ERRORCODIGO", jstringErrorCodigo);


        cout << "Máxima cantidad de juegos activos alcanzada.\nPor favor intente ingresar luego." << endl;


        return json_object_to_json_string(jobjSendErrorCodigo);

    }

}



/**
 * Comienza el juego, se reparten las fichas y el primer turno es decidido.
 * @param codigo - para saber que juego comenzar
 */
void comenzarJuego(string codigo) {

    int numJuego = getJuego(codigo);

    if (numJuego >= 0) {

        ///Guarda el juego que se modificará en una variable
        Juego* juegoActual = juegosActuales[numJuego];

        ///Pone como iniciado el juego
        juegoActual->setIniciado(true);

        ///Repartirá las fichas a los jugadores
        juegoActual->repartirFichas();

        ///Define quien comenzará en el primer turno
        juegoActual->setEnTurno(juegoActual->getJ1());

        //*************************************Consola*********************************************************

        //Cantidad final de fichas
        cout << "\nPool de fichas de Juego(" << codigo << ")" << endl;
        juegoActual->getPoolFichas()->printList();

        //Imprime el jugador en turno
        cout << "\nJugador en turno: " << juegoActual->getEnTurno()->getNombre() << endl;

        //*****************************************************************************************************

    }
    ///Cuando no hay juegos definidos
    else {
        cout << "No se puede comenzar el juego, si este no está definido." << endl;
    }

}



/**
 * Verifica el comienzo del juego
 * @param codigo
 * @return json de confirmacion de verificacion
 */
string verificarComenzado(string codigo) {
    int numJuego = getJuego(codigo);

    if (numJuego >= 0) {

        ///Guarda el juego que se modificará en una variable
        Juego* juegoActual = juegosActuales[numJuego];


        json_object *jobjComenzar = json_object_new_object();

        string iniciadoBool;

        if (juegoActual->isIniciado() == true) {
            iniciadoBool = "TRUE";
        } else {
            iniciadoBool = "FALSE";
        }


        json_object *jstringComenzar = json_object_new_string(iniciadoBool.c_str());


        json_object_object_add(jobjComenzar,"JUGARSRV", jstringComenzar);


        return json_object_to_json_string(jobjComenzar);


    }
        ///Cuando no hay juegos definidos
    else {
        cout << "No se puede comenzar el juego, si este no está definido." << endl;

        json_object *jobjComenzar = json_object_new_object();


        json_object *jstringComenzar = json_object_new_string("FALSE");


        json_object_object_add(jobjComenzar,"COMENZAR", jstringComenzar);


        return json_object_to_json_string(jobjComenzar);
    }

}


/**
 * Agrega un jugador nuevo al juego que se indica.
 * @param codigo
 * @param nombreJugador
 * @return json con confirmacion de agregado
 */
string jugadorNuevo(string codigo, string nombreJugador) {

    int numJuego = getJuego(codigo);

    if (numJuego >= 0) {

        ///Guarda el juego que se modificará en una variable
        Juego* juegoActual = juegosActuales[numJuego];

        ///Ingresa al nuevo jugador
        bool isAdded = juegoActual->addJugador(nombreJugador);

        if (isAdded == true) {

            ///Verifica si el juego está listo para iniciar cuando todos los jugadores estén completos
            bool comenzar = juegoActual->checkJugadoresCompletos();

            json_object *jobjJugador = json_object_new_object();

            string strConfirmacion = nombreJugador + " ha sido agregador al juego!";

            json_object *json_confirmacion = json_object_new_string(strConfirmacion.c_str());

            string strComenzar = "FALSE";

            if (comenzar == true) {
                strComenzar = "TRUE";
                comenzarJuego(codigo);
            }

            json_object *json_comenzar = json_object_new_string(strComenzar.c_str());

            json_object_object_add(jobjJugador,"CONFIRMACION", json_confirmacion);
            json_object_object_add(jobjJugador,"COMENZAR", json_comenzar);



            //*************************************Consola*********************************************************

            //Cantidad de jugadores
            cout << "\nCantidad de Jugadores Actuales en Juego(" << juegoActual->getCodigo()
                 << ") : " << juegoActual->getCantJugadoresActuales() << "\n" << endl;

            //*****************************************************************************************************


            return json_object_to_json_string(jobjJugador);


        } else {

            cout << "Todos los espacios disponibles estan ocupados." << endl;


            json_object *jobjJugador = json_object_new_object();

            string strConfirmacion = "Todos los espacios disponibles estan ocupados.";

            json_object *json_confirmacion = json_object_new_string(strConfirmacion.c_str());

            json_object_object_add(jobjJugador,"CONFIRMACION", json_confirmacion);

            return json_object_to_json_string(jobjJugador);

        }

    }
        ///Cuando no hay juegos definidos
    else {
        cout << "No se puede ingresar el juego, si este no está definido." << endl;


        json_object *jobjJugador = json_object_new_object();

        string strConfirmacion = "No se puede ingresar el juego, si este no está definido.";

        json_object *json_confirmacion = json_object_new_string(strConfirmacion.c_str());

        json_object_object_add(jobjJugador,"CONFIRMACION", json_confirmacion);

        return json_object_to_json_string(jobjJugador);

    }

}


/**
 * Obtiene los nombres de todos los jugadores conectados al juego con el mismo codigo
 * @param codigo
 * @return json con los nombres
 */
string getNombres(string codigo) {

    int numJuego = getJuego(codigo);

    if (numJuego >= 0) {

        ///Guarda el juego que se modificará en una variable
        Juego *juegoActual = juegosActuales[numJuego];

        int cantJugadores = juegoActual->getCantJugadoresActuales();

        ///Crea un JSON para mandar los nombres de los jugadores para graficarlos
        json_object *jobjNombres = json_object_new_object();

        if (cantJugadores == 2) {


            ///Obtiene el nombre del jugador1
            string strJugador1 = juegoActual->getJ1()->getNombre();
            ///Obtiene el nombre del jugador2
            string strJugador2 = juegoActual->getJ2()->getNombre();;

            ///Los hace un JSON
            json_object *json_Jugador1 = json_object_new_string(strJugador1.c_str());
            json_object *json_Jugador2 = json_object_new_string(strJugador2.c_str());

            ///Se ingresan a un JSON con su respectivo KEY
            json_object_object_add(jobjNombres, "JUGADOR1", json_Jugador1);
            json_object_object_add(jobjNombres, "JUGADOR2", json_Jugador2);


        } else if (cantJugadores == 3) {

            ///Obtiene el nombre del jugador1
            string strJugador1 = juegoActual->getJ1()->getNombre();
            ///Obtiene el nombre del jugador2
            string strJugador2 = juegoActual->getJ2()->getNombre();;
            ///Obtiene el nombre del jugador3
            string strJugador3 = juegoActual->getJ3()->getNombre();

            ///Los hace un JSON
            json_object *json_Jugador1 = json_object_new_string(strJugador1.c_str());
            json_object *json_Jugador2 = json_object_new_string(strJugador2.c_str());
            json_object *json_Jugador3 = json_object_new_string(strJugador3.c_str());

            ///Se ingresan a un JSON con su respectivo KEY
            json_object_object_add(jobjNombres, "JUGADOR1", json_Jugador1);
            json_object_object_add(jobjNombres, "JUGADOR2", json_Jugador2);
            json_object_object_add(jobjNombres, "JUGADOR3", json_Jugador3);

        } else {

            ///Obtiene el nombre del jugador1
            string strJugador1 = juegoActual->getJ1()->getNombre();
            ///Obtiene el nombre del jugador2
            string strJugador2 = juegoActual->getJ2()->getNombre();
            ///Obtiene el nombre del jugador3
            string strJugador3 = juegoActual->getJ3()->getNombre();
            ///Obtiene el nombre del jugador4
            string strJugador4 = juegoActual->getJ4()->getNombre();

            ///Los hace un JSON
            json_object *json_Jugador1 = json_object_new_string(strJugador1.c_str());
            json_object *json_Jugador2 = json_object_new_string(strJugador2.c_str());
            json_object *json_Jugador3 = json_object_new_string(strJugador3.c_str());
            json_object *json_Jugador4 = json_object_new_string(strJugador4.c_str());

            ///Se ingresan a un JSON con su respectivo KEY
            json_object_object_add(jobjNombres, "JUGADOR1", json_Jugador1);
            json_object_object_add(jobjNombres, "JUGADOR2", json_Jugador2);
            json_object_object_add(jobjNombres, "JUGADOR3", json_Jugador3);
            json_object_object_add(jobjNombres, "JUGADOR4", json_Jugador4);

        }

        return json_object_to_json_string(jobjNombres);
    }

        ///Cuando no hay juegos definidos
    else {
        cout << "No se puede ingresar el juego, si este no está definido." << endl;


        json_object *jobjJugador = json_object_new_object();

        string strConfirmacion = "No se puede ingresar el juego, si este no está definido.";

        json_object *json_confirmacion = json_object_new_string(strConfirmacion.c_str());

        json_object_object_add(jobjJugador, "ERROR", json_confirmacion);

        return json_object_to_json_string(jobjJugador);

    }

}


/**
 * Pasa de turno, cambia de jugador enTurno y verifica si el juego podria terminar
 * @param codigo - para saber en que juego pasar el turno
 * @return nombre de jugador en turno
 */
string pasarTurno(string codigo) {

    int numJuego = getJuego(codigo);

    if (numJuego >= 0) {

        ///Guarda el juego que se modificará en una variable
        Juego *juegoActual = juegosActuales[numJuego];

        ///Agrega +1 a los turnos pasados del jugador enTurno
        juegoActual->getEnTurno()->setTurnosPasados(juegoActual->getEnTurno()->getTurnosPasados() + 1);

        ///Verifica los turnos seguidos de todos los jugadores
        juegoActual->checkTurnosPasados();

        ///Verifica que el juego no haya terminado
        juegoActual->checkTerminado();

        ///Pasa al siguiente turno con un nuevo jugador enTurno
        juegoActual->siguienteTurno();

        json_object *jobjPasar = json_object_new_object();

        string strPasar = juegoActual->getEnTurno()->getNombre();

        json_object *json_Pasar = json_object_new_string(strPasar.c_str());

        json_object_object_add(jobjPasar, "PASAR", json_Pasar);


        //*************************************Consola*********************************************************

        //Imprime el jugador en turno
        cout << "\nJugador en turno: " << juegoActual->getEnTurno()->getNombre() << endl;

        //*****************************************************************************************************


        return json_object_to_json_string(jobjPasar);


    }
    ///Cuando no hay juegos definidos
    else {
        cout << "No se puede pasar el turno en el juego, si este no está definido." << endl;

        json_object *jobjPasar = json_object_new_object();

        string strPasar = "No se puede pasar el turno en el juego, si este no está definido.";

        json_object *json_Pasar = json_object_new_string(strPasar.c_str());

        json_object_object_add(jobjPasar, "ERROR", json_Pasar);

        return json_object_to_json_string(jobjPasar);
    }

}

/**
 * Envia el jugador en turno
 * @param codigo
 * @return nombre de jugador en turno
 */
string sendEnTurno(string codigo) {

    int numJuego = getJuego(codigo);

    if (numJuego >= 0) {

        ///Guarda el juego que se modificará en una variable
        Juego *juegoActual = juegosActuales[numJuego];

        string nombreEnTurno = juegoActual->getEnTurno()->getNombre();

        json_object *jobjEnTurno = json_object_new_object();

        string strEnTurno = juegoActual->getEnTurno()->getNombre();

        json_object *json_EnTurno = json_object_new_string(strEnTurno.c_str());

        json_object_object_add(jobjEnTurno, "TURNO", json_EnTurno);

        return json_object_to_json_string(jobjEnTurno);


    }
        ///Cuando no hay juegos definidos
    else {
        cout << "No se puede pasar el turno en el juego, si este no está definido." << endl;

        json_object *jobjPasar = json_object_new_object();

        string strPasar = "No se puede pasar el turno en el juego, si este no está definido.";

        json_object *json_Pasar = json_object_new_string(strPasar.c_str());

        json_object_object_add(jobjPasar, "ERROR", json_Pasar);

        return json_object_to_json_string(jobjPasar);
    }
}



/**
 * Lee un archivo de texto con las palabras
 * @param nombre
 * @param dcc
 */
void lectura(string nombre, string dcc[]) {
    fstream datos(nombre.c_str());
    string linea;
    int c = 0;
    if (!datos.is_open()) {
        datos.open(nombre.c_str(), ios::in);
    }
    if (nombre == "ServerScrabble/diccio.txt") {
        while (getline(datos, linea)) {
            //cout << linea << endl;
            dcc[c] = linea;
            c++;
        }
        datos.close();
    } else {
        cout << "Fichero inexistente" << endl;
    }
}


/**
 * Verifica si la palabra existe en el diccionario.
 * @param nueva
 * @return bool de si encontró la palabra en el diccionario
 */
string verificarPalabraAux(string nueva) {
    int aDcc = 186594;
    string diccionario[190000] = {};
    lectura("ServerScrabble/diccio.txt", diccionario);
    int c = 0;
    while (c < aDcc) {
        string actual = diccionario[c].substr(0, diccionario[c].length() - 1);
        //cout << actual << endl;
        if (actual.compare(nueva) == 0) {
            string strResultado = "La palabra '" + nueva + "' se encuentra en el diccionario en la posición: " + to_string(c) ;
            cout << strResultado << endl;

            return "true";
        }
        c++;
    }
    string strResultado = "La palabra '" + nueva + "' no se encuentra en el diccionario.";
    cout << strResultado << endl;

    ///Retornará un "false" que será verificado en el servidor

    return "false";

}


/**
 * Concatena las fichas que se ponen en la cuadricula
 * @param codigo
 * @param F1L
 * @param F1P
 * @param F2L
 * @param F2P
 * @param F3L
 * @param F3P
 * @param F4L
 * @param F4P
 * @param F5L
 * @param F5P
 * @param F6L
 * @param F6P
 * @param F7L
 * @param F7P
 * @return verificacion de existencia de palabra y su correcta posicion
 */
string concatenarFichas(string codigo, string F1L, string F1P, string F2L, string F2P,
                        string F3L, string F3P, string F4L, string F4P,
                        string F5L, string F5P, string F6L, string F6P,
                        string F7L, string F7P) {

    int numJuego = getJuego(codigo);

    if (numJuego >= 0) {

        ///Guarda el juego que se modificará en una variable
        Juego *juegoActual = juegosActuales[numJuego];

        Jugador* jugadorEnTurno = juegoActual->getEnTurno();

        if (F1L != "") {
            Ficha* fichaPorPasar = jugadorEnTurno->getListaFichas()->getNode(F1L)->getFicha();
            int fila = F1P[0];
            int columna = F1P[1];

            juegoActual->getCuadricula()->addFicha(fila, columna, fichaPorPasar);
        }

        if (F2L != "") {
            Ficha* fichaPorPasar = jugadorEnTurno->getListaFichas()->getNode(F2L)->getFicha();
            int fila = F2P[0];
            int columna = F2P[1];

            juegoActual->getCuadricula()->addFicha(fila, columna, fichaPorPasar);
        }

        if (F3L != "") {
            Ficha* fichaPorPasar = jugadorEnTurno->getListaFichas()->getNode(F3L)->getFicha();
            int fila = F3P[0];
            int columna = F3P[1];

            juegoActual->getCuadricula()->addFicha(fila, columna, fichaPorPasar);
        }

        if (F4L != "") {
            Ficha* fichaPorPasar = jugadorEnTurno->getListaFichas()->getNode(F4L)->getFicha();
            int fila = F4P[0];
            int columna = F4P[1];

            juegoActual->getCuadricula()->addFicha(fila, columna, fichaPorPasar);
        }

        if (F5L != "") {
            Ficha* fichaPorPasar = jugadorEnTurno->getListaFichas()->getNode(F5L)->getFicha();
            int fila = F5P[0];
            int columna = F5P[1];

            juegoActual->getCuadricula()->addFicha(fila, columna, fichaPorPasar);
        }

        if (F6L != "") {
            Ficha* fichaPorPasar = jugadorEnTurno->getListaFichas()->getNode(F6L)->getFicha();
            int fila = F6P[0];
            int columna = F6P[1];

            juegoActual->getCuadricula()->addFicha(fila, columna, fichaPorPasar);
        }

        if (F7L != "") {
            Ficha* fichaPorPasar = jugadorEnTurno->getListaFichas()->getNode(F7L)->getFicha();
            int fila = F7P[0];
            int columna = F7P[1];

            juegoActual->getCuadricula()->addFicha(fila, columna, fichaPorPasar);
        }


        string palabraPorVerificar = F1L + F2L + F3L + F4L + F5L + F6L + F7L;

        string resultadoVerificacion = verificarPalabraAux(palabraPorVerificar);

        json_object *jobjVerificacion = json_object_new_object();

        json_object *json_Verificacion;

        ///Cuando la palabra no exista
        if (resultadoVerificacion == "false") {

            json_Verificacion = json_object_new_string(resultadoVerificacion.c_str());

        }
        ///Cuando la palabra exista, se enviará el puntaje del jugador
        else {

            json_Verificacion = json_object_new_string(resultadoVerificacion.c_str());

        }

        json_object_object_add(jobjVerificacion, "VERIFICACION", json_Verificacion);

        return json_object_to_json_string(jobjVerificacion);

    }
        ///Cuando no hay juegos definidos
    else {
        cout << "No se puede hacer Scrabble! en el juego, si este no está definido." << endl;

        json_object *jobjScrabble = json_object_new_object();

        string strScrabble = "No se puede hacer Scrabble! en el juego, si este no está definido.";

        json_object *json_Scrabble = json_object_new_string(strScrabble.c_str());

        json_object_object_add(jobjScrabble, "ERROR", json_Scrabble);

        return json_object_to_json_string(jobjScrabble);

    }

}


/**
 * Boton Scrabble!
 * @param codigo - para saber en que juego pasar el turno
 */
string scrabble(string codigo){
    int numJuego = getJuego(codigo);

    if (numJuego >= 0) {

        cout << "\nCall a Scrabble!" << endl;
    }
    ///Cuando no hay juegos definidos
    else {

        cout << "No se puede hacer Scrabble! en el juego, si este no está definido." << endl;

    }
}


/**
 * Main del programa.
 * Implementación del servidor.
 *
 * @author Ruben Salas
 * @since 26/03/19.
 */
int main(int argc, char **argv) {

    int fd, fd2;

    struct sockaddr_in server;

    struct sockaddr_in client;


    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("error en socket()\n");
        exit(-1);
    }

    server.sin_family = AF_INET;

    server.sin_port = htons(PORT);

    server.sin_addr.s_addr = INADDR_ANY;

    bzero(&(server.sin_zero), 8);

    if (bind(fd, (struct sockaddr *) &server,
            sizeof(struct sockaddr)) == -1) {
        printf("error en bind() \n");
        exit(-1);
    }

    if (listen(fd, BACKLOG) == -1) {
        printf("error en listen()\n");
        exit(-1);
    }

    printf("Servidor 'Scrabble!' abierto.\n");

    while (true) {

        unsigned int address_size = sizeof(client);

        if ((fd2 = accept(fd, (struct sockaddr *) &client,
                              &address_size)) == -1) {
            printf("error en accept()\n");
            exit(-1);
        }

        printf("\n\nSe obtuvo una conexión de un cliente.\n");

        ssize_t r;

        char buff[MAXDATASIZE];

        for (;;) {
            r = read(fd2, buff, MAXDATASIZE);

            if (r == -1) {
                perror("read");
                return EXIT_FAILURE;
            }
            if (r == 0)
                break;
            printf("READ: %s\n", buff);


            ///JSON Reads & Writes


            ///KEY: JUGADOR
            ///Obtiene el nombre del jugador ingresado en el cliente.
            struct json_object *tempJugador;
            cout<<"TEST1"<<endl;
            json_object *parsed_jsonJugador = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonJugador, "JUGADOR", &tempJugador);
            printf("Jugador: %s\n", json_object_get_string(tempJugador));

            ///KEY: JUGADORES PERMITIDOS
            ///Obtiene la cantidad de jugadores permitidos ingresado en el cliente.
            struct json_object *tempCantidad;
            cout<<"TEST2"<<endl;
            json_object *parsed_jsonCantidad = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonCantidad, "JUGADORES PERMITIDOS", &tempCantidad);
            printf("Jugadores Permitidos: %s\n", json_object_get_string(tempCantidad));

            ///KEY: IP
            ///Obtiene la IP proveniente del cliente para saber que cliente modificar
            struct json_object *tempIP;
            cout<<"TEST3"<<endl;
            json_object *parsed_jsonIP = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonIP, "IP", &tempIP);
            printf("IP: %s\n", json_object_get_string(tempIP));

            ///KEY: CODIGO
            ///Obtiene el codigo proveniente del cliente para saber que juego modificar
            struct json_object *tempCodigo;
            cout<<"TEST4"<<endl;
            json_object *parsed_jsonCodigo = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonCodigo, "CODIGO", &tempCodigo);
            printf("Codigo: %s\n", json_object_get_string(tempCodigo));

            ///KEY: JUGARCL
            ///Obtiene la espera de los jugadores por iniciar.
            struct json_object *tempComenzar;
            cout<<"TEST5"<<endl;
            json_object *parsed_jsonComenzar = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonComenzar, "JUGARCL", &tempComenzar);
            printf("Status para Jugar: %s\n", json_object_get_string(tempComenzar));

            ///KEY: NOMBRES
            ///Obtiene un request para obtener los nombres de los jugadores para graficarlos.
            struct json_object *tempNombres;
            cout<<"TEST6"<<endl;
            json_object *parsed_jsonNombres = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonNombres, "NOMBRES", &tempNombres);
            printf("Nombres: %s\n", json_object_get_string(tempNombres));

            ///KEY: PASAR
            ///Obtiene un request para pasar de turno
            struct json_object *tempPasar;
            cout<<"TEST7"<<endl;
            cout<<buff<<endl;
            json_object *parsed_jsonPasar = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonPasar, "PASAR", &tempPasar);
            printf("Pasar: %s\n", json_object_get_string(tempPasar));

            ///KEY: TURNO
            ///Obtiene un request para obtener quien esta en turno
            struct json_object *tempTurno;
            cout<<"TEST8"<<endl;
            json_object *parsed_jsonTurno = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonTurno, "TURNO", &tempTurno);
            printf("Turno: %s\n", json_object_get_string(tempTurno));

            ///KEY: PALABRA
            ///Obtiene un request para verificar la palabra
            struct json_object *tempPalabra;
            cout<<"TEST9"<<endl;
            json_object *parsed_jsonPalabra = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonPalabra, "PALABRA", &tempPalabra);
            printf("Palabra: %s\n", json_object_get_string(tempPalabra));


            ///LETRA FICHAS


            ///KEY: F1L
            ///Obtiene la Letra de la Ficha 1
            struct json_object *tempF1L;
            json_object *parsed_jsonF1L = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF1L, "F1L", &tempF1L);
            printf("F1L: %s\n", json_object_get_string(tempF1L));

            ///KEY: F2L
            ///Obtiene la Letra de la Ficha 2
            struct json_object *tempF2L;
            json_object *parsed_jsonF2L = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF2L, "F2L", &tempF2L);
            printf("F2L: %s\n", json_object_get_string(tempF2L));

            ///KEY: F3L
            ///Obtiene la Letra de la Ficha 3
            struct json_object *tempF3L;
            json_object *parsed_jsonF3L = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF3L, "F3L", &tempF3L);
            printf("F3L: %s\n", json_object_get_string(tempF3L));

            ///KEY: F4L
            ///Obtiene la Letra de la Ficha 4
            struct json_object *tempF4L;
            json_object *parsed_jsonF4L = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF4L, "F4L", &tempF4L);
            printf("F4L: %s\n", json_object_get_string(tempF4L));

            ///KEY: F5L
            ///Obtiene la Letra de la Ficha 5
            struct json_object *tempF5L;
            json_object *parsed_jsonF5L = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF5L, "F5L", &tempF5L);
            printf("F5L: %s\n", json_object_get_string(tempF5L));

            ///KEY: F6L
            ///Obtiene la Letra de la Ficha 6
            struct json_object *tempF6L;
            json_object *parsed_jsonF6L = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF6L, "F6L", &tempF6L);
            printf("F6L: %s\n", json_object_get_string(tempF6L));

            ///KEY: F7L
            ///Obtiene la Letra de la Ficha 7
            struct json_object *tempF7L;
            json_object *parsed_jsonF7L = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF7L, "F7L", &tempF7L);
            printf("F7L: %s\n", json_object_get_string(tempF7L));


            ///POSICION & FICHAS


            ///KEY: F1P
            ///Obtiene la Posicion de la Ficha 1
            struct json_object *tempF1P;
            json_object *parsed_jsonF1P = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF1P, "F1P", &tempF1P);
            printf("F1P: %s\n", json_object_get_string(tempF1P));

            ///KEY: F2P
            ///Obtiene la Posicion de la Ficha 2
            struct json_object *tempF2P;
            json_object *parsed_jsonF2P = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF2P, "F2P", &tempF2P);
            printf("F2P: %s\n", json_object_get_string(tempF2P));

            ///KEY: F3P
            ///Obtiene la Posicion de la Ficha 3
            struct json_object *tempF3P;
            json_object *parsed_jsonF3P = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF3P, "F3P", &tempF3P);
            printf("F3P: %s\n", json_object_get_string(tempF3P));

            ///KEY: F4P
            ///Obtiene la Posicion de la Ficha 4
            struct json_object *tempF4P;
            json_object *parsed_jsonF4P = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF4P, "F4P", &tempF4P);
            printf("F4P: %s\n", json_object_get_string(tempF4P));

            ///KEY: F5P
            ///Obtiene la Posicion de la Ficha 5
            struct json_object *tempF5P;
            json_object *parsed_jsonF5P = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF5P, "F5P", &tempF5P);
            printf("F5P: %s\n", json_object_get_string(tempF5P));

            ///KEY: F6P
            ///Obtiene la Posicion de la Ficha 6
            struct json_object *tempF6P;
            json_object *parsed_jsonF6P = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF6P, "F6P", &tempF6P);
            printf("F6P: %s\n", json_object_get_string(tempF6P));

            ///KEY: F7P
            ///Obtiene la Posicion de la Ficha 7
            struct json_object *tempF7P;
            json_object *parsed_jsonF7P = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonF7P, "F7P", &tempF7P);
            printf("F7P: %s\n", json_object_get_string(tempF7P));


            ///JSON Verificaciones

            ///Creacion del juego
            ///Verifica que reciba los KEYS: JUGADORES PERMITIDOS Y JUGADOR
            if (json_object_get_string(tempCantidad) != 0 && json_object_get_string(tempJugador) != 0 && json_object_get_string(tempIP) != 0) {
                ///JSON saliente del servidor
                string codigoCliente = iniciar(json_object_get_string(tempCantidad),
                                                           json_object_get_string(tempJugador));
                ///Envio al cliente
                send(fd2, codigoCliente.c_str(), MAXDATASIZE, 0);
            }

            ///Vinculará al jugador a un juego
            ///Verifica que reciba los KEYS: CODIGO Y JUGADOR
            if (json_object_get_string(tempCodigo) != 0 && json_object_get_string(tempJugador) != 0) {
                ///JSON saliente del servidor
                string statusJugadorCliente = jugadorNuevo(json_object_get_string(tempCodigo),
                                                               json_object_get_string(tempJugador));
                ///Envio al cliente
                send(fd2, statusJugadorCliente.c_str(), MAXDATASIZE, 0);
            }

            ///Llama a funcion para verificar la instruccion
            ///Verifica que reciba los KEYS: CODIGO Y COMENZAR
            if (json_object_get_string(tempCodigo) != 0 && json_object_get_string(tempComenzar) != 0) {
                ///JSON saliente del servidor
                string comenzar = verificarComenzado(json_object_get_string(tempCodigo));
                ///Envio al cliente
                send(fd2, comenzar.c_str(), MAXDATASIZE, 0);
            }

            ///Obtendrá los nombres de los jugadores en el juego
            ///Verifica que reciba los KEYS: NOMBRES Y CODIGO
            if (json_object_get_string(tempCodigo) != 0 && json_object_get_string(tempNombres) != 0) {
                ///JSON saliente del servidor
                string nombres = getNombres(json_object_get_string(tempCodigo));
                ///Envio al cliente
                send(fd2, nombres.c_str(), MAXDATASIZE, 0);
            }

            ///Obtendrá un request para pasar de turno
            ///Verifica que reciba los KEYS: PASAR Y CODIGO
            if (json_object_get_string(tempCodigo) != 0 && json_object_get_string(tempPasar) != 0) {
                ///JSON saliente del servidor
                string pasar = pasarTurno(json_object_get_string(tempCodigo));
                ///Envio al cliente
                send(fd2, pasar.c_str(), MAXDATASIZE, 0);
            }

            ///Obtendra un request para obtener quien esta en turno
            ///Verifica que reciba los KEYS: TURNO Y CODIGO
            if (json_object_get_string(tempCodigo) != 0 && json_object_get_string(tempTurno) != 0) {
                ///JSON saliente del servidor
                string enTurno = sendEnTurno(json_object_get_string(tempCodigo));
                ///Envio al cliente
                send(fd2, enTurno.c_str(), MAXDATASIZE, 0);
            }

            ///Verifica que reciba los  KEYS: CODIGO, --LETRAS-- Y --POSICIONES
            ///Obtendra un request para verificar las letras recien puestas en el tablero
            if (json_object_get_string(tempCodigo) != 0 && json_object_get_string(tempF1L) != 0 && json_object_get_string(tempF1P) != 0) {

                string f1l = json_object_get_string(tempF1L);
                string f1p = json_object_get_string(tempF1P);
                string f2l = "";
                string f2p = "";
                string f3l = "";
                string f3p = "";
                string f4l = "";
                string f4p = "";
                string f5l = "";
                string f5p = "";
                string f6l = "";
                string f6p = "";
                string f7l = "";
                string f7p = "";

                if (json_object_get_string(tempF2L) != 0 && json_object_get_string(tempF2P) != 0) {

                    f2l = json_object_get_string(tempF2L);
                    f2p = json_object_get_string(tempF2P);

                    if (json_object_get_string(tempF3L) != 0 && json_object_get_string(tempF3P) != 0) {

                        f3l = json_object_get_string(tempF3L);
                        f3p = json_object_get_string(tempF3P);

                        if (json_object_get_string(tempF4L) != 0 && json_object_get_string(tempF4P) != 0) {

                            f4l = json_object_get_string(tempF4L);
                            f4p = json_object_get_string(tempF4P);

                            if (json_object_get_string(tempF5L) != 0 && json_object_get_string(tempF5P) != 0) {

                                f5l = json_object_get_string(tempF5L);
                                f5p = json_object_get_string(tempF5P);

                                if (json_object_get_string(tempF6L) != 0 && json_object_get_string(tempF6P) != 0) {

                                    f6l = json_object_get_string(tempF6L);
                                    f6p = json_object_get_string(tempF6P);

                                    if (json_object_get_string(tempF7L) != 0 && json_object_get_string(tempF7P) != 0) {

                                        f7l = json_object_get_string(tempF7L);
                                        f7p = json_object_get_string(tempF7P);

                                    }

                                }

                            }

                        }

                    }

                }
                ///JSON saliente del servidor
                string concatenacionPalabra = concatenarFichas(json_object_get_string(tempCodigo),
                        f1l, f1p, f2l, f2p, f3l, f3p, f4l, f4p, f5l, f5p, f6l, f6p, f7l, f7p);
                ///Envio al cliente
                send(fd2, concatenacionPalabra.c_str(), MAXDATASIZE, 0);

            }


            ///Reestablece el buffer
            memset(buff, 0, MAXDATASIZE);


            cout <<
            "\n\n--------------------------------------------------------------------------------"
            "END--------------------------------------------------------------------------------\n"
            << endl;


        }

        close(fd2);

    }

}
