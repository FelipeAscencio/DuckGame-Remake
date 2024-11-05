// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef DUEL_PISTOL_H
#define DUEL_PISTOL_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

// Esta clase implementa la logica del arma 'Duel Pistol'.
class DuelPistol: public Arma {
public:
    // Constructor de la clase.
    DuelPistol(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion) override;

    // Sobreescritura del metodo de chequeo de balas.
    void chequeo_balas() override;
};

#endif  // DUEL_PISTOL_H
