#include "magnum.h"

#include <iostream>

#define MAGNUM "Magnum"
#define ALCANCE 20
#define MUNICIONES 6

Magnum::Magnum(posicion_t posicion_inicial):
        Arma(ID_MAGNUM, MAGNUM, ALCANCE, MUNICIONES, true, posicion_inicial) {}

bool Magnum::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (this->municiones == 0)
        return false;

    Municion m(ID_MAGNUM, posicion_spawn, (ALCANCE * TILE_A_METRO), direccion, NO,
                               balas.size());
    if (m.avanzar(mapa)) {
        balas.push_back(m);
    }
    municiones -= 1;
    return true;
}
