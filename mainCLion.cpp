#include <iostream>
#include <typeinfo>
#include "Juego.h"


//*********************************

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
#include <iostream>

#define PORT 3550
#define BACKLOG 20
#define MAXDATASIZE 1000

//*********************************


using namespace std;


///Variable estática: cantidad de Juegos activos en el servidor
static int cantJuegosActuales = 0;
///Variable estática: Array con los juegos activos (Cantidad máxima de juegos será predefinida)
static Juego* juegosActuales[5];



/**
 * Crea una instancia de la clase juego y la ingresa en el array de juegos actuales.
 * @param cantJugadores - cantidad de jugadores permitidos en la partida [2-4]
 * @returns numero del juego (utilizado para saber que juego iniciar)
 */
int juegoNuevo(int cantJugadores) {
    if (cantJuegosActuales < 10 ) {
        ///Instancia el objeto Juego
        Juego* nJuego = new Juego(cantJugadores);
        ///Lo agrega en la siguiente posicion sin juego guardado
        juegosActuales[cantJuegosActuales] = nJuego;
        ///Manda a generar el codigo del juego
        // (PRUEBAS: Esta utilizando la cantidad de Juegos Actuales para generar un codigo mientras)
        juegosActuales[cantJuegosActuales]->generarCodigo(cantJuegosActuales+1);
        ///Actualiza la cantidad de juegos actuales con el recien creado
        cantJuegosActuales++;

        cout << "\nJuego nuevo creado!" << endl;
        cout << "Juegos activos: " << cantJuegosActuales << endl;

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
 * Agrega un jugador nuevo al juego que se indica.
 * @param codigo
 * @param nombreJugador
 */
void jugadorNuevo(string codigo, string nombreJugador) {

    int numJuego = getJuego(codigo);

    if (numJuego >= 0) {

        ///Guarda el juego que se modificará en una variable
        Juego* juegoActual = juegosActuales[numJuego];

        ///Ingresa al nuevo jugador
        juegoActual->addJugador(nombreJugador);


        //*************************************Pruebas*********************************************************

        //Cantidad de jugadores
        cout << "\nCantidad de Jugadores Actuales en Juego(" << juegoActual->getCodigo()
             << ") : " << juegoActual->getCantJugadoresActuales() << "\n" << endl;

        //*****************************************************************************************************

    }
    ///Cuando no hay juegos definidos
    else {
        cout << "No se puede ingresar el juego, si este no está definido." << endl;
    }

}

/**
 * Funcion inicial del juego.
 * Crea un nuevo juego y comienza con las preparaciones para que el juego comience.
 * @param cantJugadoresPermitidos - cantidad de jugadores maximos en el juego
 * @param nombreJugador - string del nombre del jugador
 */
void iniciarScrabble(string cantJugadoresPermitidos, string nombreJugador) {
    //Crea un nuevo juego y retorna que numero de juego es
    int numJuego = juegoNuevo(stoi(cantJugadoresPermitidos));

    if (numJuego >= 0) {
        ///Guarda el juego actual, recien creado, en una variable
        Juego* juegoActual = juegosActuales[numJuego];

        ///Crea las fichas del juego
        juegoActual->crearFichas();

        ///Ingresa al jugador que manda a crear el juego como Jugador1
        juegoActual->addJugador(nombreJugador);


        //*************************************Pruebas*********************************************************

        //Cantidad de jugadores
        cout << "\nCantidad de Jugadores Actuales en Juego(" << juegoActual->getCodigo()
                                    << ") : " << juegoActual->getCantJugadoresActuales() << "\n" << endl;

        //Cantidad inicial de fichas
        cout<<"\nPool de fichas"<<endl;
        juegoActual->getPoolFichas()->printList();

        //*****************************************************************************************************

    }
    ///Cuando ya no se pueden crear mas juegos
    else {
        cout << "\nPor favor intente ingresar luego." << endl;
        ///Servidor deberia devolver un mensaje en pantalla diciendo que espere a que termine un juego
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

        ///Repartirá las fichas a los jugadores
        juegoActual->repartirFichas();

        ///Define quien comenzará en el primer turno
        juegoActual->setEnTurno(juegoActual->getJ1());

        //*************************************Pruebas*********************************************************

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
 * Pasa de turno, cambia de jugador enTurno y verifica si el juego podria terminar
 * @param codigo - para saber en que juego pasar el turno
 */
void pasarTurno(string codigo) {

    int numJuego = getJuego(codigo);

    if (numJuego >= 0) {

        ///Guarda el juego que se modificará en una variable
        Juego* juegoActual = juegosActuales[numJuego];

        ///Agrega +1 a los turnos pasados del jugador enTurno
        juegoActual->getEnTurno()->setTurnosPasados(juegoActual->getEnTurno()->getTurnosPasados() + 1);

        ///Verifica los turnos seguidos de todos los jugadores
        juegoActual->checkTurnosPasados();

        ///Verifica que el juego no haya terminado
        juegoActual->checkTerminado();

        ///Pasa al siguiente turno con un nuevo jugador enTurno
        juegoActual->siguienteTurno();

        //*************************************Pruebas*********************************************************

        //Imprime el jugador en turno
        cout << "\nJugador en turno: " << juegoActual->getEnTurno()->getNombre() << endl;

        //*****************************************************************************************************


    }
    ///Cuando no hay juegos definidos
    else {
        cout << "No se puede pasar el turno en el juego, si este no está definido." << endl;
    }

}


/**
 * Boton Scrabble!
 * @param codigo - para saber en que juego pasar el turno
 */
void scrabble(string codigo) {

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
 * Redirige las instrucciones que son obtenidas por el servidor
 * @param indtruccion - instruccion proveniente del cliente
 * @param codigo - para saber en que juego se tiene que tomar la accion
 */
void getInstruction(string instruccion, string codigo){

    if (instruccion == "Iniciar") {

        //TEST

        iniciarScrabble("4", "Jugador_1");
        jugadorNuevo(codigo, "Jugador_2");
        jugadorNuevo(codigo, "Jugador_3");
        jugadorNuevo(codigo, "Jugador_4");


    } else if (instruccion == "Comenzar") {

        comenzarJuego(codigo);

    } else if (instruccion == "Pasar" ) {

        pasarTurno(codigo);

    } else if (instruccion == "Scrabble!") {

        scrabble(codigo);

    }

}




/**
 * Main del programa.
 *
 * @author Ruben Salas
 * @since 26/03/19.
 */
int main(int argc, char **argv) {


    int fd, fd2;

    struct sockaddr_in server;


    struct sockaddr_in client;



    if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
        printf("error en socket()\n");
        exit(-1);
    }

    server.sin_family = AF_INET;

    server.sin_port = htons(PORT);

    server.sin_addr.s_addr = INADDR_ANY;

    bzero(&(server.sin_zero),8);

    if(bind(fd,(struct sockaddr*)&server,
            sizeof(struct sockaddr))==-1) {
        printf("error en bind() \n");
        exit(-1);
    }

    if(listen(fd,BACKLOG) == -1) {
        printf("error en listen()\n");
        exit(-1);
    }

    printf("Servidor Scrabble abierto!\n");

    while(true) {

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


            ///NOMBRE JUGADOR
            struct json_object *tempJugador;
            json_object *parsed_jsonJugador = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonJugador, "JUGADOR", &tempJugador);
            printf("Jugador: %s\n", json_object_get_string(tempJugador));

            ///JUGADORES PERMITIDOS
            struct json_object *tempCantidad;
            json_object *parsed_jsonCantidad = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonCantidad, "JUGADORES PERMITIDOS", &tempCantidad);
            printf("Jugadores Permitidos: %s\n", json_object_get_string(tempCantidad));

            ///Creacion del juego -> Cuando viene ambos parametros en JSON (CODIGO y JUGADOR)
            if (json_object_get_string(tempCantidad) != 0 && json_object_get_string(tempJugador) != 0) {
                iniciarScrabble(json_object_get_string(tempCantidad), json_object_get_string(tempJugador));
            }

            ///CODIGO
            struct json_object *tempCodigo;
            json_object *parsed_jsonCodigo = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonCodigo, "CODIGO", &tempCodigo);
            printf("Codigo: %s\n", json_object_get_string(tempCodigo));

            ///Agrega un jugador al juego cuando no se incluye la cantidad de jugadores permitidos
            ///HACER FUNCION DE AGREGAR JUGADOR
            if (json_object_get_string(tempJugador) != 0 && json_object_get_string(tempCantidad) == 0) {
                jugadorNuevo(json_object_get_string(tempJugador), json_object_get_string(tempCodigo));
            }


            ///BOTON
            struct json_object *tempBoton;
            json_object *parsed_jsonBoton = json_tokener_parse(buff);
            json_object_object_get_ex(parsed_jsonBoton, "BOTON", &tempBoton);
            printf("Boton: %s\n", json_object_get_string(tempBoton));

            ///Llama a funcion para verificar la instruccion
            if (json_object_get_string(tempBoton) != 0 && json_object_get_string(tempCodigo) != 0) {
                getInstruction(json_object_get_string(tempBoton), json_object_get_string(tempCodigo));
            }



            ///Reestablece el buffer
            memset(buff, 0, MAXDATASIZE);



            cout << "\n\n--------------------------------------------------------------------------------"
                     "END--------------------------------------------------------------------------------\n" << endl;
        }

        close(fd2);

    }


    return 0;

}
