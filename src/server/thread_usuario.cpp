#include "server/thread_usuario.h"

#include <utility>

#include <syslog.h>

#include "../common/liberror.h"

#define RW_CLOSE 2

ThreadUsuario::ThreadUsuario(Socket&& s, Queue<comando_t>& queue_comandos, int id):
        skt(std::move(s)),
        queue_sender(CANTIDAD_MAXIMA_ACCIONES),
        vivo(true),
        r(skt, queue_comandos, vivo, id),
        e(skt, queue_sender, vivo),
        id_cliente(id) {}

void ThreadUsuario::iniciar() {
    r.start();
    e.start();
}

void ThreadUsuario::cortar_conexion() { vivo = false; }

ThreadUsuario::~ThreadUsuario() {
    e.terminar_ejecucion();
    r.terminar_ejecucion();
    queue_sender.close();
    try {
        skt.shutdown(RW_CLOSE);
        skt.close();
    } catch (const LibError& e){}
}
