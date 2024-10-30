#include "magnum.h"

#include <iostream>

#define MAGNUM "Magnum"
#define ALCANCE 20
#define MUNICIONES 6

Magnum::Magnum(): Arma(ID_MAGNUM, MAGNUM, ALCANCE, MUNICIONES, true) {}

void Magnum::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
    } else {
        std::cout << "Direccion invalida" << std::endl;
    }
}
