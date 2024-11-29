// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef MAGNUM_H
#define MAGNUM_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"
#include "config_juego.h"

// Esta clase implementa la logica del arma 'Magnum'.
class Magnum: public Arma {
public:
    // Constructor de la clase.
    explicit Magnum(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion, Mapa& mapa) override;

    // Deshabilito las copias.
    Magnum(const Magnum&) = delete;
    Magnum& operator=(const Magnum&) = delete;

    // Permito el movimiento del objeto.
    Magnum(Magnum&&) = default;
    Magnum& operator=(Magnum&&) = default;
};

#endif  // MAGNUM_H
