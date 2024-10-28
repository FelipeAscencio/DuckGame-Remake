#include "sniper.h"

#include <iostream>

#define SNIPER "Sniper"
#define ALCANCE 64
#define MUNICIONES 3

Sniper::Sniper(): Arma(ID_SNIPER, SNIPER, ALCANCE, MUNICIONES, false) {}

void Sniper::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA ||
        direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
    } else {
        std::cout << "Direccion invalida" << std::endl;
    }
}