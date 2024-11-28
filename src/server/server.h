// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <iostream>
#include <vector>

#include "../common/comando.h"
#include "../common/queue.h"
#include "server/aceptador.h"
#include "server/gameloop.h"
#include "server/queues_jugadores.h"

// La clase 'Server' implementa la logica del
// control de los hilos del mismo.
class Server {
private:
    Queue<comando_t> queue_juego;
    ListaQueues lista_queues;
    Aceptador a;
    Gameloop g;

    // Inicia el proceso para aceptar conexiones de jugadores.
    void comenzar_a_aceptar();

    // Inicia el ciclo principal del juego.
    void comenzar_juego();

public:
    // Constructor de la clase.
    explicit Server(const char* servname);

    // Inicia el servidor, configurando aceptacion de jugadores, el juego, y entrada de comandos.
    void start();

    // Deshabilito las copias.
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    // Permito el movimiento del objeto.
    Server(Server&&) = default;
    Server& operator=(Server&&) = default;

    ~Server();
};

#endif  // SERVER_SERVER_H_
