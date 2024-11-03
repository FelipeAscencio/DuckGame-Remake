#ifndef ARMA_H
#define ARMA_H

#include <iostream>
#include <string>
#include <vector>

#include "../common/orientacion.h"
#include "../common/posicion.h"

#include "municion.h"

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
    friend struct InformacionArma;
    friend struct EstadoJuego;

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

    std::vector<Municion*> balas;

public:
    Arma(const int& id_arma, const std::string& nombre, const int& alcance, const int& municiones,
         bool tiene_retroceso, posicion_t posicion_inicial);

    virtual ~Arma() = default;

    virtual bool disparar(const orientacion_e& direccion) = 0;

    virtual void chequeo_balas() = 0;

    void agarrar();

    void soltar();

    bool tiene_retroceso();

    int obtener_alcance();

    int municiones_restantes();

    bool en_uso();

    posicion_t obtener_posicion_inicial();

    int obtener_id() const { return id_arma; }
};

#endif
