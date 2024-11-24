#include "p_p_laser.h"
#include "config_juego.h"
#include <iostream>

#define PEW_PEW_LASER "Pew-Pew Laser"

PewPewLaser::PewPewLaser(posicion_t posicion_inicial):
        Arma(ID_PP_LASER, PEW_PEW_LASER, ConfigJuego::ALCANCE_MINIMO_PP_LASER, ConfigJuego::MUNICIONES_PP_LASER, false, posicion_inicial),
        alcance_maximo(ConfigJuego::ALCANCE_MAXIMO_PP_LASER) {}



inclinacion_e obtener_inclinacion(const int& bala){
    if (bala == 0) return NO_TIENE;
    if (bala == 1) return PARA_ARRIBA;
    return PARA_ABAJO;
}

dispersion_e obtener_dispersion(const int& bala){
    if (bala == 0) return NO;
    return ALTA;
}

bool PewPewLaser::disparar(const orientacion_e& direccion, Mapa& mapa){
    if (municiones == 0) return false;

    for (int i = 0; i < ConfigJuego::MUNICIONES_PP_LASER; i++){
        inclinacion_e inc = obtener_inclinacion(i);
        dispersion_e dis = obtener_dispersion(i);
        Municion m(ID_PP_LASER, this->posicion_spawn, (ConfigJuego::ALCANCE_MAXIMO_PP_LASER * TILE_A_METRO), direccion, dis, inc, balas.size());
        if (m.avanzar(mapa)){
            balas.push_back(m);
        }
    }
    municiones -= 1;
    return true;

}