#include "shotgun.h"

#define SHOTGUN "Shotgun"

#define CERO 0
#define UNO 1
#define DOS 2
#define CUATRO 4
#define CANTIDAD_INDICES_SHOTGUN 6

Shotgun::Shotgun(posicion_t posicion_inicial):
        Arma(ID_SHOTGUN, SHOTGUN, ConfigJuego::ALCANCE_MINIMO_SHOTGUN,
             ConfigJuego::MUNICIONES_SHOTGUN, true, posicion_inicial),
        debe_recargar(false),
        alcance_maximo(ConfigJuego::ALCANCE_MAXIMO_SHOTGUN) {}

dispersion_e obtener_dispersion(int bala_disparada) {
    if (bala_disparada == CERO)
        return NO;
    if (bala_disparada == UNO)
        return BAJA;
    if (bala_disparada < CUATRO)
        return MEDIA;

    return ALTA;
}

inclinacion_e obtener_inclinacion(int bala_disparada) {
    if (bala_disparada < DOS)
        return NO_TIENE;

    if (bala_disparada < CUATRO)
        return PARA_ARRIBA;

    return PARA_ABAJO;
}

void Shotgun::eliminar_bala(const int& indice) {
    int inicio_tanda_balas = CERO;
    if (indice >= CANTIDAD_INDICES_SHOTGUN)
        inicio_tanda_balas = CANTIDAD_INDICES_SHOTGUN;

    for (int i = CERO; i < CANTIDAD_INDICES_SHOTGUN; i++) {
        balas.erase(balas.begin() + inicio_tanda_balas);
    }

    for (int i = indice; i < (int)balas.size(); i++) {
        balas[i].nro_bala -= CANTIDAD_INDICES_SHOTGUN;
    }
}

bool Shotgun::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (municiones == CERO)
        return false;

    if (debe_recargar) {
        debe_recargar = false;
    } else {
        for (int i = CERO; i < ConfigJuego::PERDIGONES_POR_DISPARO_SG; i++) {
            inclinacion_e inc = obtener_inclinacion(i);
            dispersion_e dis = obtener_dispersion(i);
            Municion m(ID_SHOTGUN, ajustar_posicion_disparo(direccion),
                       (ConfigJuego::ALCANCE_MAXIMO_SHOTGUN * TILE_A_METRO), direccion, dis, inc,
                       balas.size());
            if (m.avanzar(mapa)) {
                balas.push_back(m);
            }
        }

        municiones -= UNO;
        debe_recargar = true;
    }

    return debe_recargar;
}
