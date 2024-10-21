#ifndef SNIPER_H
#define SNIPER_H

#include <iostream>

#include "arma.h"

class Sniper: public Arma {
public:
    Sniper();
    void disparar() override;
};


#endif
