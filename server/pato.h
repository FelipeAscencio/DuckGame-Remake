// Copyright 2024 Axel Zielonka y Felipe Ascensio
#ifndef SERVER_PATO_H_
#define SERVER_PATO_H_

#include <iostream>

#include "../common/estado_fisico.h"
#include "../common/orientacion.h"
#include "../common/posicion.h"
#include "server/arma.h"
#include "server/mapa.h"

class Pato {
    friend struct EstadoJuego;
    friend class Gameloop;
    friend struct InformacionPato;
    friend struct MismoID;

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

    bool chequeo_movimiento(Mapa& mapa, const orientacion_e& direccion);
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
    int obtener_id_arma() { return arma_equipada ? arma_equipada->obtener_id() : 0; }
    static bool buscar_pared(Mapa& mapa, const orientacion_e& direccion,
                             const posicion_t& posicion_a_chequear);

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


#endif  // SERVER_PATO_H_
