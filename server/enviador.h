#ifndef ENVIADOR_H
#define ENVIADOR_H

#include <atomic>

#include "../common/queue.h"
#include "../common/thread.h"

#include "../common/estado_juego.h"
#include "protocol.h"

using namespace ServerProtocol;

class Enviador: public Thread {
private:
    Protocol protocol;
    Queue<estado_juego_t>& queue_estados;
    std::atomic<bool>& vivo;

public:
    explicit Enviador(Socket& s, Queue<estado_juego_t>& q, std::atomic<bool>& esta_vivo);

    virtual void run() override;

    void terminar_ejecucion() { this->vivo = false; }

    ~Enviador();
};


#endif
