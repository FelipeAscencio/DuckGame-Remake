#include "shotgun.h"

#include <iostream>

#define SHOTGUN "Shotgun"
#define ALCANCE_MINIMO 7
#define ALCANCE_MAXIMO 9
#define MUNICIONES 2

Shotgun::Shotgun():
        Arma(ID_SHOTGUN, SHOTGUN, ALCANCE_MINIMO, MUNICIONES, true),
        debe_recargar(false),
        alcance_maximo(ALCANCE_MAXIMO) {}

void Shotgun::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
    } else {
        std::cout << "Direccion invalida" << std::endl;
    }
}