// Copyright 2024 Axel Zielonka y Felipe Ascensio
#include "server/mapa.h"

#include <fstream>
#include <string>

#define ARCHIVO_MAPA "../data/mapa_"
#define TXT ".txt"

Mapa::Mapa(int mapa) {
    std::string ruta_mapa = ARCHIVO_MAPA + std::to_string(mapa) + TXT;
    std::ifstream archivo_mapa(ruta_mapa);
    if (!archivo_mapa.is_open()) {
        std::cerr << "Error leyendo archivo del mapa \n";
        throw ErrorMapa();
    }
    int leido;
    archivo_mapa >> leido;
    this->alto = leido;
    archivo_mapa >> leido;
    this->largo = leido;
    this->mapa = new int*[alto];
    for (int i = 0; i < alto; i++) {
        this->mapa[i] = new int[largo];
    }
    int i = 0;
    while (i < alto) {
        int j = 0;
        while (j < largo) {
            char c;
            archivo_mapa >> c;
            this->mapa[i][j] = ((int)c - 48);
            j++;
        }
        i++;
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
        posicion[0] = (int)(pos.coordenada_x / TILE_A_METRO);
        posicion[1] = (int)(pos.coordenada_y / TILE_A_METRO);
    }
    return posicion;
}

bool Mapa::borde_bloque(const posicion_t& pos, const orientacion_e& orientacion) {
    bool borde;
    switch (orientacion) {
        case orientacion_e::DERECHA:
            borde = ((int)pos.coordenada_x % TILE_A_METRO) == (TILE_A_METRO - 1);
            break;

        case orientacion_e::IZQUIERDA:
            borde = ((int)pos.coordenada_x % TILE_A_METRO) == 0;
            break;
        default:
            borde = false;
            break;
    }
    return borde;
}

bool Mapa::piso_bloque(const posicion_t& pos) {
    return ((int)pos.coordenada_y % TILE_A_METRO == (TILE_A_METRO - 1));
}

Mapa::~Mapa() {
    for (int i = 0; i < alto; i++) {
        delete mapa[i];
    }
    delete mapa;
}
