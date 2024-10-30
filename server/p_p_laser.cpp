#include "p_p_laser.h"

#include <iostream>

#define PEW_PEW_LASER "Pew-Pew Laser"
#define ALCANCE_MINIMO 35
#define MUNICIONES 12
#define ALCANCE_MAXIMO 38

PewPewLaser::PewPewLaser():
        Arma(ID_PP_LASER, PEW_PEW_LASER, ALCANCE_MINIMO, MUNICIONES, false),
        alcance_maximo(ALCANCE_MAXIMO) {}

void PewPewLaser::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
    } else {
        std::cout << "Direccion invalida" << std::endl;
    }
}
