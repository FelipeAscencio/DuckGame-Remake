#include "sniper.h"
#include "config_juego.h"

#include <iostream>

#define SNIPER "Sniper"

Sniper::Sniper(posicion_t posicion_inicial):
        Arma(ID_SNIPER, SNIPER, ConfigJuego::ALCANCE_SNIPER, ConfigJuego::MUNICIONES_SNIPER, false, posicion_inicial) {}

bool Sniper::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (municiones == 0) return false;
    Municion bala(ID_SNIPER, this->posicion_spawn, (ConfigJuego::ALCANCE_SNIPER*TILE_A_METRO), direccion, NO, balas.size());
    if (bala.avanzar(mapa))
        balas.push_back(bala);
    municiones -= 1;
    return true;
}
