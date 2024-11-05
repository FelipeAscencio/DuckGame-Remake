// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef BANANA_H
#define BANANA_H

#include <iostream>

#include "../common/orientacion.h"

#include "arma.h"

// Esta clase implementa la logica del arma 'Banana'.
class Banana: public Arma {
private:
    bool activa;

public:
    // Constructor de la clase.
    Banana(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion) override;

    // Sobreescritura del metodo de chequeo de balas.
    void chequeo_balas() override;
};

#endif  // BANANA_H
