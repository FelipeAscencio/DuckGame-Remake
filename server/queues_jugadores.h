#ifndef QUEUES_JUGADORES_H
#define QUEUES_JUGADORES_H

#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <utility>

#include "../common/estado_juego.h"
#include "../common/queue.h"

class ListaQueues {
private:
    std::mutex mtx;
    std::list<std::pair<Queue<EstadoJuego>&, int>> lista_queues;

public:
    ListaQueues();

    void broadcast(const EstadoJuego& estado_actual);

    void agregar_queue(Queue<EstadoJuego>& q, int id_cliente);

    int get_size() { return lista_queues.size(); }

    void eliminar_queue(int id_cliente);
};

#endif
