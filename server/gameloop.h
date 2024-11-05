// Copyright 2024 Axel Zielonka y Felipe Ascensio
#ifndef SERVER_GAMELOOP_H_
#define SERVER_GAMELOOP_H_

#include <atomic>
#include <vector>

#include "../common/comando.h"
#include "../common/estado_juego.h"
#include "../common/queue.h"
#include "../common/thread.h"
#include "server/mapa.h"
#include "server/pato.h"
#include "server/queues_jugadores.h"
#include "server/arma.h"

class Gameloop: public Thread {
private:
    Queue<comando_t>& queue;
    std::atomic<bool> juego_activo;
    ListaQueues& queues_clientes;
    std::vector<Pato*> jugadores;
    std::vector<Arma*> armas_tiradas;
    Mapa mapa;

    void chequear_posiciones();

    void actualizar_estado_jugadores();

    void actualizar_balas_disparadas();

    void enviar_estado_juego();

    void chequear_nuevos_jugadores();

    void loop_juego();

public:
    explicit Gameloop(Queue<comando_t>& q, ListaQueues& l);

    virtual void run() override;

    void finalizar_juego() { this->juego_activo = false; }

    bool jugando() { return juego_activo; }

    ~Gameloop();
};

#endif  // SERVER_GAMELOOP_H_
