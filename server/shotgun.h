#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

class Shotgun: public Arma {
private:
    bool debe_recargar;
    int alcance_maximo;
    bool recargar();

public:
    Shotgun();
    void disparar(const orientacion_e& direccion) override;
};

#endif
