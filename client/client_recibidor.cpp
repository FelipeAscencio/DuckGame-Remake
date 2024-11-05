#include "client_recibidor.h"

RecibidorCliente::RecibidorCliente(ProtocoloCliente& protocol, Queue<EstadoJuego>& queue):
            protocolo(protocol), cola_estados(queue), vivo(true) {}

void RecibidorCliente::run(){
    while (this->vivo) {
        EstadoJuego estado_actual;
        if (!protocolo.recibir(estado_actual)){
            break;
        }
        
        try {
            cola_estados.push(estado_actual);
        } catch (const ClosedQueue& error) {
            std::cerr << error.what() << std::endl;
        }
    }
}

void RecibidorCliente::stop(){
    this->vivo = false;
}