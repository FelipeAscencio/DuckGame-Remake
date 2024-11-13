// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SERVER_PATO_H_
#define SERVER_PATO_H_

#include <iostream>

#include "../common/estado_fisico.h"
#include "../common/orientacion.h"
#include "../common/posicion.h"
#include "server/arma.h"
#include "server/mapa.h"

// La clase 'Pato' implementa toda la logica del
// pato en el transcurso del juego.
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
    int iteraciones_agachado;
    int iteraciones_desde_aleteo;

    // Verifica si el pato puede moverse en la direccion especificada.
    bool chequeo_movimiento(Mapa& mapa, const orientacion_e& direccion);

    // Verifica y actualiza el estado del pato segun su estado actual.
    void chequear_estado(Mapa& mapa);

    // Mueve al pato en la direccion especificada, considerando colisiones y limites del mapa.
    bool mover(Mapa& mapa, const orientacion_e& direccion);

    // Hace que el pato salte, cambiando su estado y posicion.
    void saltar();

    // Hace que el pato aletee si esta cayendo.
    void aletear();

    // Devuelve true si el pato tiene un arma equipada.
    bool tiene_arma();

    // Hace que el pato se agache.
    void agacharse();

    // Cambia la orientacion del pato a la nueva direccion especificada.
    void cambiar_orientacion(orientacion_e nueva_orientacion);

    // El pato agarra un arma, actualizando su estado y la referencia al arma.
    bool agarrar_arma(Arma* arma);

    // El pato suelta el arma equipada.
    void soltar_arma();

    // Devuelve true si el pato esta vivo.
    bool esta_vivo();

    // El pato agarra armadura, actualizando su estado.
    bool agarrar_armadura();

    // El pato agarra un casco, actualizando su estado.
    bool agarrar_casco();

    // Actualiza la posicion del pato al caer, considerando el mapa.
    void caer(Mapa& mapa);

    // Hace que el pato reciba un disparo, afectando su estado.
    void recibir_disparo();

    // Hace que el pato dispare su arma equipada, si tiene una.
    bool disparar(Mapa& mapa);
    int obtener_id_arma() { return arma_equipada ? arma_equipada->obtener_id() : 0; }

    // Verifica si hay una pared en la direccion especificada desde la posicion dada.
    static bool buscar_pared(Mapa& mapa, const orientacion_e& direccion,
                             const posicion_t& posicion_a_chequear);

public:
    // Constructor de la clase.
    explicit Pato(int id);

    // Devuelve la posicion actual del pato.
    posicion_t obtener_posicion();

    // Devuelve la orientacion actual del pato.
    orientacion_e obtener_orientacion();

    // Devuelve true si el pato tiene armadura equipada.
    bool tiene_armadura();

    // Devuelve true si el pato tiene casco equipado.
    bool tiene_casco();

    // Controla la logica previa a la ejecucion de comandos.
    void control_pre_comando(Mapa& mapa);

    // Realiza una accion segun el comando recibido.
    void realizar_accion(int accion, Mapa& mapa);

    // Destructor de la clase.
    ~Pato();
};

#endif  // SERVER_PATO_H_