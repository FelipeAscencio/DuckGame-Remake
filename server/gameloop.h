#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <atomic>
#include <vector>

#include "../common/queue.h"
#include "../common/thread.h"

#include "../common/comando.h"
#include "../common/estado_juego.h"
#include "mapa.h"
#include "pato.h"
#include "queues_jugadores.h"

class Gameloop: public Thread {
private:
    Queue<comando_t>& queue;
    std::atomic<bool> juego_activo;
    ListaQueues& queues_clientes;
    std::vector<Pato*> jugadores;
    Mapa mapa;

    void actualizar_estado_jugadores();

    void enviar_estado_juego();

public:
    explicit Gameloop(Queue<comando_t>& q, ListaQueues& l);

    virtual void run() override;

    void intentar_agregar_jugador(int id);

    void finalizar_juego() { this->juego_activo = false; }

    bool jugando() { return juego_activo; }

    ~Gameloop();
};

#endif
