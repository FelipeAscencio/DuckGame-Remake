#include "ak47.h"

#include <iostream>

#define AK_47 "AK-47"
#define ALCANCE 13
#define MUNICIONES 30
#define TILE_A_METRO 10
#define CERO 0
#define BALAS_POR_DISPARO 1

AK47::AK47(posicion_t posicion_inicial):
        Arma(ID_AK47, AK_47, ALCANCE, MUNICIONES, true, posicion_inicial),
        ultima_bala_disparada(NO) {}

void AK47::modificar_dispersion_balas(bool disparando) {
    if (disparando) {
        switch (this->ultima_bala_disparada) {
            case NO:
                this->ultima_bala_disparada = BAJA;
                break;
            case BAJA:
                this->ultima_bala_disparada = MEDIA;
                break;

            case MEDIA:
                this->ultima_bala_disparada = ALTA;
                break;
            default:
                break;
        }
    } else {
        switch (this->ultima_bala_disparada) {
            case BAJA:
                this->ultima_bala_disparada = NO;
                break;

            case MEDIA:
                this->ultima_bala_disparada = BAJA;
                break;

            case ALTA:
                this->ultima_bala_disparada = MEDIA;
                break;
            default:
                break;
        }
    }
}


bool AK47::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (this->municiones == CERO)
        return false;
    modificar_dispersion_balas(true);
    Municion* bala_disparada =
            new Municion(this->id_arma, this->posicion_spawn, ALCANCE * TILE_A_METRO, direccion,
                         this->ultima_bala_disparada, 0);
    std::cout << "Orientacion bala: " << bala_disparada->get_sentido() << std::endl;
    if (bala_disparada->avanzar(mapa)) {
        std::cout << "Bala disparada\n";
        balas.push_back(bala_disparada);
    } else {
        delete bala_disparada;
    }
    this->municiones -= BALAS_POR_DISPARO;
    return true;
}
