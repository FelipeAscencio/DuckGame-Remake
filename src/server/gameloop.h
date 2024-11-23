// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef SERVER_GAMELOOP_H_
#define SERVER_GAMELOOP_H_

#include <atomic>
#include <vector>

#include "../common/comando.h"
#include "../common/estado_juego.h"
#include "../common/queue.h"
#include "../common/thread.h"
#include "server/arma.h"
#include "server/mapa.h"
#include "server/pato.h"
#include "server/queues_jugadores.h"

// La clase 'Gameloop' implementa la logica del bucle
// del juego y el control de los 'FPS'.
class Gameloop: public Thread {
private:
    Queue<comando_t>& queue;
    std::atomic<bool> juego_activo;
    ListaQueues& queues_clientes;
    std::vector<Pato*> jugadores;
    Mapa mapa;
    std::vector<bool> jugadores_vivos;
    std::vector<InformacionArma> armas_tiradas;
    std::vector<Spawn*> puntos_spawn;
    std::vector<posicion_t> cascos_tirados;
    std::vector<posicion_t> armaduras_tiradas;
    std::vector<Municion> balas_volando;

    // Devuelve true si hay más de 2 jugadores conectados y solamente 1 vivo
    bool hay_ganador();

    // Verifica las posiciones de los jugadores para detectar impactos de balas y aplicar daños.
    void chequear_posiciones();

    // Actualiza el estado de cada jugador en base a comandos previos y el mapa actual.
    void actualizar_estado_jugadores();

    // Actualiza el estado de las balas disparadas de cada jugador.
    void actualizar_balas_disparadas();

    // Envia el estado del juego actual, incluyendo informacion de jugadores y armas en el mapa.
    void enviar_estado_juego(bool hubo_ganador);

    // Revisa si hay nuevos jugadores y, de ser necesario, crea instancias de nuevos jugadores.
    void chequear_nuevos_jugadores();

    // Ejecuta una iteracion del ciclo de juego, procesando nuevos jugadores, posiciones y acciones.
    void loop_juego();

    void spawnear_elementos();

    void control_balas();
public:
    // Constructor de la clase.
    explicit Gameloop(Queue<comando_t>& q, ListaQueues& l);

    // Ejecuta el ciclo principal de juego, manteniendo la sincronizacion de tiempo y el estado del
    // juego.
    virtual void run() override;

    // Cambia el estado del juego a 'finalizado'.
    void finalizar_juego() { this->juego_activo = false; }

    // Devuelve el estado del juego (true si sigue activo, false en caso contrario).
    bool jugando() { return juego_activo; }

    // Destructor de la clase.
    ~Gameloop();
};

#endif  // SERVER_GAMELOOP_H_
