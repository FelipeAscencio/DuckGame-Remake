#include "thread_usuario.h"

#include <syslog.h>
#include "../common/liberror.h"

#define RW_CLOSE 2

ThreadUsuario::ThreadUsuario(Socket&& s, Queue<comando_t>& queue_comandos, int id) : skt(std::move(s)), queue_sender(10), vivo(true), r(skt, queue_comandos), e(skt, queue_sender, vivo), id_cliente(id) {} 

void ThreadUsuario::iniciar(){
    r.start();
    e.start();
}

void ThreadUsuario::cortar_conexion() { vivo = false; }

ThreadUsuario::~ThreadUsuario(){
    r.terminar_ejecucion();
    e.terminar_ejecucion();
    queue_sender.close();
    skt.shutdown(RW_CLOSE);
    skt.close();
}