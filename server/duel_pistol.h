#ifndef DUEL_PISTOL_H
#define DUEL_PISTOL_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

class DuelPistol: public Arma {
public:
    DuelPistol(posicion_t posicion_inicial);
    bool disparar(const orientacion_e& direccion) override;
    void chequeo_balas() override;
};


#endif
