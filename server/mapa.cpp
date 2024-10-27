#include "server/mapa.h"

Mapa::Mapa(int largo, int alto) {
    this->largo = largo;
    this->alto = alto;
    this->mapa = new int*[alto];
    for (int i = 0; i < alto; i++) {
        mapa[i] = new int[largo];
    }
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < largo; j++) {
            mapa[i][j] = 0;
        }
    }

    mapa[3][15] = mapa[3][16] = mapa[3][17] = 1;
    mapa[5][4] = mapa[5][5] = mapa[5][6] = mapa[5][7] = mapa[5][8] = 1;
    mapa[7][10] = mapa[7][11] = mapa[7][14] = 1;
    mapa[8][10] = mapa[8][11] = mapa[8][14] = mapa[8][18] = mapa[8][19] = 1;
    mapa[9][0] = mapa[9][1] = mapa[9][2] = mapa[9][3] = mapa[9][10] = mapa[9][11] = mapa[9][14] = mapa[9][18] = mapa[9][19] = 1;
    mapa[10][0] = mapa[10][1] = mapa[10][2] = mapa[10][3] = mapa[10][10] = mapa[10][11] = mapa[10][14] = mapa[10][18] = mapa[10][19] = 1;
    mapa[10][7] = mapa[10][8] = mapa[10][9] = mapa[10][12] = mapa[10][13] = 2; // el piso no coincide con el piso del bloque    
    mapa[11][0] = mapa[11][1] = mapa[11][2] = mapa[11][3] = mapa[11][7] = mapa[11][8] = mapa[11][9] = mapa[11][10] = mapa[11][11] = mapa[11][12] = mapa[11][13] = mapa[11][14] = mapa[11][18] = mapa[11][19] = 1;
    mapa[11][15] = mapa[11][16] = mapa[11][17] = 2;
    mapa[12][0] = mapa[12][1] = mapa[12][3] = mapa[12][7] = mapa[12][8] = mapa[12][9] = mapa[12][10] = mapa[12][11] = mapa[12][12] = mapa[12][13] = mapa[12][14] = mapa[12][15] = mapa[12][16] = mapa[12][17] = mapa[12][18] = mapa[12][19] = 1;
    mapa[13][0] = mapa[13][3] = mapa[13][8] = mapa[13][9] = mapa[13][10] = mapa[13][11] = mapa[13][12] = mapa[13][13] = mapa[13][14] = mapa[13][18] = mapa[13][19] = 1;
    mapa[14][3] = mapa[14][9] = mapa[14][10] = mapa[14][11] = mapa[14][12] = mapa[14][13] = mapa[14][14] = mapa[14][18] = mapa[14][19] = 1;
    mapa[15][3] = mapa[15][10] = mapa[15][11] = mapa[15][12] = mapa[15][13] = mapa[15][18] = mapa[15][19] = 1;
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
        posicion[0] = pos.coordenada_x / TILE_A_METRO;
        posicion[1] = pos.coordenada_y / TILE_A_METRO;
    }
    return posicion;
}

bool Mapa::borde_bloque(const posicion_t& pos, const orientacion_e& orientacion) {
    bool borde;
    switch (orientacion) {
        case orientacion_e::DERECHA:
            borde = (pos.coordenada_x % TILE_A_METRO) == (TILE_A_METRO - 1);
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

bool Mapa::piso_bloque(const posicion_t& pos) {
    return (pos.coordenada_y % TILE_A_METRO == (TILE_A_METRO - 1));
}

Mapa::~Mapa() {
    for (int i = 0; i < largo; i++) {
        delete mapa[i];
    }
    delete mapa;
}
