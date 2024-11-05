// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SNIPER_H
#define SNIPER_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

// Esta clase implementa la logica del arma 'Sniper'.
class Sniper: public Arma {
public:
    // Constructor de la clase.
    Sniper(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion) override;

    // Sobreescritura del metodo de chequeo de balas.
    void chequeo_balas() override;
};

#endif  // SNIPER_H
