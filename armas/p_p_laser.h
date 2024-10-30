#ifndef P_P_LASER_H
#define P_P_LASER_H

#include <iostream>

#include "arma.h"
#include "../common/orientacion.h"

class PewPewLaser: public Arma {
private:
    int alcance_maximo;

public:
    PewPewLaser();
    void disparar(const orientacion_e& direccion) override;
};


#endif
