// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"
#include "config_juego.h"

// Esta clase implementa la logica del arma 'Shotgun'.
class Shotgun: public Arma {
private:
    bool debe_recargar;
    int alcance_maximo;

    // Elimina una bala en especifica segun el indice recibido.
    void eliminar_bala(const int& indice) override;

public:
    // Constructor de la clase.
    explicit Shotgun(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion, Mapa& mapa) override;

    // Deshabilito las copias.
    Shotgun(const Shotgun&) = delete;
    Shotgun& operator=(const Shotgun&) = delete;

    // Permito el movimiento del objeto.
    Shotgun(Shotgun&&) = default;
    Shotgun& operator=(Shotgun&&) = default;
};

#endif  // SHOTGUN_H
