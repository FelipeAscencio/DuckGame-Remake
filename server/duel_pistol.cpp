#include "duel_pistol.h"

#include <iostream>

#define DUEL_PISTOL "Duel Pistol"
#define ALCANCE 5
#define MUNICIONES 1

DuelPistol::DuelPistol(): Arma(ID_DUEL_PISTOL, DUEL_PISTOL, ALCANCE, MUNICIONES, true) {}

bool DuelPistol::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
        return true;
    } else {
        std::cout << "Direccion invalida" << std::endl;
        return false;
    }
}

void DuelPistol::chequeo_balas() {
    std::cout << "Nada por ahora\n";
    return;
}
