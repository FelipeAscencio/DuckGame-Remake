#ifndef SNIPER_H
#define SNIPER_H

#include <iostream>

#include "arma.h"
#include "../common/orientacion.h"

class Sniper: public Arma {
public:
    Sniper();
    void disparar(const orientacion_e& direccion) override;
};


#endif
