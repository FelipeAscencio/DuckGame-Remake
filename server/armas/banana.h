#ifndef BANANA_H
#define BANANA_H

#include <iostream>

#include "arma.h"
#include "orientacion.h"

class Banana: public Arma {
private:
    bool activa;

public:
    Banana();

    void disparar(const orientacion_e& direccion) override;
};

#endif
