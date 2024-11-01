#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

class LaserRifle: public Arma {
public:
    LaserRifle();
    void disparar(const orientacion_e& direccion) override;
};


#endif
