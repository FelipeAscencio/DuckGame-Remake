#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <iostream>

#include "arma.h"

class Shotgun: public Arma {
private:
    bool debe_recargar;
    int alcance_maximo;
    bool recargar();

public:
    Shotgun();
    void disparar() override;
};

#endif
