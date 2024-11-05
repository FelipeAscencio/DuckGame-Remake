// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef P_P_LASER_H
#define P_P_LASER_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

// Esta clase implementa la logica del arma 'Pew Pew Laser'.
class PewPewLaser: public Arma {
private:
    int alcance_maximo;

public:
    // Constructor de la clase.
    PewPewLaser(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion) override;

    // Sobreescritura del metodo de chequeo de balas.
    void chequeo_balas() override;
};

#endif  // P_P_LASER_H
