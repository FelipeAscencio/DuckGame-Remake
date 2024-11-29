// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef AK47_H
#define AK47_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"
#include "config_juego.h"

// Esta clase implementa la logica del arma 'AK-47'.
class AK47: public Arma {
    dispersion_e ultima_bala_disparada;
    int iteraciones_desde_disparo;

    // Modifica la dispersion de las balas en funcion de si el arma esta disparando o no.
    void modificar_dispersion_balas(bool disparando);

    // Override de la funcion de Arma
    void control_atributos(Mapa& mapa) override;

public:
    // Constructor de la clase.
    AK47(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion, Mapa& mapa) override;

    // Deshabilito las copias.
    AK47(const AK47&) = delete;
    AK47& operator=(const AK47&) = delete;

    // Permito el movimiento del objeto.
    AK47(AK47&&) = default;
    AK47& operator=(AK47&&) = default;
};

#endif  // AK47_H
