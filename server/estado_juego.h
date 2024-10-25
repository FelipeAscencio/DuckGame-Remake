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
    std::vector<estado_pato_t> estados_patos;

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
} estado_juego_t;


#endif
