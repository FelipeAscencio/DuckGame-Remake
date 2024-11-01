// Copyright 2024 Axel Zielonka y Felipe Ascensio
#include "server/gameloop.h"

#include <algorithm>
#define SLEEP 200

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
    queues_clientes.broadcast(estado_actual);
}

void Gameloop::run() {
    while (juego_activo) {
        enviar_estado_juego();
        chequear_nuevos_jugadores();
        if (!jugadores.empty()) {
            actualizar_estado_jugadores();
            comando_t cmd;
            if (queue.try_pop(cmd)) {
                for (Pato* p: jugadores) {
                    if (cmd.id_cliente == p->id_jugador) {
                        p->realizar_accion(cmd.accion, mapa);
                    }
                }
            }
        }
        // sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
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
