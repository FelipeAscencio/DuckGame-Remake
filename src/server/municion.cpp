#include "municion.h"

#include <cmath>
#include <cstdlib>

#define AVANZAR 0.5

Municion::Municion(int id, posicion_t pos, int alcance_max, orientacion_e direccion,
                   dispersion_e dispersion_bala, int cantidad_rebotes):
        id_arma(id),
        posicion_inicial(pos),
        posicion_actual(pos),
        autonomia(alcance_max),
        sentido(direccion),
        dispersion(dispersion_bala),
        rebotes(cantidad_rebotes) {
    if (dispersion == NO || sentido == ARRIBA) {
        inclinacion = NO_TIENE;
    } else {
        int inc = (rand() % 2) + 1;
        inclinacion = (inclinacion_e)inc;
    }
    subiendo = (this->sentido == ARRIBA) ? true : false;
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
        inc = -1;
    } else if (inclinacion == PARA_ABAJO) {  // cppcheck-suppress knownConditionTrueFalse
        inc = 1;
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
    if (posicion_mapa[0] == -1 || posicion_mapa[1] == -1)
        return false;

    bool borde_bloque = mapa.borde_bloque(this->posicion_actual, this->sentido);
    bool piso_o_techo =
            mapa.piso_bloque(this->posicion_actual) || mapa.techo_bloque(this->posicion_actual);
    int inc, dis;
    int lado;
    if (this->sentido == DERECHA){
        std::cout << "Derecha\n";
        lado = 1;
        if (borde_bloque && mapa.mapa[posicion_mapa[1]][posicion_mapa[0] + lado] != 0){
            std::cout << "Borde bloque y pared\n";
            if (rebotes > 0){
                this->sentido = IZQUIERDA;
                this->rebotes -= 1;
                lado = -1;
            } else {
                return false;
            }
        }
        int vertical = subiendo ? -1 : 1;
        if (piso_o_techo && mapa.mapa[posicion_mapa[1]+vertical][posicion_mapa[0]] != 0 && this->dispersion != NO){
            std::cout << "Techo/piso bloque\n";
            if (rebotes > 0){
                rebotes -= 1;
                this->inclinacion =  subiendo ? PARA_ABAJO : PARA_ARRIBA;
                subiendo = !subiendo;
            } else return false;
        }
        std::cout << "No hubo casos especiales\n";
        this->posicion_actual.coordenada_x += lado*AVANZAR;
        inc = buscar_inclinacion(this->inclinacion);
        dis = buscar_dispersion(this->dispersion);
        this->posicion_actual.coordenada_y = AVANZAR*(dis*inc);
    } else if (this->sentido ==  IZQUIERDA){
        lado = -1;
        if (borde_bloque && mapa.mapa[posicion_mapa[1]][posicion_mapa[0] + lado] != 0){
            if (rebotes > 0){
                this->sentido = DERECHA;
                this->rebotes -= 1;
                lado = 1;
            } else return false;
        }
        int vertical = subiendo ? -1 : 1;
        if (piso_o_techo && mapa.mapa[posicion_mapa[1]+vertical][posicion_mapa[0]] != 0 && this->dispersion != NO){
            if (rebotes > 0){
                this->rebotes -= 1;
                this->inclinacion = subiendo ? PARA_ABAJO : PARA_ARRIBA;
                subiendo = !subiendo;
            } else return false;
        }
        this->posicion_actual.coordenada_x += AVANZAR*lado;
        inc = buscar_inclinacion(this->inclinacion);
        dis = buscar_dispersion(this->dispersion);
        this->posicion_actual.coordenada_y += AVANZAR*(dis*inc);
    } else {
        lado = subiendo ? -1 : 1;
        if (piso_o_techo && mapa.mapa[posicion_mapa[1]+lado][posicion_mapa[0]] != 0){
            if (this->rebotes > 0){
                subiendo = !subiendo;
                rebotes -= 1;
                lado = -lado;
            } else return false;
        }
        this->posicion_actual.coordenada_y += AVANZAR*lado;
    }
    return true;
}
