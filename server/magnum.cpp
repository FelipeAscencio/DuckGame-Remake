#include "magnum.h"

#include <iostream>

#define MAGNUM "Magnum"
#define ALCANCE 20
#define MUNICIONES 6

Magnum::Magnum(posicion_t posicion_inicial):
        Arma(ID_MAGNUM, MAGNUM, ALCANCE, MUNICIONES, true, posicion_inicial) {}

bool Magnum::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
        return true;
    } else {
        std::cout << "Direccion invalida" << std::endl;
        return false;
    }
}

void Magnum::chequeo_balas() {
    std::cout << "Nada por ahora" << std::endl;
    return;
}
