#include "sniper.h"

#include <iostream>

#define SNIPER "Sniper"
#define ALCANCE 64
#define MUNICIONES 3

Sniper::Sniper(posicion_t posicion_inicial):
        Arma(ID_SNIPER, SNIPER, ALCANCE, MUNICIONES, false, posicion_inicial) {}

bool Sniper::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        if (mapa.borde_bloque(this->posicion_spawn, DERECHA)){
            std::cout << "Direccion valida" << std::endl;
            return true;
        }
    } else {
        std::cout << "Direccion invalida" << std::endl;
        return false;
    }
    return false;
}

