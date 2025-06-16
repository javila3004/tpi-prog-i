#include <string>
#include <iomanip>
#include "rlutil.h"
#include "declaracionFunciones.h"
using namespace std;

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
