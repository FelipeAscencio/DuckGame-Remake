#include "shotgun.h"

#include <iostream>

#define SHOTGUN "Shotgun"
#define ALCANCE_MINIMO 7
#define ALCANCE_MAXIMO 9
#define MUNICIONES 3
#define PERDIGONES_POR_DISPARO 6

Shotgun::Shotgun(posicion_t posicion_inicial):
        Arma(ID_SHOTGUN, SHOTGUN, ALCANCE_MINIMO, MUNICIONES, true, posicion_inicial),
        debe_recargar(false),
        alcance_maximo(ALCANCE_MAXIMO) {}

dispersion_e obtener_dispersion(int bala_disparada) {
    if (bala_disparada == 0)
        return NO;
    if (bala_disparada == 1)
        return BAJA;
    if (bala_disparada < 4)
        return MEDIA;
    return ALTA;
}

inclinacion_e obtener_inclinacion(int bala_disparada) {
    if (bala_disparada < 2)
        return NO_TIENE;
    if (bala_disparada < 4)
        return PARA_ARRIBA;
    return PARA_ABAJO;
}

void Shotgun::eliminar_bala(const int& indice) {
    int inicio_tanda_balas = 0;
    if (indice >= 6)
        inicio_tanda_balas = 6;
    for (int i = 0; i < 6; i++) {
        balas.erase(balas.begin() + inicio_tanda_balas);
    }
    for (int i = indice; i < (int)balas.size(); i++) {
        balas[i].nro_bala -= 6;
    }
}

bool Shotgun::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (municiones == 0)
        return false;

    if (debe_recargar) {
        debe_recargar = false;
    } else {
        for (int i = 0; i < PERDIGONES_POR_DISPARO; i++) {
            inclinacion_e inc = obtener_inclinacion(i);
            dispersion_e dis = obtener_dispersion(i);
            Municion m(ID_SHOTGUN, this->posicion_spawn, (ALCANCE_MAXIMO * TILE_A_METRO),
                                 direccion, dis, inc, balas.size());
            if (m.avanzar(mapa)) {
                balas.push_back(m);
            }
        }
        municiones -= 1;
        debe_recargar = true;
    }
    return debe_recargar;
}
