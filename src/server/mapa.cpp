#include "server/mapa.h"

#include <fstream>
#include <string>

#define MSJ_ERROR_ARCHIVO_MAPA "Error leyendo archivo del mapa"
#define ARCHIVO_MAPA "../data/mapa_"
#define TXT ".txt"
#define MENOS_UNO -1
#define CERO 0
#define UNO 1
#define DOS 2
#define PRIMERA_POSICION 0
#define SEGUNDA_POSICION 1
#define CANTIDAD_MAPAS 2
#define ID_PRIMER_MAPA 1
#define CONSTANTE_AUXILIAR_CHAR_MAPA 48

#define ID_PRIMER_PATO 0
#define ID_SEGUNDO_PATO 1
#define ID_TERCER_PATO 2
#define ID_CUARTO_PATO 3
#define ID_QUINTO_PATO 4
#define ID_SEXTO_PATO 5
#define ID_SEPTIMO_PATO 6
#define ID_OCTAVO_PATO 7

#define POS_INI_PATO_1_MAPA_1_X 5
#define POS_INI_PATO_2_MAPA_1_X 175
#define POS_INI_PATO_3_MAPA_1_X 63
#define POS_INI_PATO_4_MAPA_1_X 115
#define POS_INI_PATO_5_MAPA_1_X 192
#define POS_INI_PATO_6_MAPA_1_X 85
#define POS_INI_PATO_7_MAPA_1_X 137
#define POS_INI_PATO_8_MAPA_1_X 149
#define POS_INI_PATO_1_MAPA_1_Y 89
#define POS_INI_PATO_2_MAPA_1_Y 29
#define POS_INI_PATO_3_MAPA_1_Y 49
#define POS_INI_PATO_4_MAPA_1_Y 69
#define POS_INI_PATO_5_MAPA_1_Y 79
#define POS_INI_PATO_6_MAPA_1_Y 99
#define POS_INI_PATO_7_MAPA_1_Y 99
#define POS_INI_PATO_8_MAPA_1_Y 69

#define POS_INI_PATO_1_MAPA_2_X 63
#define POS_INI_PATO_2_MAPA_2_X 148
#define POS_INI_PATO_3_MAPA_2_X 9
#define POS_INI_PATO_4_MAPA_2_X 187
#define POS_INI_PATO_5_MAPA_2_X 33
#define POS_INI_PATO_6_MAPA_2_X 96
#define POS_INI_PATO_7_MAPA_2_X 125
#define POS_INI_PATO_8_MAPA_2_X 178
#define POS_INI_PATO_1_MAPA_2_Y 59
#define POS_INI_PATO_2_MAPA_2_Y 69
#define POS_INI_PATO_3_MAPA_2_Y 99
#define POS_INI_PATO_4_MAPA_2_Y 99
#define POS_INI_PATO_5_MAPA_2_Y 129
#define POS_INI_PATO_6_MAPA_2_Y 129
#define POS_INI_PATO_7_MAPA_2_Y 129
#define POS_INI_PATO_8_MAPA_2_Y 129

#define POS_SPAWN_1_MAPA_1_X 170
#define POS_SPAWN_2_MAPA_1_X 130
#define POS_SPAWN_3_MAPA_1_X 55
#define POS_SPAWN_4_MAPA_1_X 20
#define POS_SPAWN_5_MAPA_1_X 112
#define POS_SPAWN_1_MAPA_1_Y 29
#define POS_SPAWN_2_MAPA_1_Y 99
#define POS_SPAWN_3_MAPA_1_Y 49
#define POS_SPAWN_4_MAPA_1_Y 89
#define POS_SPAWN_5_MAPA_1_Y 69

#define POS_SPAWN_1_MAPA_2_X 100
#define POS_SPAWN_2_MAPA_2_X 25
#define POS_SPAWN_3_MAPA_2_X 187
#define POS_SPAWN_4_MAPA_2_X 91
#define POS_SPAWN_5_MAPA_2_X 142
#define POS_SPAWN_1_MAPA_2_Y 59
#define POS_SPAWN_2_MAPA_2_Y 99
#define POS_SPAWN_3_MAPA_2_Y 99
#define POS_SPAWN_4_MAPA_2_Y 129
#define POS_SPAWN_5_MAPA_2_Y 129

