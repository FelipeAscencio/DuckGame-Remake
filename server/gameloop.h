#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <atomic>
#include <list>

#include "../common/queue.h"
#include "../common/thread.h"

#include "comando.h"
#include "estado_juego.h"
#include "pato.h"
#include "queues_jugadores.h"

class Gameloop: public Thread {
private:
    Queue<comando_t>& queue;
    std::atomic<bool> juego_activo;
    ListaQueues& queues_clientes;
    std::list<Pato> jugadores;

    void actualizar_estado_jugadores();

    void enviar_estado_juego(estado_juego_t& estado_actual);

public:
    explicit Gameloop(Queue<comando_t>& q, ListaQueues& l);

    virtual void run() override;

    void finalizar_juego() { this->juego_activo = false; }

    ~Gameloop();
};

#endif
