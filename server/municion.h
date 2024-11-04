#ifndef MUNICION_H
#define MUNICION_H

#include <iostream>

#include "../common/orientacion.h"
#include "../common/posicion.h"

typedef enum Dispersion { NO, BAJA, MEDIA, ALTA } dispersion_e;

typedef enum Inclinacion { NO_TIENE, PARA_ARRIBA, ABAJO } inclinacion_e;

class Municion {
    friend class Arma;
    friend class Pato;
    friend class Gameloop;
private:
    const int id_arma;
    const posicion_t posicion_inicial;
    posicion_t posicion_actual;
    const int autonomia;
    const orientacion_e sentido;
    const dispersion_e dispersion;
    inclinacion_e inclinacion;

public:
    explicit Municion(int id, posicion_t pos_inicial, int alcance_maximo, orientacion_e direccion,
                      dispersion_e dispersion_bala);

    bool fuera_de_rango();

    void avanzar();
};


#endif
