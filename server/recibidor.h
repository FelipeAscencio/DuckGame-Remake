#ifndef RECIBIDOR_H
#define RECIBIDOR_H

#include <atomic>

#include "../common/queue.h"
#include "../common/thread.h"

#include "protocol.h"

using namespace ServerProtocol;

class Recibidor: public Thread {
private:
    Protocol protocol;
    Queue<comando_t>& queue_comandos;
    std::atomic<bool> vivo;

public:
    explicit Recibidor(Socket& s, Queue<comando_t>& q);

    virtual void run() override;

    void terminar_ejecucion() { this->vivo = false; }

    ~Recibidor();
};

#endif
