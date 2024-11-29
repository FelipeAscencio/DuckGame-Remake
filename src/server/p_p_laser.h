// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef P_P_LASER_H
#define P_P_LASER_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"
#include "config_juego.h"

// Esta clase implementa la logica del arma 'Pew Pew Laser'.
class PewPewLaser: public Arma {
private:
    int alcance_maximo;
    int iteraciones_desde_disparo;

public:
    // Constructor de la clase.
    explicit PewPewLaser(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion, Mapa& mapa) override;

    // Deshabilito las copias.
    PewPewLaser(const PewPewLaser&) = delete;
    PewPewLaser& operator=(const PewPewLaser&) = delete;

    // Permito el movimiento del objeto.
    PewPewLaser(PewPewLaser&&) = default;
    PewPewLaser& operator=(PewPewLaser&&) = default;
};

#endif  // P_P_LASER_H
