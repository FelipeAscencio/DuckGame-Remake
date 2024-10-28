#ifndef THREAD_USUARIO_H
#define THREAD_USUARIO_H

#include "../common/queue.h"

#include "enviador.h"
#include "recibidor.h"

class ThreadUsuario {
private:
    Socket skt;
    Queue<EstadoJuego> queue_sender;
    std::atomic<bool> vivo;
    Recibidor r;
    Enviador e;
    int id_cliente;

public:
    explicit ThreadUsuario(Socket&& s, Queue<comando_t>& queue_comandos, int id);

    void iniciar();

    bool esta_vivo() { return this->vivo; }

    void cortar_conexion();

    Queue<EstadoJuego>& obtener_queue() { return this->queue_sender; }

    int get_id() { return this->id_cliente; }

    ~ThreadUsuario();
};

#endif
