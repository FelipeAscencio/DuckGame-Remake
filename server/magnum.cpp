#include "magnum.h"

#include <iostream>

#define MAGNUM "Magnum"
#define ALCANCE 20
#define MUNICIONES 6

Magnum::Magnum(posicion_t posicion_inicial):
        Arma(ID_MAGNUM, MAGNUM, ALCANCE, MUNICIONES, true, posicion_inicial) {}

bool Magnum::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (this->municiones == CERO) {
        return false;
    }
    Municion* bala_disparada = new Municion(this->id_arma, this->posicion_spawn,
                                            ALCANCE * TILE_A_METRO, direccion, BAJA, 0);
    if (bala_disparada->avanzar(mapa)) {
        balas.push_back(bala_disparada);
    } else {
        delete bala_disparada;
    }
    this->municiones -= 1;
    return true;
}
