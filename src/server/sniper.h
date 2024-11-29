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
    explicit Sniper(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion, Mapa& mapa) override;

    // Deshabilito las copias.
    Sniper(const Sniper&) = delete;
    Sniper& operator=(const Sniper&) = delete;

    // Permito el movimiento del objeto.
    Sniper(Sniper&&) = default;
    Sniper& operator=(Sniper&&) = default;
};

#endif  // SNIPER_H
