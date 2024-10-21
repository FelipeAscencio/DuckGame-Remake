#ifndef MAGNUM_H
#define MAGNUM_H

#include <iostream>

#include "arma.h"

class Magnum: public Arma {
public:
    Magnum();
    void disparar() override;
};


#endif