#define POS_CAJA_1_MAPA_1_X 85
#define POS_CAJA_2_MAPA_1_X 35
#define POS_CAJA_3_MAPA_1_X 45
#define POS_CAJA_1_MAPA_1_Y 99
#define POS_CAJA_2_MAPA_1_Y 89
#define POS_CAJA_3_MAPA_1_Y 49
#define POS_CAJA_1_MAPA_2_X 105
#define POS_CAJA_2_MAPA_2_X 85
#define POS_CAJA_3_MAPA_2_X 55
#define POS_CAJA_1_MAPA_2_Y 129
#define POS_CAJA_2_MAPA_2_Y 59
#define POS_CAJA_3_MAPA_2_Y 129

Mapa::Mapa(): id_mapa((rand()%CANTIDAD_MAPAS) + UNO){
    try {
        cargar_mapa(this->id_mapa);
    } catch (const ErrorMapa&){}
}

void Mapa::cargar_mapa(const int& id_mapa){
    std::string ruta_mapa = ARCHIVO_MAPA + std::to_string(id_mapa) + TXT;
    std::ifstream archivo_mapa(ruta_mapa);
    if (!archivo_mapa.is_open()) {
        std::cerr << MSJ_ERROR_ARCHIVO_MAPA << std::endl;
        throw ErrorMapa();
    }

    int leido;
    archivo_mapa >> leido;
    this->alto = leido;
    archivo_mapa >> leido;
    this->largo = leido;
    this->mapa = new int*[alto];
    for (int i = CERO; i < alto; i++) {
        this->mapa[i] = new int[largo];
    }

    int i = CERO;
    while (i < alto) {
        int j = CERO;
        while (j < largo) {
            char c;
            archivo_mapa >> c;
            this->mapa[i][j] =
                    ((int)c - CONSTANTE_AUXILIAR_CHAR_MAPA);
            j++;
        }

        i++;
    }
}

std::vector<int> Mapa::posicion_en_mapa(const posicion_t& pos) {
    std::vector<int> posicion(DOS);
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
    return ((int)pos.coordenada_y % TILE_A_METRO == CERO);
}

posicion_t Mapa::posicion_inicial(const int& id_pato) {
    if (this->id_mapa == ID_PRIMER_MAPA) {
        if (id_pato == ID_PRIMER_PATO)
            return posicion_t(POS_INI_PATO_1_MAPA_1_X, POS_INI_PATO_1_MAPA_1_Y);
        else if (id_pato == ID_SEGUNDO_PATO)
            return posicion_t(POS_INI_PATO_2_MAPA_1_X, POS_INI_PATO_2_MAPA_1_Y);
        else if (id_pato == ID_TERCER_PATO)
            return posicion_t(POS_INI_PATO_3_MAPA_1_X, POS_INI_PATO_3_MAPA_1_Y);
        else if (id_pato == ID_CUARTO_PATO)
            return posicion_t(POS_INI_PATO_4_MAPA_1_X, POS_INI_PATO_4_MAPA_1_Y);
        else if (id_pato == ID_QUINTO_PATO)
            return posicion_t(POS_INI_PATO_5_MAPA_1_X, POS_INI_PATO_5_MAPA_1_Y);
        else if (id_pato == ID_SEXTO_PATO)
            return posicion_t(POS_INI_PATO_6_MAPA_1_X, POS_INI_PATO_6_MAPA_1_Y);
        else if (id_pato == ID_SEPTIMO_PATO)
            return posicion_t(POS_INI_PATO_7_MAPA_1_X, POS_INI_PATO_7_MAPA_1_Y);
        else if (id_pato == ID_OCTAVO_PATO)
            return posicion_t(POS_INI_PATO_8_MAPA_1_X, POS_INI_PATO_8_MAPA_1_Y);
    } else {
        if (id_pato == ID_PRIMER_PATO)
            return posicion_t(POS_INI_PATO_1_MAPA_2_X, POS_INI_PATO_1_MAPA_2_Y);
        else if (id_pato == ID_SEGUNDO_PATO)
            return posicion_t(POS_INI_PATO_2_MAPA_2_X, POS_INI_PATO_2_MAPA_2_Y);
        else if (id_pato == ID_TERCER_PATO)
            return posicion_t(POS_INI_PATO_3_MAPA_2_X, POS_INI_PATO_3_MAPA_2_Y);
        else if (id_pato == ID_CUARTO_PATO)
            return posicion_t(POS_INI_PATO_4_MAPA_2_X, POS_INI_PATO_4_MAPA_2_Y);
        else if (id_pato == ID_QUINTO_PATO)
            return posicion_t(POS_INI_PATO_5_MAPA_2_X, POS_INI_PATO_5_MAPA_2_Y);
        else if (id_pato == ID_SEXTO_PATO)
            return posicion_t(POS_INI_PATO_6_MAPA_2_X, POS_INI_PATO_6_MAPA_2_Y);
        else if (id_pato == ID_SEPTIMO_PATO)
            return posicion_t(POS_INI_PATO_7_MAPA_2_X, POS_INI_PATO_7_MAPA_2_Y);
        else if (id_pato == ID_OCTAVO_PATO)
            return posicion_t(POS_INI_PATO_8_MAPA_2_X, POS_INI_PATO_8_MAPA_2_Y);
    }

    return posicion_t(CERO, CERO);
}

