// Copyright 2024 Axel Zielonka y Felipe Ascensio
#ifndef SERVER_RECIBIDOR_H_
#define SERVER_RECIBIDOR_H_

#include <atomic>

#include "../common/queue.h"
#include "../common/thread.h"
#include "server/protocol.h"

using namespace ServerProtocol;

class Recibidor: public Thread {
private:
    Protocol protocol;
    Queue<comando_t>& queue_comandos;
    std::atomic<bool> vivo;
    const int id_cliente;

public:
    explicit Recibidor(Socket& s, Queue<comando_t>& q, const int& id_clientes);

    void run() override;

    void terminar_ejecucion() { this->vivo = false; }

    ~Recibidor();
};

#endif  // SERVER_RECIBIDOR_H_
