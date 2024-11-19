#include "municion.h"

#include <cmath>
#include <cstdlib>

#define AVANZAR 0.75

Municion::Municion(const int& id, const posicion_t& pos_inicial, const int& alcance_maximo, const orientacion_e& direccion,
                      const dispersion_e& dispersion_bala, const int& nro):
        id_arma(id),
        posicion_inicial(pos_inicial),
        posicion_actual(pos_inicial),
        autonomia(alcance_maximo),
        sentido(direccion),
        dispersion(dispersion_bala),
        nro_bala(nro) {
    if (dispersion == NO || sentido == ARRIBA) {
        inclinacion = NO_TIENE;
    } else {
        int inc = (rand() % 2) + 1;
        inclinacion = (inclinacion_e)inc;
    }
    subiendo = (this->sentido == ARRIBA) ? true : false;
}

Municion::Municion(const int& id, const posicion_t& pos_inicial, const int& alcance_maximo, const orientacion_e& direccion,
                      const dispersion_e& dispersion_bala, const inclinacion_e& inc, const int& nro):
        id_arma(id),
        posicion_inicial(pos_inicial),
        posicion_actual(posicion_inicial),
        autonomia(alcance_maximo),
        sentido(direccion),
        dispersion(dispersion_bala),
        inclinacion(inc),
        nro_bala(nro) {}

bool Municion::fuera_de_rango(Mapa& mapa) {
    if (this->posicion_actual.coordenada_x >= mapa.largo * TILE_A_METRO || this->posicion_actual.coordenada_x <= 0 || this->posicion_actual.coordenada_y >= mapa.alto * TILE_A_METRO || this->posicion_actual.coordenada_y <= 0) return true;
    float dx = this->posicion_actual.coordenada_x - this->posicion_inicial.coordenada_x;
    float dy = this->posicion_actual.coordenada_y - this->posicion_inicial.coordenada_y;
    float s1 = pow(dx, 2);
    float s2 = pow(dy, 2);
    float distancia = sqrt(s1 + s2);
    return ((int)distancia > autonomia);
}

float buscar_dispersion(const dispersion_e& dispersion) {
    float dis;
    switch (dispersion) {
        case BAJA:
            dis = 0.5;
            break;

        case MEDIA:
            dis = 1;
            break;

        case ALTA:
            dis = 1.5;
            break;
        default:
            dis = 0;
            break;
    }

    return dis;
}

bool Municion::avanzar(Mapa& mapa) {
    std::vector<int> posicion_mapa = mapa.posicion_en_mapa(this->posicion_actual);
    if (fuera_de_rango(mapa)) return false;
    bool borde_bloque = mapa.borde_bloque(this->posicion_actual, this->sentido);
    bool techo = mapa.techo_bloque(this->posicion_actual);
    int lado;
    int inc;
    float dis;
    if (this->sentido == ARRIBA){
        int arriba_de_todo = posicion_mapa[1] == 0 ? 0 : 1;
        if (techo && mapa.mapa[posicion_mapa[1] - arriba_de_todo][posicion_mapa[0]] != 0) return false;
        this->posicion_actual.coordenada_y -= AVANZAR;
    } else {
        lado = this->sentido == DERECHA ? 1 : -1;
        if (borde_bloque && mapa.mapa[posicion_mapa[1]-1][posicion_mapa[0] + lado] != 0) return false;
        this->posicion_actual.coordenada_x += AVANZAR * lado;
        inc = subiendo ? -1 : 1;
        dis = buscar_dispersion(this->dispersion);
        this->posicion_actual.coordenada_y += AVANZAR*inc*dis;
    }
    return true;
}
