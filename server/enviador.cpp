#include "enviador.h"

#include <syslog.h>

#include "../common/liberror.h"

Enviador::Enviador(Socket& s, Queue<estado_juego_t>& q, std::atomic<bool>& esta_vivo):
        protocol(s), queue_estados(q), vivo(esta_vivo) {}

void Enviador::run() {
    while (vivo) {
        try {
            estado_juego_t estado_actual = queue_estados.pop();
            if (!protocol.enviar(estado_actual)) {
                break;
            }
        } catch (const ClosedQueue& e) {
            syslog(LOG_INFO, "%s\n", e.what());
            break;
        }
    }
}

Enviador::~Enviador() { this->join(); }