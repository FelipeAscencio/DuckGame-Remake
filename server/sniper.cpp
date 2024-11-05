#include "sniper.h"

#include <iostream>

#define SNIPER "Sniper"
#define ALCANCE 64
#define MUNICIONES 3

Sniper::Sniper(posicion_t posicion_inicial):
        Arma(ID_SNIPER, SNIPER, ALCANCE, MUNICIONES, false, posicion_inicial) {}

bool Sniper::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
        return true;
    } else {
        std::cout << "Direccion invalida" << std::endl;
        return false;
    }
}

void Sniper::chequeo_balas() {
    std::cout << "Nada todavia" << std::endl;
    return;
}
