// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef PARTIDA_H
#define PARTIDA_H

#include <atomic>
#include <iostream>
#include <mutex>
#include <string>

#include "../common/comando.h"
#include "../common/queue.h"
#include "../common/socket.h"

#include "gameloop.h"
#include "queues_jugadores.h"
#include "thread_usuario.h"

// La clase 'Partida' encapsula todo lo relacionado a una instancia
// de un estado jugable del juego (Su gameloop, sus colas de comunicacion, etc.).
class Partida {
private:
    std::string id_partida;
    ListaQueues clientes;
    Queue<comando_t> queue;
    Gameloop juego;
    int ultimo_cliente_agregado;
    std::list<ThreadUsuario*> jugadores;
    std::mutex mtx;

    // Elimina los clientes que estan dentro de la partida.
    void eliminar_cliente(ThreadUsuario* jugador);

public:
    // Constructor de la clase.
    explicit Partida(const std::string& id_partida);

    // Genera un codigo de partida aleatorio.
    static std::string generar_codigo();

    // Agrega un jugador a la partida.
    void agregar_jugador(Socket&& peer);

    // Se fija si hay jugadores desconectados en la partida.
    void buscar_jugadores_desconectados();

    // Termina la partida.
    void terminar_partida();

    // Devuelve el codigo de la partida.
    std::string get_codigo() { return this->id_partida; }

    // Devuelve el estado de la partida.
    bool en_curso() { return this->juego.jugando(); }
};

#endif  // PARTIDA_H
