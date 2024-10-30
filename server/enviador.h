// Copyright 2024 Axel Zielonka y Felipe Ascensio
#ifndef SERVER_ENVIADOR_H_
#define SERVER_ENVIADOR_H_

#include <atomic>

#include "../common/estado_juego.h"
#include "../common/queue.h"
#include "../common/thread.h"
#include "server/protocol.h"

using namespace ServerProtocol;

class Enviador: public Thread {
private:
    Protocol protocol;
    Queue<EstadoJuego>& queue_estados;
    std::atomic<bool>& vivo;

public:
    explicit Enviador(Socket& s, Queue<EstadoJuego>& q, std::atomic<bool>& esta_vivo);

    void run() override;

    void terminar_ejecucion() { this->vivo = false; }

    ~Enviador();
};


#endif  // SERVER_ENVIADOR_H_
