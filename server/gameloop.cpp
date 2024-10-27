#include "gameloop.h"

Gameloop::Gameloop(Queue<comando_t>& q, ListaQueues& l, std::vector<int> ids_clientes):
        queue(q), juego_activo(true), queues_clientes(l), mapa(25, 15) {
    for (int i = 0; i < ids_clientes.size(); i++) {
        jugadores.push_back(new Pato(ids_clientes[i]));
    }
}

void Gameloop::actualizar_estado_jugadores() {
    for (Pato* p: jugadores) {
        p->control_pre_comando(this->mapa);
    }
}

void Gameloop::enviar_estado_juego() {
    estado_juego_t estado_actual(jugadores.size());
    for (int indice = 0; indice < jugadores.size(); indice++) {
        estado_actual.agregar_info_pato(*jugadores[indice], indice);
    }
    queues_clientes.broadcast(estado_actual);
}

void Gameloop::run() {
    while (juego_activo) {
        comando_t cmd;
        while (queue.try_pop(cmd)) {
            for (Pato* p: jugadores) {
                if (cmd.id_cliente == p->id_jugador) {
                    p->realizar_accion(cmd.accion, mapa);
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