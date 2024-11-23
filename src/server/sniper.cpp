#include "sniper.h"

#include <iostream>

#define SNIPER "Sniper"
#define ALCANCE 64
#define MUNICIONES 3

Sniper::Sniper(posicion_t posicion_inicial):
        Arma(ID_SNIPER, SNIPER, ALCANCE, MUNICIONES, false, posicion_inicial) {}

bool Sniper::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (municiones == 0) return false;
    Municion bala(ID_SNIPER, this->posicion_spawn, (ALCANCE*TILE_A_METRO), direccion, NO, balas.size());
    if (bala.avanzar(mapa))
        balas.push_back(bala);
    municiones -= 1;
    return true;
}
