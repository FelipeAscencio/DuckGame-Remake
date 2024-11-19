#include "client_recibidor.h"

#define SEGUIR_JUGANDO 253

RecibidorCliente::RecibidorCliente(ProtocoloCliente& protocol, Queue<EstadoJuego>& queue):
        protocolo(protocol), cola_estados(queue), vivo(true) {}

void RecibidorCliente::run() {
    while (this->vivo) {
        EstadoJuego estado_actual;
        if (!protocolo.recibir(estado_actual)) {
            break;
        }

        try {
            cola_estados.try_push(estado_actual);
            if (estado_actual.id_ganador != SEGUIR_JUGANDO){
                break;
            }
        } catch (const ClosedQueue& error) {
            std::cerr << error.what() << std::endl;
        }
    }
}

void RecibidorCliente::stop() { this->vivo = false; }