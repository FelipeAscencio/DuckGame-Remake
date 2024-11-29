// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef MUNICION_H
#define MUNICION_H

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "../common/orientacion.h"
#include "../common/posicion.h"

#include "mapa.h"

// 'Enum' que encapsula los tipos de dispersion de las balas.
typedef enum Dispersion { NO, BAJA, MEDIA, ALTA } dispersion_e;

// 'Enum' que encapsula los tipos de inclinacion de las balas.
typedef enum Inclinacion { NO_TIENE, PARA_ARRIBA, PARA_ABAJO } inclinacion_e;

// La clase 'Municion' implementa la logica de las balas
// una vez que ya son disparadas.
class Municion {
    friend class Arma;
    friend class Pato;
    friend class Gameloop;
    friend struct InformacionBala;
    friend struct EstadoJuego;
    friend class Shotgun;

private:
    int id_arma;
    posicion_t posicion_inicial;
    posicion_t posicion_actual;
    int autonomia;
    orientacion_e sentido;
    dispersion_e dispersion;
    inclinacion_e inclinacion;
    bool subiendo;
    int nro_bala;

public:
    // Primera variante del constructor de la clase.
    explicit Municion(const int& id, const posicion_t& pos_inicial, const int& alcance_maximo,
                      const orientacion_e& direccion, const dispersion_e& dispersion_bala,
                      const int& nro);

    // Segunda variante del constructor de la clase.
    explicit Municion(const int& id, const posicion_t& pos_inicial, const int& alcance_maximo,
                      const orientacion_e& direccion, const dispersion_e& dispersion_bala,
                      const inclinacion_e& inc, const int& nro);

    // Verifica si la municion ha excedido su alcance maximo.
    bool fuera_de_rango(Mapa& mapa);

    // Getter de sentido.
    orientacion_e get_sentido() { return this->sentido; }

    // Avanza la posicion de la municion, considerando su direccion, inclinacion y dispersion.
    bool avanzar(Mapa& mapa);

    // Tercera variante del constructor de la clase.
    Municion(const Municion& m);

    // Permito el movimiento del objeto.
    Municion(Municion&&) = default;
    Municion& operator=(Municion&&) = default;
};

#endif  // MUNICION_H
