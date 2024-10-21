#ifndef MONITOR_H
#define MONITOR_H

#include <list>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "queue.h"

// La clase 'Monitor' implementa la logica del 'monitor' necesario para evitar
// 'race conditions' y 'deathlocks' en el programa.
// Maneja una lista de colas de todos los clientes conectados.
class Monitor {
private:
    std::mutex mutex_monitor;
    std::list<Queue<std::string>*> lista_colas;

public:
    // Constructor de la clase.
    Monitor();

    // Agrega la cola de un jugador a la lista de colas.
    void agregar_cola_jugador(Queue<std::string>* cola_jugador);

    // Le envia el mensaje recibido por parametro a todos los jugadores.
    void enviar_mensajes(const std::string& mensaje);

    // Libera la memoria de la lista de colas
    void vaciar_cola_mensajes();

    // Deshabilito las copias.
    Monitor(const Monitor&) = delete;
    Monitor& operator=(const Monitor&) = delete;

    // Permito el movimiento del objeto.
    Monitor(Monitor&&) = default;
    Monitor& operator=(Monitor&&) = default;
};

#endif
