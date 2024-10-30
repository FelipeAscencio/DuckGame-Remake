#ifndef SNIPER_H
#define SNIPER_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

class Sniper: public Arma {
public:
    Sniper();
    void disparar(const orientacion_e& direccion) override;
};


#endif
