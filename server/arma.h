#ifndef ARMA_H
#define ARMA_H

#include <iostream>
#include <string>

#include "posicion.h"
#include "orientacion.h"

#define ID_GRANADA 1
#define ID_BANANA 2
#define ID_PP_LASER 3
#define ID_LASER_RIFLE 4
#define ID_AK47 5
#define ID_DUEL_PISTOL 6
#define ID_COWBOY_PISTOL 7
#define ID_MAGNUM 8
#define ID_SHOTGUN 9
#define ID_SNIPER 10

class Arma {

protected:
    const int id_arma;
    const std::string nombre;
    int alcance;
    int municiones;
    bool retroceso;
    posicion_t posicion_spawn;
    bool agarrada;
    bool soltada;
    bool puede_agarrarse();

public:
    Arma(int id_arma, std::string nombre, int alcance, int municiones, bool tiene_retroceso);

    virtual ~Arma() = default;

    virtual void disparar(const orientacion_e& direccion) = 0;

    void agarrar();

    void soltar();

    bool tiene_retroceso();

    int obtener_alcance();

    int municiones_restantes();

    bool en_uso();

    posicion_t obtener_posicion_inicial();
};

#endif
