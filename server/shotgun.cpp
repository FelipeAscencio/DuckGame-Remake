#include "shotgun.h"

#include <iostream>

#define SHOTGUN "Shotgun"
#define ALCANCE_MINIMO 7
#define ALCANCE_MAXIMO 9
#define MUNICIONES 2

Shotgun::Shotgun(posicion_t posicion_inicial):
        Arma(ID_SHOTGUN, SHOTGUN, ALCANCE_MINIMO, MUNICIONES, true, posicion_inicial),
        debe_recargar(false),
        alcance_maximo(ALCANCE_MAXIMO) {}

bool Shotgun::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
        return true;
    } else {
        std::cout << "Direccion invalida" << std::endl;
        return false;
    }
}

void Shotgun::chequeo_balas() {
    std::cout << "Nada aun" << std::endl;
    return;
}
