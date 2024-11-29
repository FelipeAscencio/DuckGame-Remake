// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef THREAD_USUARIO_H
#define THREAD_USUARIO_H

#include <utility>
#include <syslog.h>

#include "../common/liberror.h"
#include "../common/queue.h"
#include "enviador.h"
#include "recibidor.h"

// La clase 'ThreadUsuario' se encarga de manejar los
// hilos de comunicacion del 'Cliente' en el 'Server'.
class ThreadUsuario {
private:
    Socket skt;
    Queue<EstadoJuego> queue_sender;
    std::atomic<bool> vivo;
    Recibidor r;
    Enviador e;
    int id_cliente;

public:
    // Constructor de la clase.
    explicit ThreadUsuario(Socket&& s, Queue<comando_t>& queue_comandos, int id);

    // Inicia los hilos de recepcion y envio de comandos del usuario.
    void iniciar();

    // Devuelve el estado del hilo.
    bool esta_vivo() { return r.vivo; }

    // Marca el hilo como no vivo, indicando que debe cortar la conexion.
    void cortar_conexion();

    // Devuelve la cola de estados del juego del 'Cliente'.
    Queue<EstadoJuego>& obtener_queue() { return this->queue_sender; }

    // Devuelve el id del 'Cliente'.
    int get_id() { return this->id_cliente; }

    // Destructor de la clase.
    ~ThreadUsuario();

    // Deshabilito las copias.
    ThreadUsuario(const ThreadUsuario&) = delete;
    ThreadUsuario& operator=(const ThreadUsuario&) = delete;

    // Permito el movimiento del objeto.
    ThreadUsuario(ThreadUsuario&&) = default;
    ThreadUsuario& operator=(ThreadUsuario&&) = default;
};

#endif  // THREAD_USUARIO_H
