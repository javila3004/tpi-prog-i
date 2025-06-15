//
// Created by Juan Avila on 13/6/2025.
//
#pragma once
#include <vector>
#include <string>

using namespace std;
//Prototipos de funciones
// juego(): ejecuta la partida y devuelve el nombre del vencedor y su puntaje
///PARTIDA GENERAL del juego
//Devuele el resultado final: "Jugador 1 ?GANA!" / "Jugador 2 ?GANA!" / ?Empate!
string partidaJuego();

///Tirar dados (Seis caras)
int tirarDadoSeis();

///Tirar dados (Doce caras)
int tirarDadoDoce();

///RONDA del juego
//Determina quien juega
void rondaJuego (int &dadosStockJugadorUno, int &dadosStockJugadorDos, int &puntosJugadorUno, int &puntosJugadorDos);

///RONDA de Jugador 1
//Modifica stock y puntos
void turnoJugador1(int &dadosStockJugadorUno, int &dadosStockJugadorDos, int &puntosJugadorUno, string &ganador, int &puntajePartida);

///RONDA de Jugador 2
//Modifica stock y puntos
void turnoJugador2(int &dadosStockJugadorDos, int &dadosStockJugadorUno, int &puntosJugadorDos, string &ganador, int &puntajePartida);


//---------------------------------------------------------------

// actualizarEstadisticas(): inserta un nuevo resultado en el ranking TOP‑4
void actualizarEstadisticas(string jugador[4],
                            int    puntaje[4],
                            int&   nEstad,
                            const string& nombreNuevo,
                            int    puntajeNuevo);

// mostrarEstadisticas(): muestra por pantalla el ranking TOP‑4 actual
void mostrarEstadisticas(const string jugador[4],
                         const int    puntaje[4],
                         int          nEstad);

// creditos(): imprime los apellidos, nombres, legajos y nombre de equipo
void creditos();

// confirmarSalida(): pide confirmacion al usuario y devuelve true si confirma salir
bool confirmarSalida();













