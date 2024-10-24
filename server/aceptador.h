#ifndef ACEPTADOR_H
#define ACEPTADOR_H

#include <atomic>
#include <list>

#include "../common/queue.h"
#include "../common/thread.h"

#include "thread_usuario.h"

class Aceptador: public Thread {
private:
    Socket skt;
    std::list<ThreadUsuario> jugadores;
    std::atomic<bool> aceptando_jugadores;
    Queue<comando_t> queue_juego;


    void recolectar();
    void eliminar_cliente();

public:
    explicit Aceptador(const char* servname, Queue<comando_t>& q);

    virtual void run();

    void dejar_de_aceptar();

    virtual ~Aceptador();
};

#endif
