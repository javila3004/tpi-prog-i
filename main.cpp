#include <string>
#include <iomanip>
#include <cstdlib>   // rand, srand
#include <ctime>     // time
#include "rlutil.h"
#include <cctype>    // tolower
#include "declacionFunciones.h"
using namespace std;


void turnoJugador1(int &dadosStockJugadorUno, int &dadosStockJugadorDos, int &puntosJugadorUno, string &ganador, int &puntajePartida);

int main() {
    // ---------------------------------------------------
    // 1) Declaracion de arrays en main
    //    jugador[] guarda nombres de hasta 4 ganadores
    //    puntaje[] guarda puntajes correspondientes
    string jugador[4] = {"", "", "", ""};
    int    puntaje[4] = {0, 0, 0, 0};
    int    nEstad     = 0;        // contador de cuantos puestos válidos hay

    // ---------------------------------------------------
    // 2) Variables de control del bucle principal
    bool   salir      = false;    // controla salida del menu
    string ganador;               // nombre del ganador de la última partida
    int    puntPartida;           // puntaje obtenido en la ultima partida

    // ---------------------------------------------------
    // 3) Bucle principal del menu
    while (!salir) {

        // Mostrar opciones al usuario
        cout << "===== MENU PRINCIPAL =====" << endl;
        cout << "1) JUGAR"        << endl;
        cout << "2) ESTADISTICAS" << endl;
        cout << "3) CREDITOS"     << endl;
        cout << "0) SALIR"        << endl;
        cout << "=> Opcion: ";
        int opc;
        cin >> opc;  // Leer opcion elegida
        // Procesar opcion



        switch (opc) {
            case 1: {
                srand(time(0)); // Inicializa con la hora actual (solo una vez)

                int stock1 = 6;
                int stock2 = 6;
                int puntos1 = 0;


                // 1) Llamar a juego(): se ejecuta la partida
                //    y se obtiene nombre del vencedor y su puntaje
                turnoJugador1(stock1, stock2, puntos1,ganador, puntPartida);

                cout << "\nFin del turno del Jugador 1.\n";
                cout << "Stock Jugador 1: " << stock1 << endl;
                cout << "Stock Jugador 2: " << stock2 << endl;
                cout << "Puntos Jugador 1: " << puntos1 << endl;

                // 2) Actualizar ranking TOP‑4 en los arrays
                actualizarEstadisticas(jugador, puntaje, nEstad,
                                       ganador, puntPartida);

                break;
            }
            case 2:
                // Mostrar el TOP‑4 actual
                mostrarEstadisticas(jugador, puntaje, nEstad);
                break;

            case 3:
                // Mostrar creditos del equipo
                creditos();
                break;

            case 0:
                // Preguntar confirmacion de salida
                if (confirmarSalida())
                    salir = true;
                break;

            default:
                // Opcion invalida: volver a mostrar menu
                cout << "Opcion invalida. Intente otra vez." << endl;
                break;
        }
    }

    // Mensaje final antes de terminar programa
    cout << "Hasta la proxima!" << endl;
    return 0;
}

//------------------------------------------------------------------------------------------------
//                   UNIFICATION DE  LA FUNCIONES

//Resultado aleatorio luego de tirar un dado de seis caras
int tirarDadoSeis(){
    return (rand() % 6) + 1;
}
//Resultado aleatorio luego de tirar un dado de doce caras
int tirarDadoDoce(){
    return (rand() % 12) + 1;
}
void turnoJugador1(int &dadosStockJugadorUno, int &dadosStockJugadorDos, int &puntosJugadorUno, string &ganador, int &puntajePartida){
    // Se tiran los dos dados de 12 caras para obtener el n£mero de Dados Objetivo
    int dadosObjetivo;
    int dadoDoceUno = tirarDadoDoce();
    int dadoDoceDos = tirarDadoDoce();
    dadosObjetivo = dadoDoceUno + dadoDoceDos;

    // Se tiran los dados de 6 caras del jugador 1
    int dadosTotalesJugadorUno[6]; // array fijo
    for (int i = 0; i < dadosStockJugadorUno; i++) {
        dadosTotalesJugadorUno[i] = tirarDadoSeis();
    }

    int sumaStock = 0, sumaDados = 0, eleccion;

    // Mostrar dados y permitir selecci¢n
    while (true) {
        cout << "\n Numero objetivo: " << dadosObjetivo << endl;
        cout << "Tus dados: ";
        for (int i = 0; i < dadosStockJugadorUno; i++) {
            if (dadosTotalesJugadorUno[i] != 0)
                cout << "[" << i << "]:" << dadosTotalesJugadorUno[i] << " ";
        }
        cout << endl;

        cout << "Elegi un dado (indice): ";
        cin >> eleccion;

        if (eleccion < 0 || eleccion >= dadosStockJugadorUno || dadosTotalesJugadorUno[eleccion] == 0) {
            cout << "Eleccion invalida. Probar de nuevo.\n";
            continue;
        }

        sumaStock += dadosTotalesJugadorUno[eleccion];
        dadosTotalesJugadorUno[eleccion] = 0;
        sumaDados++;

        if (sumaStock >= dadosObjetivo) break;
    }

    // Resultado
    if (sumaStock == dadosObjetivo) {
        dadosStockJugadorUno -= sumaDados;
        if (dadosStockJugadorUno == 0) {
            puntosJugadorUno += 10000; // premio
            return;
        }
        puntosJugadorUno += dadosStockJugadorUno * sumaStock;
        dadosStockJugadorDos -= sumaDados;
    } else if (sumaStock > dadosObjetivo) {
        if (dadosStockJugadorDos > 1) {
            dadosStockJugadorDos--;
            dadosStockJugadorUno++;
        }
    }
}




