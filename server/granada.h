#ifndef GRANADA_H
#define GRANADA_H

#include <iostream>

#include "arma.h"

class Granada: public Arma {
private:
    int tiempo_hasta_explotar;
    bool seguro_puesto;
    bool activa;

public:
    Granada();
    void disparar() override;
};


#endif