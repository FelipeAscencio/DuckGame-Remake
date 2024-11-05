// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef ACEPTADOR_H
#define ACEPTADOR_H

#include <atomic>
#include <list>

#include "../common/queue.h"
#include "../common/thread.h"

#include "queues_jugadores.h"
#include "thread_usuario.h"

// La clase 'Aceptador' controla la logica de la conexion
// (conexion y desconexion) del 'Cliente' con el 'Server'.
class Aceptador: public Thread {
private:
    Socket skt;
    std::list<ThreadUsuario*> jugadores;
    std::atomic<bool> aceptando_jugadores;
    Queue<comando_t>& queue_juego;
    ListaQueues& queues_clientes;

    // Recolecta y elimina los hilos de jugadores que hayan finalizado.
    void recolectar();

    // Elimina al cliente representado por 'jugador' de las colas y libera su memoria.
    void eliminar_cliente(ThreadUsuario* jugador);

public:
    // Constructor de la clase.
    explicit Aceptador(const char* servname, Queue<comando_t>& q, ListaQueues& l);

    // Inicia el hilo que acepta la conexion de los 'Clientes' con el 'Server'.
    virtual void run() override;

    // Cambia el estado del hilo para que no siga aceptando usuarios.
    void dejar_de_aceptar() { this->aceptando_jugadores = false; }

    // Destructor de la clase.
    virtual ~Aceptador();
};

#endif  // ACEPTADOR_H
