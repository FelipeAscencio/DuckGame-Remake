#ifndef COWBOY_PISTOL_H
#define COWBOY_PISTOL_H

#include <iostream>

#include "arma.h"

class CowboyPistol: public Arma {
public:
    CowboyPistol();
    void disparar() override;
};


#endif
