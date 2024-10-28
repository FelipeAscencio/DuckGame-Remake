#ifndef MAPA_H
#define MAPA_H

#include <iostream>
#include <vector>

#include "../common/orientacion.h"
#include "pato.h"
#include "../common/posicion.h"

#define TILE_A_METRO 10

class Mapa {
    friend Pato;

private:
    int largo;
    int alto;
    int** mapa;

public:
    explicit Mapa(int largo, int alto);
    std::vector<int> posicion_en_mapa(const posicion_t& posicion);
    bool borde_bloque(const posicion_t& pos, const orientacion_e& orientacion);
    bool piso_bloque(const posicion_t& pos);
    ~Mapa();
};

#endif
