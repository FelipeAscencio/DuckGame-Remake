/*
    Copyright [2024] Axel Zielonka
*/
#include "server/mapa.h"

Mapa::Mapa(int largo, int alto) {
    this->largo = largo;
    this->alto = alto;
    this->mapa = new int*[largo];
    for (int i = 0; i < largo; i++) {
        mapa[i] = new int[alto];
    }
    for (int i = 0; i < largo; i++) {
        for (int j = 0; j < alto; j++) {
            mapa[i][j] = 0;
        }
    }
}

std::vector<int> Mapa::posicion_en_mapa(const posicion_t& pos) {
    std::vector<int> posicion(2);
    bool x_fuera_rango =
            ((pos.coordenada_x / TILE_A_METRO) > largo) || ((pos.coordenada_x / TILE_A_METRO) < 0);
    bool y_fuera_rango =
            (pos.coordenada_y / TILE_A_METRO) > alto || (pos.coordenada_y / TILE_A_METRO) < 0;
    if (x_fuera_rango || y_fuera_rango) {
        posicion[0] = -1;
        posicion[1] = -1;
    } else {
        posicion[0] = pos.coordenada_x / 10;
        posicion[1] = pos.coordenada_y / 10;
    }
    return posicion;
}

bool Mapa::borde_bloque(const posicion_t& pos, const orientacion_e& orientacion) {
    bool borde;
    switch (orientacion) {
        case orientacion_e::DERECHA:
            borde = (pos.coordenada_x % TILE_A_METRO) == 9;
            break;

        case orientacion_e::IZQUIERDA:
            borde = (pos.coordenada_x % TILE_A_METRO) == 0;
            break;
        default:
            borde = false;
            break;
    }
    return borde;
}

bool Mapa::piso_bloque(const posicion_t& pos) { return (pos.coordenada_y % TILE_A_METRO == 0); }

Mapa::~Mapa() {
    for (int i = 0; i < largo; i++) {
        delete mapa[i];
    }
    delete mapa;
}
