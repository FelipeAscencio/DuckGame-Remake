// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef COWBOY_PISTOL_H
#define COWBOY_PISTOL_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

// Esta clase implementa la logica del arma 'Cowboy Pistol'.
class CowboyPistol: public Arma {
public:
    // Constructor de la clase.
    CowboyPistol(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion) override;

    // Sobreescritura del metodo de chequeo de balas.
    void chequeo_balas() override;
};


#endif  // COWBOY_PISTOL_H
