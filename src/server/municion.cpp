#include "municion.h"

#include <cmath>
#include <cstdlib>

#define AVANZAR 0.75

#define MENOS_UNO -1
#define CERO 0
#define UNO 1
#define DOS 2
#define TRES 3
#define MIN_X_MAPA 1
#define MAX_X_MAPA 199

#define VALOR_DISPERSION_NULA 0
#define VALOR_DISPERSION_BAJA 0.5
#define VALOR_DISPERSION_MEDIA 1
#define VALOR_DISPERSION_ALTA 1.5

Municion::Municion(const int& id, const posicion_t& pos_inicial, const int& alcance_maximo,
                   const orientacion_e& direccion, const dispersion_e& dispersion_bala,
                   const int& nro):
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
        int inc = (rand() % DOS) + UNO;
        inclinacion = (inclinacion_e)inc;
    }

    subiendo = (this->sentido == ARRIBA) ? true : false;
}

Municion::Municion(const int& id, const posicion_t& pos_inicial, const int& alcance_maximo,
                   const orientacion_e& direccion, const dispersion_e& dispersion_bala,
                   const inclinacion_e& inc, const int& nro):
        id_arma(id),
        posicion_inicial(pos_inicial),
        posicion_actual(posicion_inicial),
        autonomia(alcance_maximo),
        sentido(direccion),
        dispersion(dispersion_bala),
        inclinacion(inc),
        nro_bala(nro) {
    subiendo = (this->sentido == ARRIBA) ? true : false;
}

Municion::Municion(const Municion& m):
        id_arma(m.id_arma),
        posicion_inicial(m.posicion_inicial),
        posicion_actual(m.posicion_actual),
        autonomia(m.autonomia),
        sentido(m.sentido),
        dispersion(m.dispersion),
        inclinacion(m.inclinacion),
        subiendo(m.subiendo),
        nro_bala(m.nro_bala) {}

bool Municion::fuera_de_rango(Mapa& mapa) {
    if (this->posicion_actual.coordenada_x >= mapa.largo * TILE_A_METRO ||
        this->posicion_actual.coordenada_x <= CERO ||
        this->posicion_actual.coordenada_y >= mapa.alto * TILE_A_METRO ||
        this->posicion_actual.coordenada_y <= CERO)
        return true;

    float dx = this->posicion_actual.coordenada_x - this->posicion_inicial.coordenada_x;
    float dy = this->posicion_actual.coordenada_y - this->posicion_inicial.coordenada_y;
    float s1 = pow(dx, DOS);
    float s2 = pow(dy, DOS);
    float distancia = sqrt(s1 + s2);
    return ((int)distancia > autonomia);
}

float buscar_dispersion(const dispersion_e& dispersion) {
    float dis;
    switch (dispersion) {
        case BAJA:
            dis = VALOR_DISPERSION_BAJA;
            break;

        case MEDIA:
            dis = VALOR_DISPERSION_MEDIA;
            break;

        case ALTA:
            dis = VALOR_DISPERSION_ALTA;
            break;

        default:
            dis = VALOR_DISPERSION_NULA;
            break;
    }

    return dis;
}

bool Municion::avanzar(Mapa& mapa) {
    std::vector<int> posicion_mapa = mapa.posicion_en_mapa(this->posicion_actual);
    if (posicion_mapa[0] == -1 || posicion_mapa[1] == -1) return false;
    if (fuera_de_rango(mapa))
        return false;

    bool borde_bloque = mapa.borde_bloque(this->posicion_actual, this->sentido);
    bool techo = mapa.techo_bloque(this->posicion_actual);
    int lado;
    int inc;
    float dis;
    int arriba_de_todo = posicion_mapa[UNO] == CERO ? CERO : UNO;
    if (this->sentido == ARRIBA) {
        if (techo && mapa.mapa[posicion_mapa[UNO] - arriba_de_todo][posicion_mapa[CERO]] != CERO)
            return false;

        inc = this->inclinacion == PARA_ARRIBA ? MENOS_UNO : UNO;
        dis = buscar_dispersion(this->dispersion);
        if (dis != CERO) {
            if (borde_bloque && mapa.mapa[posicion_mapa[UNO]][posicion_mapa[CERO] + inc] != CERO) {
                return false;
            }
        }

        this->posicion_actual.coordenada_y -= AVANZAR;
        this->posicion_actual.coordenada_x += AVANZAR * inc * dis;
    } else {
        lado = this->sentido == DERECHA ? UNO : MENOS_UNO;
        inc = this->inclinacion == PARA_ARRIBA ? MENOS_UNO : UNO;
        if (borde_bloque && (posicion_mapa[0] == 0 || posicion_mapa[0] == mapa.largo -1)) lado = 0;
        if (borde_bloque && mapa.mapa[posicion_mapa[UNO]][posicion_mapa[CERO] + lado] != CERO && mapa.mapa[posicion_mapa[UNO]][posicion_mapa[CERO] + lado] != TRES){
            return false;
        }
        dis = buscar_dispersion(this->dispersion);
        if (dis != CERO) {
            if (mapa.piso_bloque(this->posicion_actual) || techo) {
                if (mapa.mapa[posicion_mapa[UNO] - inc][posicion_mapa[CERO]] != CERO) {
                    return false;
                }
            }
        }

        this->posicion_actual.coordenada_x += AVANZAR * lado;
        this->posicion_actual.coordenada_y += AVANZAR * inc * dis;
    }

    // Si las balas llegan al borde del mapa, se sacan para que no sean visibles.
    if (posicion_actual.coordenada_x <= MIN_X_MAPA){
        posicion_actual.coordenada_x = MENOS_UNO;
    } else if (posicion_actual.coordenada_x >= MAX_X_MAPA){
        posicion_actual.coordenada_x = MENOS_UNO;
    }

    return true;
}
