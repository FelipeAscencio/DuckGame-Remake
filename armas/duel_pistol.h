#ifndef DUEL_PISTOL_H
#define DUEL_PISTOL_H

#include <iostream>

#include "arma.h"
#include "orientacion.h"

class DuelPistol: public Arma {
public:
    DuelPistol();
    void disparar(const orientacion_e& direccion) override;
};


#endif
