#include "queues_jugadores.h"
#include <syslog.h>

ListaQueues::ListaQueues() {}

void ListaQueues::broadcast(const estado_juego_t& estado_actual){
    std::lock_guard<std::mutex> lck(mtx);

    if (lista_queues.empty()) 
        return;

    for (auto& p : lista_queues){
        Queue<estado_juego_t>& q = p.first;
        try {
            q.try_push(estado_actual);
        } catch (const ClosedQueue& e){
            syslog(LOG_INFO, "%s\n", e.what());
        }
    }
}

void ListaQueues::agregar_queue(Queue<estado_juego_t>& q, int id_cliente){
    std::lock_guard<std::mutex> lck(mtx);
    lista_queues.push_back(std::make_pair(std::ref(q), id_cliente));
}

void ListaQueues::eliminar_queue(int id){
    std::lock_guard<std::mutex> lck(mtx);
    auto i = lista_queues.begin();
    bool borrado = false;
    while (i != lista_queues.end() && !borrado){
        int id_actual = i->second;
        if (id_actual == id){
            i = lista_queues.erase(i);
            borrado = true;
        } else {
            i++;
        }
    }
}

