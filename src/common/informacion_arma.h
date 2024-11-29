// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef INFORMACION_ARMA_H
#define INFORMACION_ARMA_H

#include <iostream>

#include "../server/arma.h"
#include "posicion.h"

// 'Struct' que encapsula la informacion de todas las armas del juego.
struct InformacionArma {
    int id_arma;  // 0 = no arma, 1 ak, 2 magnum, 3 laser, 4 shotgun, 5 sniper.
    posicion_t posicion;

    // Primera variante del constructor del struct.
    explicit InformacionArma(Arma* a): id_arma(a->id_arma), posicion(a->posicion_spawn) {}

    // Segunda variante del constructor del struct.
    explicit InformacionArma(uint8_t id, float x, float y): id_arma(id), posicion(x, y) {}

    // Tercera variante del constructor del struct.
    explicit InformacionArma(uint8_t id, posicion_t pos): id_arma(id), posicion(pos) {}
};

#endif  // INFORMACION_ARMA_H
