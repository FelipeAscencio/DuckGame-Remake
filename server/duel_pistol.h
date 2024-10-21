#ifndef DUEL_PISTOL_H
#define DUEL_PISTOL_H

#include <iostream>

#include "arma.h"

class DuelPistol: public Arma {
public:
    DuelPistol();
    void disparar() override;
};


#endif
