#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

class LaserRifle: public Arma {
public:
    LaserRifle(posicion_t posicion_inicial);
    bool disparar(const orientacion_e& direccion) override;
    void chequeo_balas() override;
};


#endif
