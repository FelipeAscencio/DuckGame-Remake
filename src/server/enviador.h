// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SERVER_ENVIADOR_H_
#define SERVER_ENVIADOR_H_

#include <atomic>

#include "../common/estado_juego.h"
#include "../common/queue.h"
#include "../common/thread.h"
#include "server/protocol.h"

using namespace ServerProtocol;

// La clase 'Enviador' se encarga de enviar los
// estados del juego a los 'Clientes'.
class Enviador: public Thread {
private:
    Protocol protocol;
    Queue<EstadoJuego>& queue_estados;
    std::atomic<bool>& vivo;

public:
    // Constructor de la clase.
    explicit Enviador(Socket& s, Queue<EstadoJuego>& q, std::atomic<bool>& esta_vivo);

    // Ejecuta el ciclo de envio de estados de juego a los clientes.
    void run() override;

    // Termina la ejecucion del hilo y para de enviar estados del juego.
    void terminar_ejecucion() { this->vivo = false; }

    // Destructor de la clase.
    ~Enviador();

    // Deshabilito las copias.
    Enviador(const Enviador&) = delete;
    Enviador& operator=(const Enviador&) = delete;

    // Permito el movimiento del objeto.
    Enviador(Enviador&&) = default;
    Enviador& operator=(Enviador&&) = default;
};

#endif  // SERVER_ENVIADOR_H_
