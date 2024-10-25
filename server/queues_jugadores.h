#ifndef QUEUES_JUGADORES_H
#define QUEUES_JUGADORES_H


#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <utility>

#include "../common/queue.h"

#include "estado_juego.h"

class ListaQueues {
private:
    std::mutex mtx;
    std::list<std::pair<Queue<estado_juego_t>&, int>> lista_queues;

public:
    ListaQueues();

    void broadcast(const estado_juego_t& estado_actual);

    void agregar_queue(Queue<estado_juego_t>& q, int id_cliente);

    void eliminar_queue(int id_cliente);
};

#endif
