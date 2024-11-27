// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef QUEUES_JUGADORES_H
#define QUEUES_JUGADORES_H

#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <utility>

#include "../common/estado_juego.h"
#include "../common/queue.h"

// La clase 'ListaQueues' se encarga de controlar las colas
// de mensajes, y utiliza el 'mutex' para evitar 'race conditions'.
class ListaQueues {
private:
    std::mutex mtx;
    std::list<std::pair<Queue<EstadoJuego>&, int>> lista_queues;

public:
    // Constructor de la clase.
    ListaQueues();

    // Envia el estado del juego a todas las colas de clientes activas.
    void broadcast(const EstadoJuego& estado_actual);

    // Agrega una nueva cola para un cliente a la lista de colas.
    void agregar_queue(Queue<EstadoJuego>& q, int id_cliente);

    // Devuelve el tamaño de la lista de colas.
    int get_size() { return lista_queues.size(); }

    // Elimina la cola asociada a un cliente usando su ID.
    void eliminar_queue(int id_cliente);

    // Deshabilito las copias.
    ListaQueues(const ListaQueues&) = delete;
    ListaQueues& operator=(const ListaQueues&) = delete;

    // Permito el movimiento del objeto.
    ListaQueues(ListaQueues&&) = default;
    ListaQueues& operator=(ListaQueues&&) = default;
};

#endif  // QUEUES_JUGADORES_H