//------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------
// actualizarEstadisticas()
// Inserta un nuevo registro en los arrays jugador[] y puntaje[] para
// mantener orden descendente por puntaje, y recorta a los primeros 4.
// ------------------------------------------------------------------------
void actualizarEstadisticas(string jugador[4],int puntaje[4],int& nEstad,const string& nombreNuevo,int puntajeNuevo)
{
    // 1) Determinar posicion donde insertar el nuevo puntaje
    int pos = nEstad;  // por defecto al final de los existentes
    for (int i = 0; i < nEstad; ++i) {
        if (puntajeNuevo > puntaje[i]) {
            pos = i;
            break;
        }
    }

    // 2) Desplazar los elementos desde el final hasta la posicion pos
    //    para hacer espacio al nuevo registro
    int limite = min(nEstad, 3);  // ultimo indice valido es 3
    for (int k = limite; k > pos; --k) {
        jugador[k] = jugador[k - 1];
        puntaje[k] = puntaje[k - 1];
    }

    // 3) Insertar nuevo nombre y puntaje en la posicion correcta
    jugador[pos] = nombreNuevo;
    puntaje[pos] = puntajeNuevo;

    // 4) Si hay menos de 4 registros, incrementar contador
    if (nEstad < 4) ++nEstad;
}

// ------------------------------------------------------------------------
// mostrarEstadisticas()
// Recorre los arrays jugador[] y puntaje[] hasta nEstad y los imprime
// ------------------------------------------------------------------------
void mostrarEstadisticas(const string jugador[4],const int puntaje[4],int nEstad)
{
    cout << "===== TOP 4 JUGADORES =====" << endl;

    if (nEstad == 0) {
        // No hay ningun registro aun
        cout << "No hay estadisticas disponibles." << endl;
    } else {
        // Mostrar cada puesto numerado
        for (int i = 0; i < nEstad; ++i) {
            cout << setw(2) << (i + 1) << ". "
                 << left << setw(15) << jugador[i]
                 << " - " << puntaje[i] << " pts"
                 << endl;
        }
    }

    cout << "===========================" << endl;
}

// ------------------------------------------------------------------------
// creditos()
// Imprime apellidos, nombres, legajos de los integrantes y nombre de equipo
// ------------------------------------------------------------------------
void creditos() {
    cout << "===== CREDITOS =====" << endl;
    cout << "* Camila Ariadna Gamboa (Legajo: 32347)"     << endl;
    cout << "* Santiago sosa  (Legajo:32544)"             << endl;
    cout << "* Agustin Juarez (Legajo:33205) "            << endl;
    cout << "* Avila Reina Juan Esteban (Legajo: 32887)"  << endl;
    cout << "===================="                        << endl;
}

// ------------------------------------------------------------------------
// confirmarSalida()
// Solicita al usuario confirmacion  para salir.
// Devuelve true si ingresa 's' o 'S'.
// ------------------------------------------------------------------------
// confirmarSalida()
// Solicita al usuario confirmacion para salir.
// 's' o 'S' = sí, salir → retorna true
// 'n' o 'N' = no salir    → retorna false
// Sigue preguntando hasta recibir una de esas dos.
bool confirmarSalida() {
    char r;
    do {
        cout << "Seguro que deseas salir? (s/n): ";
        cin >> r;
        // Normalizar a minúscula
        r = tolower(r);
        if (r != 's' && r != 'n') {
            cout << "Entrada invalida. Por favor ingresa 's' o 'n'." << endl;
        }
    } while (r != 's' && r != 'n');

    return (r == 's');
}
