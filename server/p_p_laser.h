#ifndef P_P_LASER_H
#define P_P_LASER_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

class PewPewLaser: public Arma {
private:
    int alcance_maximo;

public:
    PewPewLaser(posicion_t posicion_inicial);
    bool disparar(const orientacion_e& direccion) override;
    void chequeo_balas() override;
};


#endif
