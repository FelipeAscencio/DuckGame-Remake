// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

// Esta clase implementa la logica del arma 'Laser Rifle'.
class LaserRifle: public Arma {
public:
    // Constructor de la clase.
    LaserRifle(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion) override;

    // Sobreescritura del metodo de chequeo de balas.
    void chequeo_balas() override;
};

#endif  // LASER_RIFLE_H
