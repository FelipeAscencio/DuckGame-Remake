// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef MUNICION_H
#define MUNICION_H

#include <iostream>

#include "../common/orientacion.h"
#include "../common/posicion.h"

#include "mapa.h"

typedef enum Dispersion { NO, BAJA, MEDIA, ALTA } dispersion_e;

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
    const int id_arma;
    const posicion_t posicion_inicial;
    posicion_t posicion_actual;
    const int autonomia;
    orientacion_e sentido;
    const dispersion_e dispersion;
    inclinacion_e inclinacion;
    int rebotes;
    bool subiendo;
    int nro_bala;

public:
    // Constructor de la clase.
    explicit Municion(int id, posicion_t pos_inicial, int alcance_maximo, orientacion_e direccion,
                      dispersion_e dispersion_bala, int rebotes, int nro);

    explicit Municion(int id, posicion_t pos_inicial, int alcance_maximo, orientacion_e direccion,
                      dispersion_e dispersion_bala, inclinacion_e inc, int rebotes, int nro);

    // Verifica si la munición ha excedido su alcance máximo.
    bool fuera_de_rango();

    orientacion_e get_sentido() {return this->sentido;}

    // Avanza la posición de la munición, considerando su dirección, inclinación y dispersión.
    bool avanzar(Mapa& mapa);
};

#endif  // MUNICION_H
