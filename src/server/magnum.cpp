#include "magnum.h"
#include "config_juego.h"
#include <iostream>

#define MAGNUM "Magnum"

Magnum::Magnum(posicion_t posicion_inicial):
        Arma(ID_MAGNUM, MAGNUM, ConfigJuego::ALCANCE_MAGNUM, ConfigJuego::MUNICIONES_MAGNUM, true, posicion_inicial) {}

bool Magnum::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (this->municiones == 0)
        return false;

    Municion m(ID_MAGNUM, posicion_spawn, (ConfigJuego::ALCANCE_MAGNUM * TILE_A_METRO), direccion, NO,
                               balas.size());
    if (m.avanzar(mapa)) {
        balas.push_back(m);
    }
    municiones -= 1;
    return true;
}
