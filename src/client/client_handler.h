// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../common/estado_juego.h"
#include "../common/liberror.h"
#include "../common/queue.h"
#include "../common/thread.h"

#include "client_controlador.h"
#include "client_dibujador.h"
#include "client_enviador.h"
#include "client_recibidor.h"
#include "protocolo_cliente.h"

#define MSJ_PARTIDA_LLENA \
    "La partida esta llena, no se puede inicializar el cliente en este momento"

// Suprimimos el reporte en 'CPPLINT' de los 'namespaces'.
using namespace SDL2pp;  // NOLINT(build/namespaces)

// 'Struct' utilizado para encapsular el error de la partida llena.
struct ErrorPartidaLlena: public std::runtime_error {
    ErrorPartidaLlena(): std::runtime_error(MSJ_PARTIDA_LLENA) {}
};

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

    // Controla la comunicacion inicial con el servidor para ingresar a una nueva partida creada.
    bool ingresar_nueva_partida();

    // Entabla la comunicacion (y el loop para controlar errores de ID)
    // para conectarse a una partida ya existente en el servidor.
    bool loop_ingresar_partida_existente();

    // Entabla el primer contacto con el servidor.
    bool primer_contacto_con_servidor();

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

    // Destructor de la clase.
    ~Client();
};

#endif  // CLIENT_HANDLER_H
