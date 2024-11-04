#ifndef AK47_H
#define AK47_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

class AK47: public Arma {
    dispersion_e ultima_bala_disparada;

    void modificar_dispersion_balas(bool disparando);

public:
    AK47(posicion_t posicion_inicial);
    bool disparar(const orientacion_e& direccion) override;

    void chequeo_balas() override;
};


#endif
