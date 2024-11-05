// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef GRANADA_H
#define GRANADA_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

// Esta clase implementa la logica del arma 'Granada'.
class Granada: public Arma {
private:
    int tiempo_hasta_explotar;
    bool seguro_puesto;
    bool activa;

public:
    // Constructor de la clase.
    Granada(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccions) override;

    // Sobreescritura del metodo de chequeo de balas.
    void chequeo_balas() override;
};

#endif  // GRANADA_H
