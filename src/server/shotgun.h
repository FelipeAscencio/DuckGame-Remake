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

    void eliminar_bala(int indice) override;

public:
    // Constructor de la clase.
    Shotgun(posicion_t posicion_inicial);

    // Sobreescritura del metodo de disparo.
    bool disparar(const orientacion_e& direccion, Mapa& mapa) override;
};

#endif  // SHOTGUN_H
