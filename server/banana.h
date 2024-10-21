#ifndef BANANA_H
#define BANANA_H

#include <iostream>

#include "arma.h"

class Banana: public Arma {
private:
    bool activa;

public:
    Banana();

    void disparar() override;
};

#endif
