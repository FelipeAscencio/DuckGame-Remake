#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <chrono>
#include <thread>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "client_controlador.h"
#include "client_dibujador.h"

#include <atomic>
#include <string>

#include "../common/estado_juego.h"
#include "../common/queue.h"
#include "../common/thread.h"

#include "protocolo_cliente.h"

class EnviadorCliente: public Thread {
private:
    ProtocoloCliente protocol;  // conectado con el ServerRecibidor
    Queue<char>& queue_comandos;
    int id_cliente;
    std::atomic<bool> vivo;

public:
    EnviadorCliente(ProtocoloCliente& p, Queue<char>& q, int id):
            protocol(p), queue_comandos(q), id_cliente(id), vivo(true) {}

    void run() override {
        while (vivo) { //cppcheck-suppress variableScope
            char accion;
            try {
                accion = queue_comandos.pop();
                if (!protocol.enviar(accion))
                    break;
            } catch (const ClosedQueue& e) {
                std::cerr << e.what();
            }
        }
    }

    void dejar_de_enviar() { this->vivo = false; }

    ~EnviadorCliente() { this->join(); }
    // Protocolo
    // Queue <comandos> --> pop --> sendall()
};

class RecibidorCliente: public Thread {
private:
    ProtocoloCliente protocol;  // conectado con el ServerEnviador
    Queue<EstadoJuego>& queue_estados;
    std::atomic<bool> vivo;

public:
    explicit RecibidorCliente(ProtocoloCliente& p, Queue<EstadoJuego>& q):
            protocol(p), queue_estados(q), vivo(true) {}

    void run() override {
        while (vivo) {
            EstadoJuego estado_actual;
            if (!protocol.recibir(estado_actual))
                break;
            try {
                queue_estados.push(estado_actual);
            } catch (const ClosedQueue& e) {
                std::cerr << e.what();
            }
        }
    }

    void dejar_de_recibir() { this->vivo = false; }

    ~RecibidorCliente() { this->join(); }
    // Protocolo
    //  recvall() --> push --> Queue <estado_juego>
};

using namespace SDL2pp;

// La clase 'Client' implementa toda la logica de control
// de los eventos y el dibujo del 'Cliente'.
class Client {
private:
    Queue<char> queue_enviador;
    Queue<EstadoJuego> queue_recibidor;
    bool jugador_activo;
    Controlador controlador;
    std::optional<Dibujador> dibujador;
    Socket s;
    ProtocoloCliente protocolo;
    int id;
    EnviadorCliente e;
    RecibidorCliente r;

    // Inicia la musica de fondo y devuelve un puntero a la misma.
    Mix_Music* iniciar_musica();

    // Finaliza la musica y libera la memoria de la misma.
    void terminar_musica(Mix_Music* musica_fondo);

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

    ~Client();
};

#endif
