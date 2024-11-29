#include "queues_jugadores.h"

ListaQueues::ListaQueues() {}

void ListaQueues::broadcast(const EstadoJuego& estado_actual) {
    std::lock_guard<std::mutex> lck(mtx);
    if (lista_queues.empty())
        return;

    for (auto& p: lista_queues) {
        Queue<EstadoJuego>& q = p.first;
        try {
            q.try_push(estado_actual);
        } catch (const ClosedQueue& e) {
            syslog(LOG_INFO, "%s\n", e.what());
        }
    }
}

void ListaQueues::agregar_queue(Queue<EstadoJuego>& q, int id_cliente) {
    std::lock_guard<std::mutex> lck(mtx);
    lista_queues.push_back(std::make_pair(std::ref(q), id_cliente));
}

bool ListaQueues::encontrar_cliente(const int& id) {
    auto i = lista_queues.begin();
    bool cliente_encontrado = false;
    while (i != lista_queues.end() && !cliente_encontrado) {
        if (i->second == id)
            cliente_encontrado = true;
        i++;
    }

    return cliente_encontrado;
}

void ListaQueues::eliminar_queue(int id) {
    std::lock_guard<std::mutex> lck(mtx);
    auto i = lista_queues.begin();
    bool borrado = false;
    while (i != lista_queues.end() && !borrado) {
        int id_actual = i->second;
        if (id_actual == id) {
            i = lista_queues.erase(i);
            borrado = true;
        } else {
            i++;
        }
    }
}
