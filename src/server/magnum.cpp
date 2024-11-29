#include "magnum.h"

#define MAGNUM "Magnum"

#define CERO 0
#define UNO 1

Magnum::Magnum(posicion_t posicion_inicial):
        Arma(ID_MAGNUM, MAGNUM, ConfigJuego::ALCANCE_MAGNUM, ConfigJuego::MUNICIONES_MAGNUM, true,
             posicion_inicial) {}

bool Magnum::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (this->municiones == CERO)
        return false;

    Municion m(ID_MAGNUM, ajustar_posicion_disparo(direccion), (ConfigJuego::ALCANCE_MAGNUM * TILE_A_METRO), direccion,
               NO, balas.size());
    if (m.avanzar(mapa)) {
        balas.push_back(m);
    }

    municiones -= UNO;
    return true;
}
