#include "aceptador.h"

#include <syslog.h>

#include "../common/liberror.h"

#define EXCEPCION_ESPERADA "Se produjo una excepcion esperada: "
#define EXCEPCION_INESPERADA "Se produjo una excepcion inesperada: "
#define EXCEPCION_DESCONOCIDA "Se produjo una excepcion desconocida. "
#define RW_CLOSE 2

Aceptador::Aceptador(const char* servname, Queue<comando_t>& q, ListaQueues& l,
                     std::vector<int>& ids_jugadores):
        skt(servname),
        aceptando_jugadores(true),
        queue_juego(q),
        queues_clientes(l),
        ids_clientes(ids_jugadores) {}

void Aceptador::run() {
    int id = 0;
    while (aceptando_jugadores) {
        try {
            Socket peer = skt.accept();
            ThreadUsuario* jugador = new ThreadUsuario(std::move(peer), queue_juego, id);
            ids_clientes.push_back(id);
            queues_clientes.agregar_queue(jugador->obtener_queue(), id);
            jugadores.push_back(jugador);
            jugador->iniciar();
            id++;
            recolectar();
        } catch (const LibError& e) {
            if (!aceptando_jugadores) {
                syslog(LOG_INFO, "%s%s. No hay clientes esperando a ser aceptados\n",
                       EXCEPCION_ESPERADA, e.what());
            } else {
                syslog(LOG_ERR, "%s%s\n", EXCEPCION_INESPERADA, e.what());
            }
            break;
        } catch (...) {
            syslog(LOG_ERR, "%s\n", EXCEPCION_DESCONOCIDA);
            break;
        }
    }
}

void Aceptador::eliminar_cliente(ThreadUsuario* jugador) {
    jugador->cortar_conexion();
    int id = jugador->get_id();
    queues_clientes.eliminar_queue(id);
    delete jugador;
}

void Aceptador::recolectar() {
    jugadores.remove_if([this](ThreadUsuario* j) {
        if (!(j->esta_vivo())) {
            eliminar_cliente(j);
            return true;
        }
        return false;
    });
}

Aceptador::~Aceptador() {
    for (auto& j: jugadores) {
        eliminar_cliente(j);
    }
    jugadores.clear();
    queue_juego.close();
    skt.shutdown(RW_CLOSE);
    skt.close();
    this->join();
}