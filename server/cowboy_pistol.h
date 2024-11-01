#ifndef COWBOY_PISTOL_H
#define COWBOY_PISTOL_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

class CowboyPistol: public Arma {
public:
    CowboyPistol();
    bool disparar(const orientacion_e& direccion) override;
    void chequeo_balas() override;
};


#endif
