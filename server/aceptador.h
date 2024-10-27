#ifndef ACEPTADOR_H
#define ACEPTADOR_H

#include <atomic>
#include <list>

#include "../common/queue.h"
#include "../common/thread.h"

#include "queues_jugadores.h"
#include "thread_usuario.h"

class Aceptador: public Thread {
private:
    Socket skt;
    std::list<ThreadUsuario*> jugadores;
    std::atomic<bool> aceptando_jugadores;
    Queue<comando_t>& queue_juego;
    ListaQueues& queues_clientes;
    std::vector<int>& ids_clientes;

    void recolectar();
    void eliminar_cliente(ThreadUsuario* jugador);

public:
    explicit Aceptador(const char* servname, Queue<comando_t>& q, ListaQueues& l,
                       std::vector<int>& ids_clientes);

    virtual void run();

    void dejar_de_aceptar() { this->aceptando_jugadores = false; };

    virtual ~Aceptador();
};

#endif
