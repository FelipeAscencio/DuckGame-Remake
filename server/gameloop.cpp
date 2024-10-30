// Copyright 2024 Axel Zielonka y Felipe Ascensio
#include "server/gameloop.h"

#include <algorithm>
#define SLEEP 200

Gameloop::Gameloop(Queue<comando_t>& q, ListaQueues& l):
        queue(q), juego_activo(true), queues_clientes(l), mapa(20, 16) {}

void Gameloop::intentar_agregar_jugador(int id) {
    if (std::none_of(jugadores.cbegin(), jugadores.cend(), MismoID(id)))
        jugadores.push_back(Pato(id));
}

void Gameloop::actualizar_estado_jugadores() {
    for (Pato p: jugadores) {
        p.control_pre_comando(this->mapa);
    }
}

void Gameloop::enviar_estado_juego() {
    EstadoJuego estado_actual;
    if (jugadores.empty()) {

    } else {
        for (Pato p: jugadores) {
            estado_actual.agregar_info_pato(p);
        }
    }
    queues_clientes.broadcast(estado_actual);
}

void Gameloop::run() {
    enviar_estado_juego();  // primer envio del estado del juego para inicializar todo
    while (juego_activo) {
        if (!jugadores.empty()) {
            actualizar_estado_jugadores();
            comando_t cmd;
            if (queue.try_pop(cmd)) {
                for (Pato p: jugadores) {
                    if (cmd.id_cliente == p.id_jugador) {
                        p.realizar_accion(cmd.accion, mapa);
                    }
                }
            }
            enviar_estado_juego();
        }
        // sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
    }
}

Gameloop::~Gameloop() { jugadores.clear(); }
