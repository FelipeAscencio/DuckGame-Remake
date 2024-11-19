#include "server/mapa.h"

#include <fstream>
#include <string>

#define ARCHIVO_MAPA "../data/mapa_"
#define TXT ".txt"
#define MENOS_UNO -1
#define CERO 0
#define UNO 1
#define PRIMERA_POSICION 0
#define SEGUNDA_POSICION 1

Mapa::Mapa(int mapa): id_mapa(mapa) {
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
            this->mapa[i][j] =
                    ((int)c - 48);  // A ESTE NUMERO MAGICO HAY QUE PONERLE UN NOMBRE DE CONSTANTE.
            j++;
        }

        i++;
    }
}

std::vector<int> Mapa::posicion_en_mapa(const posicion_t& pos) {
    std::vector<int> posicion(2);
    bool x_fuera_rango = ((pos.coordenada_x / TILE_A_METRO) > largo) ||
                         ((pos.coordenada_x / TILE_A_METRO) < CERO);
    bool y_fuera_rango = (pos.coordenada_y / TILE_A_METRO) > alto || pos.coordenada_y < CERO;
    if (x_fuera_rango || y_fuera_rango) {
        posicion[PRIMERA_POSICION] = MENOS_UNO;
        posicion[SEGUNDA_POSICION] = MENOS_UNO;
    } else {
        posicion[PRIMERA_POSICION] = (int)(pos.coordenada_x / TILE_A_METRO);
        posicion[SEGUNDA_POSICION] = (int)(pos.coordenada_y / TILE_A_METRO);
    }

    return posicion;
}

bool Mapa::borde_bloque(const posicion_t& pos, const orientacion_e& orientacion) {
    bool borde;
    switch (orientacion) {
        case orientacion_e::DERECHA:
            borde = ((int)pos.coordenada_x % TILE_A_METRO) == (TILE_A_METRO - UNO);
            break;

        case orientacion_e::IZQUIERDA:
            borde = ((int)pos.coordenada_x % TILE_A_METRO) == CERO;
            break;
        default:
            borde = false;
            break;
    }

    return borde;
}

bool Mapa::piso_bloque(const posicion_t& pos) {
    return ((int)pos.coordenada_y % TILE_A_METRO == (TILE_A_METRO - UNO));
}

bool Mapa::techo_bloque(const posicion_t& pos) {
    return ((int)pos.coordenada_y % TILE_A_METRO == 0);
}

posicion_t Mapa::posicion_inicial(const int& id_pato) {
    if (this->id_mapa == 1) {
        if (id_pato == 0)
            return posicion_t(5, 89);
        else if (id_pato == 1)
            return posicion_t(175, 29);
        else if (id_pato == 2)
            return posicion_t(63, 49);
        else if (id_pato == 3)
            return posicion_t(115, 69);
        else if (id_pato == 4)
            return posicion_t(192, 79);
        else if (id_pato == 5)
            return posicion_t(85, 99);
        else if (id_pato == 6)
            return posicion_t(137, 99);
        else if (id_pato == 7)
            return posicion_t(149, 69);
    } else {
        if (id_pato == 0)
            return posicion_t(63, 59);
        else if (id_pato == 1)
            return posicion_t(148, 69);
        else if (id_pato == 2)
            return posicion_t(9, 99);
        else if (id_pato == 3)
            return posicion_t(187, 99);
        else if (id_pato == 4)
            return posicion_t(33, 129);
        else if (id_pato == 5)
            return posicion_t(96, 129);
        else if (id_pato == 6)
            return posicion_t(125, 129);
        else if (id_pato == 7)
            return posicion_t(178, 129);
    }
    return posicion_t(0, 0);
}


Mapa::~Mapa() {
    for (int i = 0; i < alto; i++) {
        delete[] mapa[i];
    }

    delete[] mapa;
}
