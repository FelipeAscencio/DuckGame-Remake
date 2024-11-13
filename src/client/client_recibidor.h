// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef CLIENT_RECIBIDOR_H
#define CLIENT_RECIBIDOR_H

#include <atomic>

#include "../common/estado_juego.h"
#include "../common/queue.h"
#include "../common/thread.h"

#include "protocolo_cliente.h"

// La clase 'RecibidorCliente' se encarga de mandar los estados que recibe
// desde el 'Server' a la cola de estados del 'Cliente'.
class RecibidorCliente: public Thread {
private:
    ProtocoloCliente& protocolo;
    Queue<EstadoJuego>& cola_estados;
    std::atomic<bool> vivo;

public:
    // Constructor de la clase.
    explicit RecibidorCliente(ProtocoloCliente& p, Queue<EstadoJuego>& q);

    // Recibe los estados del juego desde el 'Protocolo' y los agrega
    // a la cola de estados del 'Cliente'.
    void run() override;

    // Cambia el estado del bool vivo del hilo de 'true' a 'false'.
    void stop() override;

    // Deshabilito las copias.
    RecibidorCliente(const RecibidorCliente&) = delete;
    RecibidorCliente& operator=(const RecibidorCliente&) = delete;

    // Permito el movimiento del objeto.
    RecibidorCliente(RecibidorCliente&&) = default;
    RecibidorCliente& operator=(RecibidorCliente&&) = default;
};

#endif  // CLIENT_RECIBIDOR_H
