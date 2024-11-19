#include "sniper.h"

#include <iostream>

#define SNIPER "Sniper"
#define ALCANCE 64
#define MUNICIONES 3

Sniper::Sniper(posicion_t posicion_inicial):
        Arma(ID_SNIPER, SNIPER, ALCANCE, MUNICIONES, false, posicion_inicial) {}

bool Sniper::disparar(const orientacion_e& direccion, Mapa& mapa) {
    std::cout << mapa.piso_bloque(this->posicion_spawn) << std::endl;
    std::cout << direccion << std::endl;
    std::cout << "Aun no esta implementado\n";
    return false;
}
