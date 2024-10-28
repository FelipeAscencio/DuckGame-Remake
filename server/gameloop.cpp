#include "gameloop.h"

Gameloop::Gameloop(Queue<comando_t>& q, ListaQueues& l):
        queue(q), juego_activo(true), queues_clientes(l), mapa(20, 16) {}

void Gameloop::intentar_agregar_jugador(int id) {
    bool id_existente = false;
    for (Pato* p: jugadores) {
        if (p->id_jugador == id) {
            id_existente = true;
            break;
        }
    }
    if (!id_existente)
        jugadores.push_back(new Pato(id));
}

void Gameloop::actualizar_estado_jugadores() {
    for (Pato* p: jugadores) {
        p->control_pre_comando(this->mapa);
    }
}

void Gameloop::enviar_estado_juego() {
    EstadoJuego estado_actual(jugadores.size());
    for (size_t indice = 0; indice < jugadores.size(); indice++) {
        estado_actual.agregar_info_pato(*jugadores[indice], indice);
    }
    queues_clientes.broadcast(estado_actual);
}

void Gameloop::run() {
    while (juego_activo) {
        if (!jugadores.empty()) {
            comando_t cmd;
            if (queue.try_pop(cmd)) {
                for (Pato* p: jugadores) {
                    if (cmd.id_cliente == p->id_jugador) {
                        p->realizar_accion(cmd.accion, mapa);
                    }
                }
            }
            actualizar_estado_jugadores();
        }
        // sleep
    }
}

Gameloop::~Gameloop() {
    for (Pato* p: jugadores) {
        delete p;
    }
    jugadores.clear();
}