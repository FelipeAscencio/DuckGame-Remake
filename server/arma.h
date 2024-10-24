#ifndef ARMA_H
#define ARMA_H

#include <iostream>
#include <string>

#include "posicion.h"

class Arma {
protected:
    const std::string nombre;
    int alcance;
    int municiones;
    bool retroceso;
    posicion_t posicion_spawn;
    bool agarrada;
    bool soltada;
    bool puede_agarrarse();

public:
    Arma(std::string nombre, int alcance, int municiones, bool tiene_retroceso);

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
