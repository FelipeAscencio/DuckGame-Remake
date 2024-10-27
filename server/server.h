#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <vector>
#include "comando.h"
#include "../common/queue.h"
#include "queues_jugadores.h"
#include "aceptador.h"
#include "gameloop.h"


class Server {
    private: 
        Queue<comando_t> queue_juego;
        ListaQueues lista_queues;
        std::vector<int> ids_clientes;
        Aceptador a;
        Gameloop g;

        void comenzar_a_aceptar();

        void comenzar_juego();

        void agregar_nuevos_jugadores();

    public:
        explicit Server(const char* servname);

        void start();

        ~Server();

};

#endif 

