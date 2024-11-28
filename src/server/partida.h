#ifndef PARTIDA_H
#define PARTIDA_H


#include <iostream>
#include <string>
#include "gameloop.h"
#include "queues_jugadores.h"
#include <mutex>
#include <atomic>
#include "../common/comando.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include "thread_usuario.h"

class Partida {
    private:
        std::string id_partida;
        ListaQueues clientes;
        Queue<comando_t> queue;
        Gameloop juego;
        // std::atomic<bool> partida_en_curso;
        int ultimo_cliente_agregado;
        std::list<ThreadUsuario*> jugadores;
        std::mutex mtx;
        void eliminar_cliente(ThreadUsuario* jugador);

    public:
        Partida(const std::string& id_partida);

        static std::string generar_codigo();

        void agregar_jugador(Socket&& peer);

        void buscar_jugadores_desconectados();

        void terminar_partida();

        std::string get_codigo() { return this->id_partida; }

        bool en_curso() { return this->juego.jugando(); }
};


#endif