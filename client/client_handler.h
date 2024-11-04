// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <chrono>
#include <thread>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "client_controlador.h"
#include "client_dibujador.h"
#include "client_enviador.h"
#include "client_recibidor.h"
#include "protocolo_cliente.h"
#include "../common/estado_juego.h"
#include "../common/queue.h"
#include "../common/thread.h"

#include "protocolo_cliente.h"

using namespace SDL2pp;

// La clase 'Client' implementa toda la logica de control
// de los eventos y el dibujo del 'Cliente'.
// Ademas de los hilos de comunicacion con el 'Server'.
class Client {
private:
    Queue<char> cola_enviador;
    Queue<EstadoJuego> cola_recibidor;
    bool jugador_activo;
    Controlador controlador;
    std::optional<Dibujador> dibujador;
    Socket socket;
    ProtocoloCliente protocolo;
    int id;
    EnviadorCliente enviador;
    RecibidorCliente recibidor;

    // Inicia la musica de fondo y devuelve un puntero a la misma.
    Mix_Music* iniciar_musica();

    // Finaliza la musica y libera la memoria de la misma.
    void terminar_musica(Mix_Music* musica_fondo);

    // Inicia los hilos 'Enviador' y 'Recibidor' del 'Cliente'.
    void iniciar_hilos();

    // Detiene y espera que terminen los hilos 'Enviador' y 'Recibidor' del 'Cliente'.
    void finalizar_hilos();

public:
    // Constructor de la clase.
    explicit Client(const char* hostname, const char* servicio);

    // Maneja la secuencia de controlador y dibujo del 'Cliente'.
    void controlar_loop_juego();

    // Deshabilito las copias.
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    // Permito el movimiento del objeto.
    Client(Client&&) = default;
    Client& operator=(Client&&) = default;
};

#endif  // CLIENT_HANDLER_H
