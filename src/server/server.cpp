#include "server.h"

#include <string>

#define EXIT 'q'

Server::Server(const char* servname):
        queue_juego(CANTIDAD_MAXIMA_ACCIONES),
        lista_queues(),
        a(servname, queue_juego, lista_queues),
        g(queue_juego, lista_queues) {}

void Server::comenzar_a_aceptar() { a.start(); }

void Server::comenzar_juego() { g.start(); }

void Server::start() {
    comenzar_a_aceptar();
    comenzar_juego();
    std::string leido;
    while (std::getline(std::cin, leido)){
        if (leido[0] == EXIT){
            g.finalizar_juego();
            a.dejar_de_aceptar();
            break;
        }
    }
}

Server::~Server(){
    g.join();
    a.join();
}


