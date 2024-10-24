#ifndef ENVIADOR_H
#define ENVIADOR_H

#include <atomic>

#include "protocol.h"
#include "../common/queue.h"
#include "../common/thread.h"

using namespace ServerProtocol;

typedef struct EstadoJuego {
    int a; // aca tengo que ver bien que es lo que se envia
} estado_juego_t;

class Enviador : public Thread {
    private:
        Protocol protocol;
        Queue<estado_juego_t>& queue_snapshots;
        std::atomic<bool> vivo;

    public:
        explicit Enviador(Socket& s, Queue<estado_juego_t>& q, std::atomic<bool>& esta_vivo);

        virtual void run() override;

        void terminar_ejecucion() { this->vivo = false; }

        ~Enviador();
};


#endif
