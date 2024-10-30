// Copyright 2024 Axel Zielonka y Felipe Ascensio
#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <iostream>
#include <vector>

#include "../common/comando.h"
#include "../common/queue.h"
#include "server/aceptador.h"
#include "server/gameloop.h"
#include "server/queues_jugadores.h"

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

#endif  // SERVER_SERVER_H_
