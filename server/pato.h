#ifndef PATO_H
#define PATO_H

#include <iostream>

#include "arma.h"
#include "orientacion.h"
#include "posicion.h"

class Pato {
private:
    int id_jugador;
    posicion_t posicion;
    bool vivo;
    bool posee_arma;
    bool posee_armadura;
    bool posee_casco;
    bool agachado;
    orientacion_e orientacion;
    Arma* arma_equipada;

public:
    explicit Pato(int id);
    posicion_t obtener_posicion();
    bool mover_derecha();
    bool mover_izquierda();
    void saltar();
    void aletear();
    bool tiene_arma();
    void agacharse();
    orientacion_e obtener_orientacion();
    void cambiar_orientacion(orientacion_e nueva_orientacion);
    bool agarrar_arma();
    void soltar_arma();
    bool esta_vivo();
    bool agarrar_armadura();
    bool agarrar_casco();
    bool tiene_armadura();
    bool tiene_casco();
    bool disparar();
    void caer();

    ~Pato();
};


#endif
