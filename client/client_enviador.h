// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef CLIENT_ENVIADOR_H
#define CLIENT_ENVIADOR_H

#include <atomic>

#include "../common/queue.h"
#include "../common/thread.h"

#include "protocolo_cliente.h"

// La clase 'EnviadorCliente' se encarga de mandar los comandos que recibe
// por la 'cola_comandos' al 'Server'.
class EnviadorCliente: public Thread {
private:
    ProtocoloCliente& protocolo;
    Queue<char>& cola_comandos;
    int id_cliente;
    std::atomic<bool> vivo;

public:
    // Constructor de la clase.
    EnviadorCliente(ProtocoloCliente& protocol, Queue<char>& queue, int id);

    // Hace el 'Pop' de la cola de comandos que el controlador llena
    // y envia el contenido de la misma con el 'Protocolo'.
    void run() override;

    // Cambia el estado del bool vivo del hilo de 'true' a 'false'.
    void stop() override;

    // Deshabilito las copias.
    EnviadorCliente(const EnviadorCliente&) = delete;
    EnviadorCliente& operator=(const EnviadorCliente&) = delete;

    // Permito el movimiento del objeto.
    EnviadorCliente(EnviadorCliente&&) = default;
    EnviadorCliente& operator=(EnviadorCliente&&) = default;
};

#endif  // CLIENT_ENVIADOR_H
