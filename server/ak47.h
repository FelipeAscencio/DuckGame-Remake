#ifndef AK47_H
#define AK47_H

#include <iostream>

#include "arma.h"

class AK47: public Arma {
public:
    AK47();
    void disparar() override;
};


#endif
