#include "monitor.h"

Monitor::Monitor() {}

void Monitor::agregar_cola_jugador(Queue<std::string>* cola_jugador) {
    std::lock_guard<std::mutex> lock(mutex_monitor);
    lista_colas.push_back(cola_jugador);
}

void Monitor::enviar_mensajes(const std::string& mensaje) {
    std::lock_guard<std::mutex> lock(mutex_monitor);
    for (auto& cola: lista_colas) {
        cola->try_push(mensaje);
    }
}

void Monitor::vaciar_cola_mensajes() { lista_colas.clear(); }
