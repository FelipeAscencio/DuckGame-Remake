// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef MAGNUM_H
#define MAGNUM_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

// Esta clase implementa la logica del arma 'Magnum'.
class Magnum: public Arma {
public:
    // Constructor de la clase.
    Magnum(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion) override;

    // Sobreescritura del metodo de chequeo de balas.
    void chequeo_balas() override;
};

#endif  // MAGNUM_H
