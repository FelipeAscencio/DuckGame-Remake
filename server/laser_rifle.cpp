#include "laser_rifle.h"

#include <iostream>

#define LASER_RIFLE "Laser Rifle"
#define ALCANCE 30
#define MUNICIONES 10

LaserRifle::LaserRifle(): Arma(ID_LASER_RIFLE, LASER_RIFLE, ALCANCE, MUNICIONES, false) {}

bool LaserRifle::disparar(const orientacion_e& direccion) {
    if (direccion == DERECHA || direccion == IZQUIERDA || direccion == ARRIBA) {
        std::cout << "Direccion valida" << std::endl;
        return true;
    } else {
        std::cout << "Direccion invalida" << std::endl;
        return true;
    }
}

void LaserRifle::chequeo_balas() {
    std::cout << "Nada por ahora\n";
    return;
}
