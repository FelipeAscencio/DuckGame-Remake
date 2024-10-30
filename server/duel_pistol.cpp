#include "duel_pistol.h"

#include <iostream>

#define DUEL_PISTOL "Duel Pistol"
#define ALCANCE 5
#define MUNICIONES 1

DuelPistol::DuelPistol(): Arma(ID_DUEL_PISTOL, DUEL_PISTOL, ALCANCE, MUNICIONES, true) {}

void DuelPistol::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
    } else {
        std::cout << "Direccion invalida" << std::endl;
    }
}
