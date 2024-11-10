#include "municion.h"

#include <cmath>
#include <cstdlib>

#define AVANZAR 1

Municion::Municion(int id, posicion_t pos, int alcance_max, orientacion_e direccion,
                   dispersion_e dispersion_bala, int cantidad_rebotes):
        id_arma(id),
        posicion_inicial(pos),
        posicion_actual(pos),
        autonomia(alcance_max),
        sentido(direccion),
        dispersion(dispersion_bala),
        rebotes(cantidad_rebotes) {
    if (dispersion == NO) {
        inclinacion = NO_TIENE;
    } else {
        int inc = (rand() % 2) + 1;
        inclinacion = (inclinacion_e)inc;
    }
}

Municion::Municion(int id, posicion_t pos_inicial, int alcance_maximo, orientacion_e direccion,
                   dispersion_e dispersion_bala, inclinacion_e inc, int cantidad_rebotes):
        id_arma(id),
        posicion_inicial(pos_inicial),
        posicion_actual(posicion_inicial),
        autonomia(alcance_maximo),
        sentido(direccion),
        dispersion(dispersion_bala),
        inclinacion(inc),
        rebotes(cantidad_rebotes) {}

bool Municion::fuera_de_rango() {
    float dx = this->posicion_actual.coordenada_x - this->posicion_inicial.coordenada_x;
    float dy = this->posicion_actual.coordenada_y - this->posicion_inicial.coordenada_y;
    float s1 = pow(dx, 2);
    float s2 = pow(dy, 2);
    float distancia = sqrt(s1 + s2);
    return ((int)distancia > autonomia);
}

int buscar_inclinacion(const inclinacion_e& inclinacion) {
    int inc = 0;
    if (inclinacion == PARA_ARRIBA) {
        inc = 1;
    } else if (inclinacion == PARA_ABAJO) {  // cppcheck-suppress knownConditionTrueFalse
        inc = -1;
    }

    return inc;
}

int buscar_dispersion(const dispersion_e& dispersion) {
    int dis;
    switch (dispersion) {
        case BAJA:
            dis = 1;
            break;

        case MEDIA:
            dis = 2;
            break;

        case ALTA:
            dis = 3;
            break;
        default:
            dis = 0;
            break;
    }

    return dis;
}

bool Municion::avanzar(Mapa& mapa) {
    if (fuera_de_rango())
        return false;

    std::vector<int> posicion_mapa = mapa.posicion_en_mapa(this->posicion_actual);
    bool borde_bloque = mapa.borde_bloque(this->posicion_actual, this->sentido);
    bool piso_o_techo =
            mapa.piso_bloque(this->posicion_actual) || mapa.techo_bloque(this->posicion_actual);
    int inc, dis;
    if (this->sentido == ARRIBA) {
        if (piso_o_techo && mapa.mapa[posicion_mapa[1] - 1][posicion_mapa[0]] == 1) {
            if (rebotes > 0) {
                this->sentido = ABAJO;
                rebotes -= 1;
            } else {
                return false;
            }
            this->posicion_actual.coordenada_y += AVANZAR;
        } else {
            this->posicion_actual.coordenada_y -= AVANZAR;
        }
        inc = -(buscar_inclinacion(this->inclinacion));
        dis = buscar_dispersion(this->dispersion);
        this->posicion_actual.coordenada_x += (dis * inc);
    } else if (this->sentido == ABAJO) {
        if (piso_o_techo && mapa.mapa[posicion_mapa[1] + 1][posicion_mapa[0]] == 1) {
            if (rebotes > 0) {
                this->sentido = ARRIBA;
                rebotes -= 1;
            } else {
                return false;
            }
            this->posicion_actual.coordenada_y -= AVANZAR;
        } else {
            this->posicion_actual.coordenada_y += AVANZAR;
        }
        inc = -(buscar_inclinacion(this->inclinacion));
        dis = buscar_dispersion(this->dispersion);
        this->posicion_actual.coordenada_x += (dis * inc);
    } else {
        int lado = (this->sentido == DERECHA) ? AVANZAR : -AVANZAR;
        if (borde_bloque && mapa.mapa[posicion_mapa[1]][posicion_mapa[0] + lado] == 1) {
            if (rebotes > 0) {
                this->sentido = orientacion_e(-(this->sentido) + 1);
                rebotes -= 1;
            } else {
                return false;
            }
        }
        this->posicion_actual.coordenada_x += lado;
        inc = buscar_inclinacion(this->inclinacion);
        dis = buscar_dispersion(this->dispersion);
        this->posicion_actual.coordenada_y += (dis * inc);
    }
    return true;
}
