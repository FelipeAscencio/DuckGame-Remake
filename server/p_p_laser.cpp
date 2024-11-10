#include "p_p_laser.h"

#include <iostream>

#define PEW_PEW_LASER "Pew-Pew Laser"
#define ALCANCE_MINIMO 35
#define MUNICIONES 12
#define ALCANCE_MAXIMO 38

PewPewLaser::PewPewLaser(posicion_t posicion_inicial):
        Arma(ID_PP_LASER, PEW_PEW_LASER, ALCANCE_MINIMO, MUNICIONES, false, posicion_inicial),
        alcance_maximo(ALCANCE_MAXIMO) {}

bool PewPewLaser::disparar(const orientacion_e& direccion, Mapa& mapa) {
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
