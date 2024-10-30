#ifndef GRANADA_H
#define GRANADA_H

#include <iostream>

#include "arma.h"
#include "../common/orientacion.h"

class Granada: public Arma {
private:
    int tiempo_hasta_explotar;
    bool seguro_puesto;
    bool activa;

public:
    Granada();
    void disparar(const orientacion_e& direccions) override;
};


#endif