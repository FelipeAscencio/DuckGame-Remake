#ifndef MAGNUM_H
#define MAGNUM_H

#include <iostream>

#include "arma.h"
#include "orientacion.h"

class Magnum: public Arma {
public:
    Magnum();
    void disparar(const orientacion_e& direccion) override;
};


#endif
