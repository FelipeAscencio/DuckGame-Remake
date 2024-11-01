#ifndef DUEL_PISTOL_H
#define DUEL_PISTOL_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

class DuelPistol: public Arma {
public:
    DuelPistol();
    void disparar(const orientacion_e& direccion) override;
};


#endif
