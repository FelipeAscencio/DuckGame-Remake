// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SERVER_RECIBIDOR_H_
#define SERVER_RECIBIDOR_H_

#include <atomic>

#include "../common/queue.h"
#include "../common/thread.h"
#include "server/protocol.h"

using namespace ServerProtocol;

// La clase 'Recibidor' se encarga de recibir los
// comandos de los 'Clientes'.
class Recibidor: public Thread {
private:
    Protocol protocol;
    Queue<comando_t>& queue_comandos;
    std::atomic<bool> vivo;
    const int id_cliente;

public:
    // Constructor de la clase.
    explicit Recibidor(Socket& s, Queue<comando_t>& q, const int& id_clientes);

    // Ejecuta el hilo del recibidor, procesando comandos hasta que el objeto esta marcado como
    // vivo.
    void run() override;

    // Termina la ejecucion del hilo y para de recibir comandos del cliente.
    void terminar_ejecucion() { this->vivo = false; }

    // Destructor de la clase.
    ~Recibidor();

    // Deshabilito las copias.
    Recibidor(const Recibidor&) = delete;
    Recibidor& operator=(const Recibidor&) = delete;

    // Permito el movimiento del objeto.
    Recibidor(Recibidor&&) = default;
    Recibidor& operator=(Recibidor&&) = default;
};

#endif  // SERVER_RECIBIDOR_H_
