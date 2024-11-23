#include "p_p_laser.h"
#include "config_juego.h"
#include <iostream>

#define PEW_PEW_LASER "Pew-Pew Laser"

PewPewLaser::PewPewLaser(posicion_t posicion_inicial):
        Arma(ID_PP_LASER, PEW_PEW_LASER, ConfigJuego::ALCANCE_MINIMO_PP_LASER, ConfigJuego::MUNICIONES_PP_LASER, false, posicion_inicial),
        alcance_maximo(ConfigJuego::ALCANCE_MAXIMO_PP_LASER) {}

inclinacion_e buscar_inclinacion(const int& bala){
    if (bala == 0) return NO_TIENE;
    else if (bala == 1) return PARA_ARRIBA;
    else return PARA_ABAJO;
}

dispersion_e buscar_dispersion(const int& bala){
    if (bala == 0) return NO;
    else return ALTA;
}

bool PewPewLaser::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (this->municiones == 0) return false;
    inclinacion_e inc;
    dispersion_e dis;
    for (int i = 0; i < ConfigJuego::LASERS_POR_DISPARO_PP; i++){
        Municion m(ID_PP_LASER, this->posicion_spawn, (ConfigJuego::ALCANCE_MAXIMO_PP_LASER * TILE_A_METRO), direccion, dis, inc, balas.size());    
        if (m.avanzar(mapa)){
            balas.push_back(m);
        }
    }
    municiones -= 1;
    return true;
}
