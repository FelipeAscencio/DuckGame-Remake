#ifndef ESTADO_JUEGO_H
#define ESTADO_JUEGO_H

#include <iostream>
#include <vector>

#include <posicion.h>

#include "arma.h"
#include "estado_fisico.h"
#include "orientacion.h"

typedef struct EstadoJuego {
    int cantidad_jugadores;
    std::vector<int> id_jugadores;
    std::vector<posicion_t> posiciones;
    std::vector<bool> poseen_armas;
    std::vector<Arma*> armas_equipadas;
    std::vector<bool> cascos_equipados;
    std::vector<bool> armaduras_equipadas;
    std::vector<orientacion_e> orientaciones;
    std::vector<estado_pato_e> estados_patos;

    EstadoJuego(int jugadores):
            cantidad_jugadores(jugadores),
            id_jugadores(cantidad_jugadores),
            posiciones(cantidad_jugadores),
            poseen_armas(cantidad_jugadores),
            armas_equipadas(cantidad_jugadores),
            cascos_equipados(cantidad_jugadores),
            armaduras_equipadas(cantidad_jugadores),
            orientaciones(cantidad_jugadores),
            estados_patos(cantidad_jugadores) {}

    void agregar_info_pato(const Pato& pato, int indice){
        id_jugadores[indice] = pato.id_jugador;
        posiciones[indice] = pato.posicion;
        poseen_armas[indice] = pato.posee_arma;
        armas_equipadas[indice] = pato.arma_equipada;
        cascos_equipados[indice] = pato.posee_casco;
        armaduras_equipadas[indice] = pato.posee_armadura;
        orientaciones[indice] = pato.orientacion;
        estados_patos[indice] = pato.estado_actual;
    }
} estado_juego_t;


#endif