void Mapa::inicializar_puntos_spawn(std::vector<Spawn>& puntos_spawn){
    if (id_mapa == ID_PRIMER_MAPA){
        puntos_spawn.push_back(Spawn(posicion_t(POS_SPAWN_1_MAPA_1_X, POS_SPAWN_1_MAPA_1_Y)));
        puntos_spawn.push_back(Spawn(posicion_t(POS_SPAWN_2_MAPA_1_X, POS_SPAWN_2_MAPA_1_Y)));
        puntos_spawn.push_back(Spawn(posicion_t(POS_SPAWN_3_MAPA_1_X, POS_SPAWN_3_MAPA_1_Y)));
        puntos_spawn.push_back(Spawn(posicion_t(POS_SPAWN_4_MAPA_1_X, POS_SPAWN_4_MAPA_1_Y)));
        puntos_spawn.push_back(Spawn(posicion_t(POS_SPAWN_5_MAPA_1_X, POS_SPAWN_5_MAPA_1_Y)));   
    } else {
        puntos_spawn.push_back(Spawn(posicion_t(POS_SPAWN_1_MAPA_2_X, POS_SPAWN_1_MAPA_2_Y)));
        puntos_spawn.push_back(Spawn(posicion_t(POS_SPAWN_2_MAPA_2_X, POS_SPAWN_2_MAPA_2_Y)));
        puntos_spawn.push_back(Spawn(posicion_t(POS_SPAWN_3_MAPA_2_X, POS_SPAWN_3_MAPA_2_Y)));
        puntos_spawn.push_back(Spawn(posicion_t(POS_SPAWN_4_MAPA_2_X, POS_SPAWN_4_MAPA_2_Y)));
        puntos_spawn.push_back(Spawn(posicion_t(POS_SPAWN_5_MAPA_2_X, POS_SPAWN_5_MAPA_2_Y)));
    }
}

posicion_t Mapa::posicion_caja(const int& caja){
    if (id_mapa == ID_PRIMER_MAPA){
        if (caja == CERO){
            return posicion_t(POS_CAJA_1_MAPA_1_X, POS_CAJA_1_MAPA_1_Y);
        } else if (caja == UNO){
            return posicion_t(POS_CAJA_2_MAPA_1_X, POS_CAJA_2_MAPA_1_Y);
        } else {
            return posicion_t(POS_CAJA_3_MAPA_1_X, POS_CAJA_3_MAPA_1_Y);
        }
    } else {
        if (caja == CERO){
            return posicion_t(POS_CAJA_1_MAPA_2_X, POS_CAJA_1_MAPA_2_Y);
        } else if (caja == UNO){
            return posicion_t(POS_CAJA_2_MAPA_2_X, POS_CAJA_2_MAPA_2_Y);
        } else {
            return posicion_t(POS_CAJA_3_MAPA_2_X, POS_CAJA_3_MAPA_2_Y);
        }
    }
}

void Mapa::resetear(){
    for (int i = CERO; i < alto; i++) {
        delete[] mapa[i];
    }

    delete[] mapa;
    this->id_mapa = rand()%CANTIDAD_MAPAS + UNO;
    try{
        cargar_mapa(id_mapa);
    } catch (const ErrorMapa&){}
}

Mapa::~Mapa() {
    for (int i = CERO; i < alto; i++) {
        delete[] mapa[i];
    }
    delete[] mapa;
}
