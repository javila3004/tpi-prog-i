#include <string>
#include <windows.h>
#include <iomanip>
#include <cstdlib>   // rand, srand
#include <ctime>     // time
#include "rlutil.h"
#include <cctype>    // tolower
#include "declaracionFunciones.h"
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // ---------------------------------------------------
    // 1) Declaracion de arrays en main
    //    jugador[] guarda nombres de hasta 4 ganadores
    //    puntaje[] guarda puntajes correspondientes
    string jugador[4] = {"", "", "", ""};
    int    puntaje[4] = {0, 0, 0, 0};
    int    nEstad     = 0;        // contador de cuantos puestos validos hay

    // ---------------------------------------------------
    // 2) Variables de control del bucle principal
    bool   salir      = false;    // controla salida del menu
    string ganador;               // nombre del ganador de la ultima partida
    int    puntPartida;           // puntaje obtenido en la ultima partida

    // ---------------------------------------------------
    // 3) Bucle principal del menu
    int x = 35;
    int y = 13;

    while (!salir) {
        rlutil::cls();

        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::YELLOW);

        rlutil::locate(0,0);
        cout << endl;
        cout << "███████╗███╗   ██╗███████╗██████╗ ███████╗███╗   ██╗██████╗  █████╗ ██████╗  ██████╗ ███████╗" << endl;
        cout << "██╔════╝████╗  ██║██╔════╝██╔══██╗██╔════╝████╗  ██║██╔══██╗██╔══██╗██╔══██╗██╔═══██╗██╔════╝" << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << "█████╗  ██╔██╗ ██║█████╗  ██████╔╝█████╗  ██╔██╗ ██║██║  ██║███████║██║  ██║██║   ██║███████╗" << endl;
        cout << "██╔══╝  ██║╚██╗██║██╔══╝  ██╔══██╗██╔══╝  ██║╚██╗██║██║  ██║██╔══██║██║  ██║██║   ██║╚════██║" << endl;
        rlutil::setColor(rlutil::YELLOW);
        cout << "███████╗██║ ╚████║██║     ██║  ██║███████╗██║ ╚████║██████╔╝██║  ██║██████╔╝╚██████╔╝███████║" << endl;
        cout << "╚══════╝╚═╝  ╚═══╝╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚═════╝ ╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚══════╝" << endl;
        rlutil::setColor(rlutil::WHITE);
        cout << endl << "Bienvenidos a Enfrendados, un juego en el que interviene el azar y las matematicas. ¡Suerte!";

        rlutil::setColor(rlutil::YELLOW);
        // Mostrar opciones al usuario
        rlutil::locate(x,y);
        cout << "===== MENU PRINCIPAL =====" << endl;
        rlutil::locate(x,y+1);
        cout << "1) JUGAR             " << endl;
        rlutil::locate(x,y+2);
        cout << "2) ESTADÍSTICAS      " << endl;
        rlutil::locate(x,y+3);
        cout << "3) CRÉDITOS          " << endl;
        rlutil::locate(x,y+4);
        cout << "==========================" << endl;
        rlutil::locate(x,y+5);
        cout << "0) SALIR"        << endl << endl;
        rlutil::locate(0,y+7);
        cout << "=> Elige tu opción: ";
        rlutil::resetColor();


        int opc;
        cin >> opc;  // Leer opcion elegida
        rlutil::cls();
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

                // 2) Actualizar ranking TOP 4 en los arrays
                actualizarEstadisticas(jugador, puntaje, nEstad,
                                       ganador, puntPartida);

                cout << "\nPresiona una tecla para volver al menú principal...";
                rlutil::anykey();
                break;
            }
            case 2:
                // Mostrar el TOP 4 actual
                mostrarEstadisticas(jugador, puntaje, nEstad);
                cout << "\nPresiona una tecla para volver al menú principal...";
                rlutil::anykey();
                break;

            case 3:
                // Mostrar creditos del equipo
                creditos();
                cout << "\nPresiona una tecla para volver al menú principal...";
                rlutil::anykey();
                break;

            case 0:
                // Preguntar confirmacion de salida
                if (confirmarSalida())
                    salir = true;
                break;

            default:
                // Opcion invalida: volver a mostrar menu
                cout << "Opcion invalida. Intente otra vez." << endl;
                cout << "Presiona una tecla para continuar...";
                rlutil::anykey();
                break;
        }
    }

    // Mensaje final antes de terminar programa
    cout << "Hasta la proxima!" << endl;




    return 0;
}


