#include "server.h"
#include <time.h>
#include <string>

#define EXIT 'q'


Server::Server(const char* servname):
        a(servname, partidas_en_juego),c() {}

void Server::comenzar_a_aceptar() { a.start(); }

void Server::start() {
    comenzar_a_aceptar();
    c.start();
    while (c.esta_vivo()){
        for (size_t i = 0; i < partidas_en_juego.size(); i++){
            partidas_en_juego[i]->buscar_jugadores_desconectados();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    c.join();
    for (size_t i = 0; i < partidas_en_juego.size(); i++){
        partidas_en_juego[i]->terminar_partida();
    }
    a.dejar_de_aceptar();
}

Server::~Server(){
    for (size_t i = 0; i < partidas_en_juego.size(); i++){
        delete partidas_en_juego[i];
    }
    partidas_en_juego.clear();
    a.join();
}


