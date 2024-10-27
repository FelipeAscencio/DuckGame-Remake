#include "server.h"

Server::Server(const char* servname):
        queue_juego(CANTIDAD_MAXIMA_ACCIONES),
        lista_queues(),
        a(servname, queue_juego, lista_queues, ids_clientes),
        g(queue_juego, lista_queues) {}

void Server::comenzar_a_aceptar() { a.start(); }

void Server::comenzar_juego() { g.start(); }

void Server::agregar_nuevos_jugadores() {
    while (true) {
        for (int id: ids_clientes) {
            g.intentar_agregar_jugador(id);
        }
        if (!g.jugando())
            break;
    }
}

void Server::start() {
    comenzar_a_aceptar();
    comenzar_juego();
    agregar_nuevos_jugadores();
}

Server::~Server() {
    g.finalizar_juego();
    a.dejar_de_aceptar();
}
