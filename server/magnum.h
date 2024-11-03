#ifndef MAGNUM_H
#define MAGNUM_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

class Magnum: public Arma {
public:
    Magnum(posicion_t posicion_inicial);
    bool disparar(const orientacion_e& direccion) override;
    void chequeo_balas() override;
};


#endif
