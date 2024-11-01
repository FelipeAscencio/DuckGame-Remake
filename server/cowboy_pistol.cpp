#include "cowboy_pistol.h"

#include <iostream>

#define COWBOY_PISTOL "Cowboy Pistol"
#define ALCANCE 20
#define MUNICIONES 6

CowboyPistol::CowboyPistol(): Arma(ID_COWBOY_PISTOL, COWBOY_PISTOL, ALCANCE, MUNICIONES, false) {}

bool CowboyPistol::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
        return true;
    } else {
        std::cout << "Direccion invalida" << std::endl;
        return false;
    }
}

void CowboyPistol::chequeo_balas() {
    std::cout << "Nada por ahora\n";
    return;
}
