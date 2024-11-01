#include "municion.h"

#include <cmath>
#include <cstdlib>

#define AVANZAR 1

Municion::Municion(int id, posicion_t pos, int alcance_max, orientacion_e direccion,
                   dispersion_e dispersion_bala):
        id_arma(id),
        posicion_inicial(pos),
        posicion_actual(pos),
        autonomia(alcance_max),
        sentido(direccion),
        dispersion(dispersion_bala) {
    if (dispersion == NO) {
        inclinacion = NO_TIENE;
    } else {
        int inc = (rand() % 2) + 1;
        inclinacion = (inclinacion_e)inc;
    }
}

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
    if (inclinacion == ARRIBA) {
        inc = 1;
    } else if (inclinacion == ABAJO) {  // cppcheck-suppress knownConditionTrueFalse
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

void Municion::avanzar() {
    if (fuera_de_rango())
        return;
    int inc, dis;
    if (this->sentido == ARRIBA) {
        this->posicion_actual.coordenada_y -= AVANZAR;
        inc = -(buscar_inclinacion(this->inclinacion));
        dis = buscar_dispersion(this->dispersion);
        this->posicion_actual.coordenada_x += (dis * inc);
    } else {
        int lado = (this->sentido == DERECHA) ? AVANZAR : -AVANZAR;
        this->posicion_actual.coordenada_x += lado;
        inc = buscar_inclinacion(this->inclinacion);
        dis = buscar_dispersion(this->dispersion);
        this->posicion_actual.coordenada_y += (dis * inc);
    }
}
