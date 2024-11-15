
// Copyright 2024 Axel Zielonka y Felipe Ascensio
#include "server/gameloop.h"

#include <algorithm>

#include <time.h>

#define FPS 30
#define CERO 0
#define UNO 1
#define CIEN 100
#define MIL 1000

Gameloop::Gameloop(Queue<comando_t>& q, ListaQueues& l):
        queue(q), juego_activo(true), queues_clientes(l), mapa(1) {}

void Gameloop::chequear_nuevos_jugadores() {
    size_t cantidad_jugadores = jugadores.size();
    size_t cantidad_queues = queues_clientes.get_size();
    if (cantidad_jugadores == cantidad_queues)
        return;
    if (cantidad_jugadores < cantidad_queues) {
        for (size_t i = cantidad_jugadores; i < cantidad_queues; i++) {
            jugadores.push_back(new Pato(i));
        }
    }
}

void Gameloop::actualizar_estado_jugadores() {
    for (Pato* p: jugadores) {
        p->control_pre_comando(this->mapa);
    }
}

void Gameloop::enviar_estado_juego() {
    EstadoJuego estado_actual;
    if (jugadores.empty()) {

    } else {
        for (Pato* p: jugadores) {
            if (p->vivo)
                estado_actual.agregar_info_pato(p);
        }
    }
    if (!this->armas_tiradas.empty()) {
        for (Arma* a: armas_tiradas) {
            estado_actual.agregar_arma(a);
        }
    }
    queues_clientes.broadcast(estado_actual);
}

void Gameloop::actualizar_balas_disparadas() {
    for (Pato* p: jugadores) {
        if (p->arma_equipada) {
            p->arma_equipada->chequeo_balas(mapa);
        }
    }
}

void Gameloop::chequear_posiciones() {
    for (Pato* p: jugadores) {
        for (Pato* o: jugadores) {
            if (p->id_jugador != o->id_jugador) {
                if (p->arma_equipada && !p->arma_equipada->balas.empty()) {
                    for (Municion* m: p->arma_equipada->balas) {
                        if (o->posicion.misma_posicion(m->posicion_actual)) {
                            o->recibir_disparo();
                        }
                    }
                }
            }
        }
    }
}

void Gameloop::loop_juego() {
    chequear_nuevos_jugadores();
    if (!jugadores.empty()) {
        chequear_posiciones();
        actualizar_estado_jugadores();
        actualizar_balas_disparadas();
        comando_t cmd;
        if (queue.try_pop(cmd)) {
            for (Pato* p: jugadores) {
                if (cmd.id_cliente == p->id_jugador) {
                    p->realizar_accion(cmd.accion, mapa);
                }
            }
        }
    }
    enviar_estado_juego();
}

void Gameloop::run() {
    enviar_estado_juego();
    auto t1 = std::chrono::steady_clock::now();
    unsigned long frame_count = 0;

    // Definir el intervalo de tiempo ideal para cada frame en milisegundos
    int ms_per_frame = 1000 / FPS;

    while (juego_activo) {
        loop_juego();

        // Calcular el tiempo transcurrido desde el inicio de este frame
        auto t2 = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        // Dormir el tiempo restante para completar el intervalo de 30 FPS
        if (elapsed < ms_per_frame) {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms_per_frame - elapsed));
        }

        // Actualizar `t1` sumando un intervalo fijo para mantener la consistencia en el tiempo de
        // frames
        t1 += std::chrono::milliseconds(ms_per_frame);
        frame_count++;
    }
}

Gameloop::~Gameloop() {
    for (size_t i = 0; i < jugadores.size(); i++) {
        if (jugadores[i]) {
            delete jugadores[i];
        }
    }
    jugadores.clear();
    this->join();
}