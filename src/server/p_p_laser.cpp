#include "p_p_laser.h"

#include <iostream>

#define PEW_PEW_LASER "Pew-Pew Laser"
#define ALCANCE_MINIMO 35
#define MUNICIONES 12
#define ALCANCE_MAXIMO 38
#define LASERS_POR_DISPARO 3

PewPewLaser::PewPewLaser(posicion_t posicion_inicial):
        Arma(ID_PP_LASER, PEW_PEW_LASER, ALCANCE_MINIMO, MUNICIONES, false, posicion_inicial),
        alcance_maximo(ALCANCE_MAXIMO) {}

inclinacion_e buscar_inclinacion(const int& bala){
    if (bala == 0) return NO_TIENE;
    else if (bala == 1) return PARA_ARRIBA;
    else return PARA_ABAJO;
}

dispersion_e buscar_dispersion(const int& bala){
    if (bala == 0) return NO;
    else return MEDIA;
}

void PewPewLaser::control_atributos(Mapa& mapa){
    Arma::control_atributos(mapa);
    iteraciones_desde_disparo += 1;
}

bool PewPewLaser::disparar(const orientacion_e& direccion, Mapa& mapa) {
    if (this->municiones == 0) return false;
    if (iteraciones_desde_disparo == 0) return true;
    inclinacion_e inc;
    dispersion_e dis;
    for (int i = 0; i < LASERS_POR_DISPARO; i++){
        Municion* m = new Municion(ID_PP_LASER, this->posicion_spawn, (ALCANCE_MAXIMO * TILE_A_METRO), direccion, dis, inc, municiones_iniciales - municiones);    
        if (m->avanzar(mapa)){
            balas.push_back(m);
        } else {
            delete m;
        }
    }
    iteraciones_desde_disparo = 0;
    municiones -= 1;
    return true;
}
