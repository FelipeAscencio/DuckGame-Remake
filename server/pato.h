#ifndef PATO_H
#define PATO_H

#include <iostream>

#include "arma.h"
#include "mapa.h"
#include "orientacion.h"
#include "posicion.h"
#include "protocol.h"

using namespace ServerProtocol;
class Pato {
    friend Protocol;  // para poder enviar la informacion del pato sin usar getters
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
    bool saltando;
    bool aleteando;
    bool cayendo;
    int iteraciones_subiendo;

    bool chequeo_bordes(Mapa mapa, const orientacion_e& direccion);

public:
    explicit Pato(int id);
    posicion_t obtener_posicion();
    bool mover(Mapa mapa, const orientacion_e& direccion);
    void saltar(Mapa mapa);
    void aletear();
    bool tiene_arma();
    void agacharse();
    orientacion_e obtener_orientacion();
    void cambiar_orientacion(orientacion_e nueva_orientacion);
    bool agarrar_arma(Arma* arma);
    void soltar_arma();
    bool esta_vivo();
    bool agarrar_armadura();
    bool agarrar_casco();
    bool tiene_armadura();
    bool tiene_casco();
    bool disparar();
    void caer(Mapa mapa);
    void control_pre_comando(Mapa mapa);
    void recibir_disparo();

    ~Pato();
};


#endif
