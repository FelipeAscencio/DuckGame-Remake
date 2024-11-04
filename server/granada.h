#ifndef GRANADA_H
#define GRANADA_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

class Granada: public Arma {
private:
    int tiempo_hasta_explotar;
    bool seguro_puesto;
    bool activa;

public:
    Granada(posicion_t posicion_inicial);
    bool disparar(const orientacion_e& direccions) override;
    void chequeo_balas() override;
};


#endif
