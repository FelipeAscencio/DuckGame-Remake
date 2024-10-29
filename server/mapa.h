// Copyright 2024 Axel Zielonka y Felipe Ascensio
#ifndef SERVER_MAPA_H_
#define SERVER_MAPA_H_

#include <iostream>
#include <vector>

#include "../common/orientacion.h"
#include "../common/posicion.h"

#define TILE_A_METRO 10

struct ErrorMapa: public std::runtime_error {
    ErrorMapa(): std::runtime_error("Se produjo un error al intentar crear el mapa") {}
};

class Mapa {
    friend class Pato;

private:
    int largo;
    int alto;
    int** mapa;

public:
    explicit Mapa(int largo, int alto);
    explicit Mapa(int mapa);
    std::vector<int> posicion_en_mapa(const posicion_t& posicion);
    bool borde_bloque(const posicion_t& pos, const orientacion_e& orientacion);
    bool piso_bloque(const posicion_t& pos);
    ~Mapa();
};

#endif  // SERVER_MAPA_H_
