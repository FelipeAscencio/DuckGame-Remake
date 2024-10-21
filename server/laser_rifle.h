#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H

#include <iostream>

#include "arma.h"

class LaserRifle: public Arma {
public:
    LaserRifle();
    void disparar() override;
};


#endif
