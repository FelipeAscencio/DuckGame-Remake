#include "client_enviador.h"

#define COMANDO_EXIT 'X'

EnviadorCliente::EnviadorCliente(ProtocoloCliente& protocol, Queue<char>& queue, int id):
        protocolo(protocol), cola_comandos(queue), id_cliente(id), vivo(true) {}

void EnviadorCliente::run() {
    while (this->vivo) {
        char accion;
        try {
            accion = cola_comandos.pop();
            if (accion == COMANDO_EXIT) {
                this->vivo = false;
                break;
            } else if (!protocolo.enviar(accion))
                break;
        } catch (const ClosedQueue& error) {
            std::cerr << error.what() << std::endl;
        }
    }
}

void EnviadorCliente::stop() { this->vivo = false; }
