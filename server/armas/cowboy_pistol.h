#ifndef COWBOY_PISTOL_H
#define COWBOY_PISTOL_H

#include <iostream>

#include "arma.h"
#include "orientacion.h"

class CowboyPistol: public Arma {
public:
    CowboyPistol();
    void disparar(const orientacion_e& direccion) override;
};


#endif
