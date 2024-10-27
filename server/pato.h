#ifndef PATO_H
#define PATO_H

#include <iostream>

#include "arma.h"
#include "estado_fisico.h"
#include "gameloop.h"
#include "mapa.h"
#include "orientacion.h"
#include "posicion.h"
#include "protocol.h"

using namespace ServerProtocol;
class Pato {
    friend Protocol;  // para poder enviar la informacion del pato sin usar getters
    friend estado_juego_t;
    friend Gameloop;

private:
    int id_jugador;
    posicion_t posicion;
    bool vivo;
    bool posee_arma;
    bool posee_armadura;
    bool posee_casco;
    orientacion_e orientacion;
    Arma* arma_equipada;
    estado_pato_e estado_actual;
    int iteraciones_subiendo;

    bool chequeo_bordes(Mapa& mapa, const orientacion_e& direccion);
    void chequear_estado();
    bool mover(Mapa& mapa, const orientacion_e& direccion);
    void saltar();
    void aletear();
    bool tiene_arma();
    void agacharse();
    void cambiar_orientacion(orientacion_e nueva_orientacion);
    bool agarrar_arma(Arma* arma);
    void soltar_arma();
    bool esta_vivo();
    bool agarrar_armadura();
    bool agarrar_casco();
    void caer(Mapa& mapa);
    void recibir_disparo();
    bool disparar();

public:
    explicit Pato(int id);
    posicion_t obtener_posicion();
    orientacion_e obtener_orientacion();
    bool tiene_armadura();
    bool tiene_casco();
    void control_pre_comando(Mapa& mapa);
    void realizar_accion(int accion, Mapa& mapa);
    ~Pato();
};


#endif
