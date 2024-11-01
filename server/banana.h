#ifndef BANANA_H
#define BANANA_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

class Banana: public Arma {
private:
    bool activa;

public:
    Banana();

    bool disparar(const orientacion_e& direccion) override;

    void chequeo_balas() override;
};

#endif
