#include "sniper.h"

#include <iostream>

#include "config_juego.h"

#define SNIPER "Sniper"

#define CERO 0
#define UNO 1

Sniper::Sniper(posicion_t posicion_inicial):
        Arma(ID_SNIPER, SNIPER, ConfigJuego::ALCANCE_SNIPER, ConfigJuego::MUNICIONES_SNIPER, false,
             posicion_inicial) {}

bool Sniper::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (municiones == CERO)
        return false;
    Municion bala(ID_SNIPER, ajustar_posicion_disparo(direccion), (ConfigJuego::ALCANCE_SNIPER * TILE_A_METRO),
                  direccion, NO, balas.size());
    if (bala.avanzar(mapa))
        balas.push_back(bala);

    municiones -= UNO;
    return true;
}
