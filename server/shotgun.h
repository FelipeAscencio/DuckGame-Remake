// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

// Esta clase implementa la logica del arma 'Shotgun'.
class Shotgun: public Arma {
private:
    bool debe_recargar;
    int alcance_maximo;
    bool recargar();

public:
    // Constructor de la clase.
    Shotgun(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion) override;

    // Sobreescritura del metodo de chequeo de balas.
    void chequeo_balas() override;
};

#endif  // SHOTGUN_H
